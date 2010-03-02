#! nqp
# Copyright (C) 2010, Parrot Foundation.
# $Id$

=begin

=head1 NAME

Ops::Op - Parrot Operation

=head1 SYNOPSIS

  use Ops::Op;

=head1 DESCRIPTION

C<Ops::Op> represents a Parrot operation (op, for short), as read
from an ops file via C<Ops::OpsFile>, or perhaps even generated by
some other means. It is the Perl equivalent of the C<op_info_t> C
C<struct> defined in F<include/parrot/op.h>.

=head2 Op Type

Ops are either I<auto> or I<manual>. Manual ops are responsible for
having explicit next-op C<RETURN()> statements, while auto ops can count
on an automatically generated next-op to be appended to the op body.

Note that F<tools/build/ops2c.pl> supplies either 'inline' or 'function'
as the op's type, depending on whether the C<inline> keyword is present
in the op definition. This has the effect of causing all ops to be
considered manual.

=head2 Op Arguments

Note that argument 0 is considered to be the op itself, with arguments
1..9 being the arguments passed to the op.

Op argument direction and type are represented by short one or two letter
descriptors.

Op Direction:

    i   The argument is incoming
    o   The argument is outgoing
    io  The argument is both incoming and outgoing

Op Type:

    i   The argument is an integer register index.
    n   The argument is a number register index.
    p   The argument is a PMC register index.
    s   The argument is a string register index.
    ic  The argument is an integer constant (in-line).
    nc  The argument is a number constant index.
    pc  The argument is a PMC constant index.
    sc  The argument is a string constant index.
    kc  The argument is a key constant index.
    ki  The argument is a key integer register index.
    kic  The argument is a key integer constant (in-line).

=head2 Class Methods

=over 4

=end

class Ops::Op is PAST::Block;

=begin

=item C<new(:$code, :$type, :$name, :@args, :%flags)>

Allocates a new bodyless op. A body must be provided eventually for the
op to be usable.

C<$code> is the integer identifier for the op.

C<$type> is the type of op (see the note on op types above).

C<$name> is the name of the op.

C<@args> is a reference to an array of argument type descriptors.

C<$flags> is a hash reference containing zero or more I<hints> or
I<directives>.


=back

=head2 Instance Methods

=over 4

=item C<code()>

Returns the op code.

=item C<type()>

The type of the op, either 'inline' or 'function'.

=item C<name()>

The (short or root) name of the op.

=item C<full_name()>

For argumentless ops, it's the same as C<name()>. For ops with
arguments, an underscore followed by underscore-separated argument types
are appended to the name.

=item C<func_name()>

The same as C<full_name()>, but with 'C<Parrot_>' prefixed.

=end

method code($code?) { self.attr('code', $code, defined($code)) }

method type($type?) { self.attr('type', $type, defined($type)) }

method name($name?) { self.attr('name', $name, defined($name)) }

method args($args?) { self.attr('args', $args, defined($args)) }


method full_name() {
    my $name      := self.name;
    my @arg_types := self.arg_types;

    join('_', $name, @arg_types);
}

method func_name($trans) {
    return $trans.prefix ~ self.full_name;
}


=begin

=item C<flags()>

Sets the op's flags.  This returns a hash reference, whose keys are any
flags (passed as ":flag") specified for the op.

=end

method flags(%flags?) { self.attr('flags', %flags, defined(%flags)) }

=begin

=item C<body($body)>

=item C<body()>

Sets/gets the op's code body.

=end

method body($body?) { self.attr('body', $body, defined($body)) }

=begin

=item C<jump($jump)>

=item C<jump()>

Sets/gets a string containing one or more C<op_jump_t> values joined with
C<|> (see F<include/parrot/op.h>). This indicates if and how an op
may jump.

=end

method jump(*@jumps) {

    if (@jumps) {
        self<JUMP> := @jumps;
    }

    self<JUMP>;
}

=begin

=item C<full_body()>

For manual ops, C<full_body()> is the same as C<body()>. For auto ops
this method adds a final C<goto NEXT()> line to the code to represent
the auto-computed return value. See the note on op types above.

=end

method full_body() {
    my $body := self.body;

    # FIXME
    #$body := $body ~ '_' ~ sprintf( "  {{+=%d}};\n", self.size ) if self.type eq 'auto';

    $body;
}

=begin

# Called from rewrite_body() to perform the actual substitutions.
sub _substitute {
    my $self           = shift;
    local $_           = shift;
    my $trans          = shift;
    my $preamble_only  = shift;

    my $rewrote_access =
        s/{{\@([^{]*?)}}/   $trans->access_arg($self->arg_type($1 - 1), $1, $self); /me;

    die "Argument access not allowed in preamble\n"
        if $preamble_only && $rewrote_access;

    s/{{=0,=([^{]*?)}}/   $trans->restart_address($1) . "; {{=0}}"; /me;
    s/{{=0,\+=([^{]*?)}}/ $trans->restart_offset($1)  . "; {{=0}}"; /me;
    s/{{=0,-=([^{]*?)}}/  $trans->restart_offset(-$1) . "; {{=0}}"; /me;

    s/{{\+=([^{]*?)}}/    $trans->goto_offset($1);  /me;
    s/{{-=([^{]*?)}}/     $trans->goto_offset(-$1); /me;
    s/{{=([^*][^{]*?)}}/  $trans->goto_address($1); /me;

    s/{{\^(-?\d+)}}/      $1                        /me;
    s/{{\^\+([^{]*?)}}/   $trans->expr_offset($1);  /me;
    s/{{\^-([^{]*?)}}/    $trans->expr_offset(-$1); /me;
    s/{{\^([^{]*?)}}/     $trans->expr_address($1); /me;

    return $_;
}

=item C<rewrite_body($body, $trans, [$preamble])>

Performs the various macro substitutions using the specified transform,
correctly handling nested substitions, and repeating over the whole string
until no more substitutions can be made.

C<VTABLE_> macros are enforced by converting C<<< I<< x >>->vtable->I<<
method >> >>> to C<VTABLE_I<method>>.

=cut

sub rewrite_body {
    my ( $self, $body, $trans, $preamble_only ) = @_;

    # use vtable macros
    $body =~ s!
        (?:
            {{\@\d+\}}
            |
            \b\w+(?:->\w+)*
        )->vtable->\s*(\w+)\(
        !VTABLE_$1(!sgx;

    while (1) {
        my $new_body = $self->_substitute( $body, $trans, !!$preamble_only );

        last if $body eq $new_body;

        $body = $new_body;
    }

    return $body;
}

=item C<source($trans)>

Returns the L<C<full_body()>> of the op with substitutions made by
C<$trans> (a subclass of C<Ops::OpTrans>).

=cut

sub source {
    my ( $self, $trans ) = @_;

    my $flags = $self->flags;

    if (exists($$flags{pic})
        && !( ref($trans) eq 'Ops::OpTrans::CGP' || ref($trans) eq 'Ops::OpTrans::CSwitch' ) )
    {
        return qq{PANIC(interp, "How did you do that");\n};
    }

    my $prelude = $trans->can( 'add_body_prelude' )
                ? $trans->add_body_prelude()
                : '';

    return $self->rewrite_body( $prelude . $self->full_body, $trans );
}

=item C<size()>

Returns the op's number of arguments. Note that this also includes
the op itself as one argument.

=cut

sub size {
    my $self = shift;

    return scalar( $self->arg_types + 1 );
}
=end

=begin

=back

=head1 SEE ALSO

=over 4

=item C<Ops::OpsFile>

=item C<Ops::OpTrans>

=item F<tools/build/ops2c.pl>

=item F<tools/build/ops2pm.pl>

=item F<tools/build/pbc2c.pl>

=back

=head1 HISTORY

Author: Gregor N. Purdy E<lt>gregor@focusresearch.comE<gt>

Migrate to NQP: Vasily Chekalkin E<lt>bacek@bacek.comE<gt>

=end

1;

# Local Variables:
#   mode: cperl
#   cperl-indent-level: 4
#   fill-column: 100
# End:
# vim: ft=perl6 expandtab shiftwidth=4:

