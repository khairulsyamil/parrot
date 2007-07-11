/* library.h
 *  Copyright (C) 2004, The Perl Foundation.
 *  SVN Info
 *     $Id$
 *  Overview:
 *      Contains accessor functions for the _parrotlib bytecode interface
 *  Data Structure and Algorithms:
 *  History:
 *  Notes:
 *  References:
 */

#ifndef PARROT_LIBRARY_H_GUARD
#define PARROT_LIBRARY_H_GUARD

typedef enum {
    PARROT_RUNTIME_FT_LIBRARY = 0x0001,
    PARROT_RUNTIME_FT_INCLUDE = 0x0002,
    PARROT_RUNTIME_FT_DYNEXT  = 0x0004,
    PARROT_RUNTIME_FT_PBC     = 0x0010,
    PARROT_RUNTIME_FT_PASM    = 0x0100,
    PARROT_RUNTIME_FT_PIR     = 0x0200,
    PARROT_RUNTIME_FT_PAST    = 0x0400,
    PARROT_RUNTIME_FT_SOURCE  = 0x0F00
} enum_runtime_ft;

typedef enum {
    PARROT_LIB_PATH_INCLUDE,            /* .include "foo" */
    PARROT_LIB_PATH_LIBRARY,            /* load_bytecode "bar" */
    PARROT_LIB_PATH_DYNEXT,             /* loadlib "baz" */
    PARROT_LIB_DYN_EXTS,                /* ".so", ".dylib" .. */
    /* must be last: */
    PARROT_LIB_PATH_SIZE
} enum_lib_paths;

/* HEADERIZER BEGIN: src/library.c */

PARROT_API
char* Parrot_get_runtime_prefix( PARROT_INTERP,
    STRING **prefix_str /*NULLOK*/ )
        __attribute__nonnull__(1);

PARROT_API
char* Parrot_locate_runtime_file( PARROT_INTERP,
    const char *file_name /*NN*/,
    enum_runtime_ft type )
        __attribute__nonnull__(1)
        __attribute__nonnull__(2)
        __attribute__warn_unused_result__;

PARROT_API
STRING* Parrot_locate_runtime_file_str( PARROT_INTERP,
    STRING *file /*NN*/,
    enum_runtime_ft type )
        __attribute__nonnull__(1)
        __attribute__nonnull__(2)
        __attribute__warn_unused_result__;

void parrot_init_library_paths( PARROT_INTERP )
        __attribute__nonnull__(1);

STRING * parrot_split_path_ext( Interp* interp /*NN*/,
    STRING *in,
    STRING **wo_ext /*NN*/,
    STRING **ext /*NN*/ )
        __attribute__nonnull__(1)
        __attribute__nonnull__(3)
        __attribute__nonnull__(4);

/* HEADERIZER END: src/library.c */

#endif /* PARROT_LIBRARY_H_GUARD */

/*
 * Local variables:
 *   c-file-style: "parrot"
 * End:
 * vim: expandtab shiftwidth=4:
 */
