#! parrot
# Copyright (C) 2009, Parrot Foundation.
# $Id$

=head1 NAME

pbc_to_exe

=head2 SYNOPSIS

  pbc_to_exe my.pbc
  => my.exe

  pbc_to_exe my.pbc --install
  => installable_my.exe

Warning! With --install there must be no directory prefix in the first arg yet.

=cut

.include 'library/config.pir'

.sub 'main' :main
    .param pmc    argv
    .local string infile
    .local string cfile
    .local string objfile
    .local string exefile
    .local string out
    .local int    closeresult

    (infile, cfile, objfile, exefile) = 'handle_args'(argv)
    unless infile > '' goto err_infile

    # Generate the string (on non-Win32) or string table (on Win32) that
    # contains all the bytecode. Also generate the get_program_code function
    # that masks the difference between the two representations.
    .local string codestring
    $P0 = '_config'()
    .local string osname
    osname = $P0['osname']
    # XXX This needs to test for MS compiler, not just Win32; Mingw32 does not need the slow version.
    unless osname == 'MSWin32' goto code_for_non_windows
  code_for_windows:
    codestring = 'generate_code_win32'(infile)
    goto code_end
  code_for_non_windows:
    codestring = 'generate_code'(infile)
  code_end:


  open_outfile:
    .local pmc outfh
    outfh = open cfile, 'w'
    unless outfh goto err_outfh
    print outfh, <<'HEADER'
#include "parrot/parrot.h"
#include "parrot/embed.h"
HEADER

    print outfh, codestring

    print outfh, <<'MAIN'

        int main(int argc, char *argv[])
        {
            PackFile     *pf;
            Parrot_Interp interp;

            const char   * const program_code = get_program_code();
            if (!program_code)
                return 1;

            Parrot_set_config_hash();

            interp = Parrot_new( NULL );

            if (!interp)
                return 1;

            Parrot_set_executable_name(interp,
                Parrot_str_new(interp, argv[0], 0));
            Parrot_set_flag(interp, PARROT_DESTROY_FLAG);

            pf = PackFile_new(interp, 0);

            if (!PackFile_unpack(interp, pf,
                    (const opcode_t *)program_code, bytecode_size))
                return 1;

            do_sub_pragmas(interp, pf->cur_cs, PBC_PBC, NULL);

            Parrot_pbc_load(interp, pf);

            PackFile_fixup_subs(interp, PBC_MAIN, NULL);
            Parrot_runcode(interp, argc, argv);
            Parrot_destroy(interp);
            Parrot_exit(interp, 0);
        }
MAIN

    # The close opcode does not return a result code,
    # use the method instead.
    closeresult = outfh.'close'()
    unless closeresult == 0 goto err_close

    'compile_file'(cfile, objfile)
    'link_file'(objfile, exefile)
    .return ()

  err_infile:
    die "cannot read infile"
  err_outfh:
    die "cannot write outfile"
  err_close:
    die "cannot close outfile"
.end


.sub 'handle_args'
    .param pmc argv

    .local pmc args
    args   = argv

    .local int argc
    argc = args

    if argc == 2 goto proper_args
    if argc == 3 goto check_install
    .return ()

  check_install:
    .local string infile, install

    $P0    = shift args
    infile = shift args
    install = shift args
    if install == '--install' goto proper_install
    .return ()

  proper_install:
    .local string cfile, objfile, obj, exefile, exe

    $P0    = '_config'()
    obj    = $P0['o']
    exe    = $P0['exe']

    .local int infile_len
    infile_len  = length infile
    infile_len -= 3

    cfile       = substr infile, 0, infile_len
    cfile      .= 'c'

    dec infile_len
    objfile     = substr infile, 0, infile_len
    exefile     = 'installable_'
    exefile    .= objfile
    exefile    .= exe
    objfile    .= obj
    .return(infile, cfile, objfile, exefile)

  proper_args:
    .local string infile, cfile, objfile, obj, exefile, exe

    $P0    = '_config'()
    obj    = $P0['o']
    exe    = $P0['exe']

    $P0    = shift args
    infile = shift args

    .local int infile_len
    infile_len  = length infile
    infile_len -= 3

    cfile       = substr infile, 0, infile_len
    cfile      .= 'c'

    dec infile_len
    objfile     = substr infile, 0, infile_len
    objfile    .= obj
    exefile     = substr infile, 0, infile_len
    exefile    .= exe

    # substitute .c for .pbc
    # remove .c for executable

    # TODO this should complain about results/returns mismatch
    .return(infile, cfile, objfile, exefile)
.end

# The PBC will be represented as a C string, so this sub builds a table
# of the C representation of each ASCII character, for lookup by ordinal value.
.sub 'generate_encoding_table'
    # Use '\%o' for speed, or '\x%02x' for readability
    .const string encoding_format = '\%o'

    # The 'sprintf' op requires the arglist to be in an array, even when
    # there is only one arg.
    .local pmc one_number
    one_number    = new 'FixedIntegerArray'
    set one_number, 1

    .local pmc coded_strings
    coded_strings = new 'FixedStringArray'
    set coded_strings, 256

    .local int index
    index = 0

  next_index:
    one_number[0] = index
    $S0 = sprintf encoding_format, one_number
    coded_strings[index] = $S0
    inc index
    if index < 256 goto next_index

    .return (coded_strings)
.end

# With GCC (and all other known non-Microsoft compilers), huge string constants
# are allowed. We generate a single C string to represent the entire bytecode.
# The get_program_code function simply returns a pointer to the compile-time
# string.
.sub 'generate_code'
    .param string infile
    .local pmc ifh
    ifh = open infile, 'r'
    unless ifh goto err_infile

    .local pmc encoding_table
    encoding_table = 'generate_encoding_table'()

    .local string codestring
    .local int size
    codestring = "const char * const program_code_raw =\n"
    codestring .= '"'
    size = 0

  read_loop:
    .local string pbcstring
    .local int pbclength

    pbcstring = read ifh, 16384
    pbclength = length pbcstring
    unless pbclength > 0 goto read_done

    .local int pos
    pos = 0
  code_loop:
    unless pos < pbclength goto code_done
    $I0 = ord pbcstring, pos
    $S0 = encoding_table[$I0]
    codestring .= $S0
    inc pos
    inc size
    $I0 = size % 32
    unless $I0 == 0 goto code_loop
    codestring .= '"'
    codestring .= "\n"
    codestring .= '"'
    goto code_loop
  code_done:
    goto read_loop

  read_done:
    close ifh

    codestring .= '"'
    codestring .= "\n;\n\n"
    codestring .= "const int bytecode_size = "
    $S0 = size
    codestring .= $S0
    codestring .= ";\n"

    $S0 = <<'SUBROUTINE'
        const char * get_program_code(void);
        const char * get_program_code(void)
        {
            return program_code_raw;
        }
SUBROUTINE
    codestring .= $S0

    .return (codestring)

  err_infile:
    die "cannot open infile"
.end


# On the most limited known version of the Microsoft C compiler, 16KB is the
# maximum size of a string. We generate an array of C strings to represent
# the bytecode; each string is of a fixed size smaller than 16KB.
# The get_program_code() function allocates a block large enough to contain
# the entire bytecode, then fills the block with the C strings at run-time.
.sub 'generate_code_win32'
    .param string infile
    .local pmc ifh
    ifh = open infile, 'r'
    unless ifh goto err_infile

    # Since we cannot use the last byte (the end-of-string NULL), the maximum
    # block size would be 16384-1. However, we will use 16384-32 (the number
    # of bytes in each line) to simplify the code.
    .const int line_length = 32
    .const int max_block_size = 16352

    .local pmc encoding_table
    encoding_table = 'generate_encoding_table'()

    .local string codestring
    .local int size
    codestring = "const char * const program_code_array[] = {\n"
    size = 0

  read_loop:
    .local string pbcstring
    .local int pbclength

    pbcstring = read ifh, max_block_size
    pbclength = length pbcstring
    unless pbclength > 0 goto read_done

    # This padding is to keep the memcpy() from ever having to deal with a short block.
  pad_to_full_block:
    unless pbclength < max_block_size goto end_pad
    pbcstring .= "\0"
    inc pbclength
    goto pad_to_full_block
  end_pad:

    if size == 0 goto skip_comma_separating_strings
    codestring .= ",\n"
  skip_comma_separating_strings:


    .local int pos
    pos = 0
  code_loop:
    unless pos < pbclength goto code_done

    $I0 = pos % line_length
    unless $I0 == 0 goto skip_line_start_quote
    codestring .= '  "'
  skip_line_start_quote:


    $I0 = ord pbcstring, pos
    $S0 = encoding_table[$I0]
    codestring .= $S0
    inc pos
    inc size


    $I0 = size % line_length
    unless $I0 == 0 goto skip_line_end_quote
    codestring .= '"'
    codestring .= "\n"
  skip_line_end_quote:

    goto code_loop
  code_done:
    goto read_loop

  read_done:
    close ifh

    codestring .= ",\nNULL\n"
    codestring .= "};\n\n"

    codestring .= "const int bytecode_size = "
    $S0 = size
    codestring .= $S0
    codestring .= ";\n"

    codestring .= "const int max_block_size = "
    $S0 = max_block_size
    codestring .= $S0
    codestring .= ";\n"

    $S0 = <<'SUBROUTINE'
        const char * get_program_code(void);
        const char * get_program_code(void)
        {
            int i;
            char *p, *program_code_in_one_block;

            program_code_in_one_block = malloc( bytecode_size );
            if (!program_code_in_one_block)
                return NULL;

            for ( i = 0, p = program_code_in_one_block; program_code_array[i]; i++, p += max_block_size )
                memcpy( p, program_code_array[i], max_block_size );

            return program_code_in_one_block;
        }
SUBROUTINE
    codestring .= $S0

    .return (codestring)

  err_infile:
    die "cannot open infile"
.end


# util functions
.sub 'compile_file'
    .param string cfile
    .param string objfile
    .param int install :optional

    $P0 = '_config'()
    .local string cc, ccflags, cc_o_out, osname, build_dir, slash
    cc        = $P0['cc']
    ccflags   = $P0['ccflags']
    cc_o_out  = $P0['cc_o_out']
    osname    = $P0['osname']
    build_dir = $P0['build_dir']
    slash     = $P0['slash']

    .local string includedir, pathquote
    includedir = concat build_dir, slash
    includedir = concat includedir, 'include'
    pathquote  = ''
    unless osname == 'MSWin32' goto not_windows
    pathquote  = '"'
  not_windows:

    .local string compile
    compile  = cc
    compile .= ' '
    compile .= cc_o_out
    compile .= objfile
    compile .= ' -I'
    compile .= pathquote
    compile .= includedir
    compile .= pathquote
    compile .= ' '
    compile .= ccflags
    compile .= ' -c '
    compile .= cfile

    say compile
    .local int status
    status = spawnw compile
    unless status goto compiled

    die "compilation failed"

  compiled:
    print "Compiled: "
    say objfile
    .return()
.end

.sub 'link_file'
    .param string objfile
    .param string exefile
    .param int install :optional

    $P0 = '_config'()
    .local string cc, link, link_dynamic, linkflags, ld_out, libparrot, libs, o
    .local string rpath, osname, build_dir, slash, icushared
    cc           = $P0['cc']
    link         = $P0['link']
    link_dynamic = $P0['link_dynamic']
    linkflags    = $P0['linkflags']
    ld_out       = $P0['ld_out']
    libparrot    = $P0['libparrot_ldflags']
    libs         = $P0['libs']
    o            = $P0['o']
    rpath        = $P0['rpath_blib']
    osname       = $P0['osname']
    build_dir    = $P0['build_dir']
    slash        = $P0['slash']
    icushared    = $P0['icu_shared']

    .local string config, pathquote, exeprefix
    exeprefix = substr exefile, 0, 12
    config     = concat build_dir, slash
    config    .= 'src'
    config    .= slash
    if exeprefix == 'installable_' goto config_install
    config    .= 'parrot_config'
    goto config_cont
 config_install:
    config    .= 'install_config'
    rpath     = $P0['rpath_lib']
 config_cont:
    config    .= o
    pathquote  = ''
    unless osname == 'MSWin32' goto not_windows
    pathquote  = '"'
  not_windows:

    link .= ' '
    link .= ld_out
    link .= exefile
    link .= ' '
    link .= pathquote
    link .= objfile
    link .= pathquote
    link .= ' '
    link .= config
    link .= ' '
    link .= rpath
    link .= ' '
    link .= libparrot
    link .= ' '
    link .= link_dynamic
    link .= ' '
    link .= linkflags
    link .= ' '
    link .= libs
    link .= ' '
    link .= icushared

    say link
    .local int status
    status = spawnw link
    unless status goto check_manifest

    die "linking failed"

  check_manifest:
    # Check if there is a MSVC app manifest
    .local pmc file
    file = new 'File'
    .local string manifest_file_name
    manifest_file_name  = exefile
    manifest_file_name .= '.manifest'
    .local pmc manifest_exists
    manifest_exists = file.'exists'( manifest_file_name )
    unless manifest_exists goto linked

  embed_manifest:
    # MSVC app manifest exists, embed it
    .local string embed_manifest_str
    embed_manifest_str  = 'mt.exe -nologo -manifest '
    embed_manifest_str .= manifest_file_name
    embed_manifest_str .= ' -outputresource:'
    embed_manifest_str .= exefile
    embed_manifest_str .= ';1'

    say embed_manifest_str
    .local int embed_manifest_status
    embed_manifest_status = spawnw embed_manifest_str
    unless embed_manifest_status goto linked
    die 'manifest embedding failed'

  linked:
    print "Linked: "
    say exefile
    .return()
.end


# Local Variables:
#   mode: pir
#   fill-column: 100
# End:
# vim: expandtab shiftwidth=4 ft=pir:
