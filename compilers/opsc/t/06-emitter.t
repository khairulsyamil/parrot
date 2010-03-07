#! ./parrot-nqp

pir::load_bytecode("compilers/opsc/opsc.pbc");
pir::load_bytecode("nqp-settings.pbc");

plan(18);

my $trans := Ops::Trans::C.new();

my @files := <
    src/ops/io.ops
    src/ops/sys.ops
>;

my $f := Ops::File.new(|@files);
my $emitter := Ops::Emitter.new(
    :ops_file($f), :trans($trans), :script('ops2c'),
    :flags(
        hash( dir => 'tmp/', core => 1 )
    ),
);

ok( $emitter, "Emitter created");
ok( $emitter<include> eq 'parrot/oplib/core_ops.h', 'Include is correct');
say('# ' ~ $emitter<include>);
ok( $emitter<header> ~~ /^tmp/, 'header file in tmp');
say('# ' ~ $emitter<header>);

#$emitter.print_c_header_file();

my $fh := pir::new__Ps('StringHandle');
$fh.open('header.h', 'w');
$emitter.emit_c_header_file($fh);

$fh.close();
my $header := $fh.readall();

ok($header ~~ /define \s PARROT_OPLIB_CORE_OPS_H_GUARD/, 'Guard generated');
ok($header ~~ /endif/, 'Close guard generated');
ok($header ~~ /DO \s NOT \s EDIT \s THIS \s FILE/, 'Preamble generated');
ok($header ~~ /Parrot_DynOp_core_ \d+ _ \d+ _ \d+/, '... and contains init_func');

# Testing C emitting.
#$emitter.print_c_source_file();

$fh := pir::new__Ps('StringHandle');
$fh.open('core.c', 'w');
$emitter.emit_c_source_file($fh);

$fh.close();
my $source := $fh.readall();

ok($source ~~ /DO \s NOT \s EDIT \s THIS \s FILE/, 'Preamble generated');
ok($source ~~ /Parrot_pcc_get_constants/, 'defines from Trans::C generated');
ok($source ~~ /io_private.h/, 'Preamble from io.ops preserved');

ok($source ~~ /static \s int \s get_op/, 'Trans::C preamble generated');

ok($source ~~ /PARROT_FUNCTION_CORE/, 'Trans::C core_type preserved');
ok($source ~~ /static \s size_t \s hash_str/, 'Trans::C op_lookup preserved');

ok($source ~~ /'PREG(1)'/, 'Trans::C arg translation works');
ok($source ~! /'OP_SIZE'/, 'Trans::C translates OP_SIZE');


my $op_body := '
inline op do_stuff(invar PMC)
{
    restart ADDRESS(234);
}';
my $new_body := translate_op_body($trans, $op_body);
my $restart_addr_ok := $new_body ~~ /'return' \s '(' 'opcode_t' \s '*' ')' \s '234'/;
ok($restart_addr_ok, "restart ADDRESS() translated ok");

$op_body := '
inline op branch(in LABEL) :base_loop :flow {
    goto OFFSET($1);
}';
$new_body := translate_op_body($trans, $op_body);
$restart_addr_ok := $new_body ~~ /'return (opcode_t *) cur_opcode + IREG(1);'/;
ok($restart_addr_ok, "goto OFFSET() and \$1 translated ok");
ok($new_body ~~ /'PARROT_JUMP_RELATIVE'/, "jump flags generated");

#say($source);

sub translate_op_body($trans, $body) {
    my $file  := Ops::File.new_str($body);
    my $emitter := Ops::Emitter.new(
        :ops_file($file),
        :trans($trans),
        :script("opsc"),
        :flags( hash(core => '1') )
    );

    my $sh := pir::new__Ps('StringHandle');
    $sh.open('your_bank_account_information.txt', 'w');
    $emitter.emit_c_source_file($sh);
    $sh.close();
    $sh.readall();
}

# vim: expandtab shiftwidth=4 ft=perl6:
