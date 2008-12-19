# Copyright (C) 2007, The Perl Foundation.
# $Id$
package Parrot::OpsRenumber;
use strict;
use warnings;
use lib qw ( lib );
use base qw( Parrot::Ops2pm::Base );
#use Parrot::OpsFile;

=head1 NAME

Parrot::OpsRenumber - Methods holding functionality for F<tools/build/opsrenumber.pl>.

=head1 SYNOPSIS

    use Parrot::Config qw( %PConfig );
    use Parrot::OpsRenumber;

    $self = Parrot::OpsRenumber->new( {
        argv            => [ @ARGV ],
        nolines         => $nolines_flag,
        moddir          => "lib/Parrot/OpLib",
        module          => "core.pm",
        inc_dir         => "include/parrot/oplib",
        inc_f           => "ops.h",
        script          => "tools/build/opsrenumber.pl",
    } );

    $self->prepare_ops();
    $self->renum_op_map_file( $PConfig{MAJOR} );

=cut

=head1 DESCRIPTION

Parrot::OpsRenumber provides methods called by F<tools/dev/opsrenumber.pl>.

=head1 METHODS

=head2 C<new()>

Inherited from Parrot::Ops2pm::Base and documented in
F<lib/Parrot/Ops2pm/Base.pm>.

=head2 C<prepare_ops()>

Inherited from Parrot::Ops2pm::Base and documented in
F<lib/Parrot/Ops2pm/Base.pm>.

=head2 C<renum_op_map_file()>

=over 4

=item * Purpose

This method renumbers F<src/ops/ops.num> based on the already
existing file of that name and additional F<.ops> files.

=item * Arguments

Two scalars.  First is Parrot major version number.  Second is optional:
string holding name of an F<.ops> file; defaults to F<src/ops/ops.num>.
(Implicitly requires that the C<argv> and C<script> elements were provided to
the constructor.)

=item * Return Value

Returns true value upon success.

=back

=cut

sub renum_op_map_file {
    my $self = shift;
    my $major_version = shift;

    my $file = scalar(@_) ? shift : $self->{num_file};
    if ($major_version == 0) {
        # Pre-Parrot 1.0 case

        # We open up the currently existing ops.num and file and read it
        # line-by-line.  That file is basically divided into two halves
        # separated by the ###DYNAMIC### line.  Above that line are found
        # (a) # inline comments and
        # (b) the first 7, never-to-be-altered opcodes.
        # Below that line are all the remaining opcodes.  All opcode lines
        # match the pattern /^(\w+)\s+(\d+)$/.  Everything above the line gets
        # pushed into @lines and, if it's an opcode line, gets split and
        # pushed into %fixed as well.  Nothing happens to the (opcode) lines
        # below the DYNAMIC line.

        my ( $name, $number, @lines, %seen, %fixed, $fix );
        $fix = 1;
        open my $OP, '<', $file
            or die "Can't open $file, error $!";
        while (<$OP>) {
            push @lines, $_ if $fix;
            chomp;
            $fix = 0 if /^###DYNAMIC###/;
            s/#.*$//;
            s/\s*$//;
            s/^\s*//;
            next unless $_;
            ( $name, $number ) = split( /\s+/, $_ );
            $seen{$name}  = $number;
            $fixed{$name} = $number if $fix;
        }
        close $OP;

        # Now we re-open the very same file we just read -- this time for
        # writing.  We directly print all the lines in @lines, i.e., those
        # above the DYNAMIC line.  For the purpose of renumbering, we create
        # an index $n.

        open $OP, '>', $file
            or die "Can't open $file, error $!";
        print $OP @lines;
        my ($n);

        # We can't use all autogenerated ops from oplib/core
        # there are unwanted permutations like 'add_i_ic_ic
        # which aren't opcodes but calculated at compile-time.

        # The ops element is set by prepare_ops(), which is inherited from
        # Parrot::Ops2pm::Base.  prepare_ops(), in turn, works off
        # Parrot::OpsFile.

        # So whether a particular opcode will appear in the *new* ops.num
        # depends entirely on whether or not it's found in
        # @{ $self->{ops}->{OPS} }.  If a particular opcode has been deleted or
        # gone missing from that array, then it won't appear in the new
        # ops.num.  That's acceptable pre-version 1.0, but not afterwards (per
        # http://rt.perl.org/rt3/Ticket/Display.html?id=53976).  At and after
        # 1.0, the opcodes in ops.num will be non-deletable.  New opcodes may
        # be added to the end of the list and numbered accordingly, but no
        # opcodes may be deleted.

        for ( @{ $self->{ops}->{OPS} } ) {

            # To account for the number of opcodes above the line, we'll
            # increment the index by one for every element in %fixed.

            if ( defined $fixed{ $_->full_name } ) {
                $n = $fixed{ $_->full_name };
            }

            # For all other opcodes, we'll print the opcode, increment the
            # index, then print the index on that same line.

            elsif ( $seen{ $_->full_name } ) {
                printf $OP "%-31s%4d\n", $_->full_name, ++$n;
            }
        }
        close $OP;
    }
    else {
        # Parrot 1.0 and beyond case
        my ( $name, $number, @lines, %fixed );
        open my $OP, '<', $file
            or die "Can't open $file, error $!";
        while (<$OP>) {
            push @lines, $_;
            chomp;
            s/#.*$//;
            s/\s*$//;
            s/^\s*//;
            next unless $_;
            ( $name, $number ) = split( /\s+/, $_ );
            $fixed{$name} = $number;
        }
        close $OP;

        # We re-open the very same file we just read -- this time for
        # writing.  We directly print all the lines in @lines -- but post-1.0
        # that means re-printing the whole file (not just entries
        # above the DYNAMIC line).  For the purpose of renumbering, we create
        # an index $n and initialize it at the highest opcode number yet seen.

        open $OP, '>', $file
            or die "Can't open $file, error $!";
        print $OP @lines;
        my $n = (scalar keys %fixed) - 1;

        # We now add any opcodes detected by Parrot::OpsFile but not seen
        # heretofore in src/ops/ops.num.
        for my $op ( @{ $self->{ops}->{OPS} } ) {
            my $fn = $op->full_name;
            if (! defined $fixed{$fn} ) {
                printf $OP "%-31s%4d\n", $fn, ++$n;
            }
        }
        close $OP;
    }
    return 1;
}

1;

# Local Variables:
#   mode: cperl
#   cperl-indent-level: 4
#   fill-column: 100
# End:
# vim: expandtab shiftwidth=4:
