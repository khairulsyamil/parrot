#! perl
# Copyright (C) 2007, Parrot Foundation.
# $Id$
# auto/jit-01.t

use strict;
use warnings;
use Test::More tests =>  9;
use Carp;
use Cwd;
use File::Path qw( mkpath );
use File::Temp qw( tempdir );
use File::Spec;
use lib qw( lib t/configure/testlib );
use_ok('config::init::defaults');
use_ok('config::auto::jit');
use Parrot::Configure;
use Parrot::Configure::Options qw( process_options );
use IO::CaptureOutput qw( capture );
use Parrot::Configure::Test qw(
    test_step_thru_runstep
    rerun_defaults_for_testing
    test_step_constructor_and_description
);


my ($args, $step_list_ref) = process_options( {
    argv => [ ],
    mode => q{configure},
} );

my $conf = Parrot::Configure->new;

my $serialized = $conf->pcfreeze();

test_step_thru_runstep( $conf, q{init::defaults}, $args );

my $pkg = q{auto::jit};
$conf->add_steps($pkg);
$conf->options->set( %{$args} );
my $step = test_step_constructor_and_description($conf);

################### DOCUMENTATION ###################

=head1 NAME

auto/jit-01.t - test auto::jit

=head1 SYNOPSIS

    % prove t/steps/auto/jit-01.t

=head1 DESCRIPTION

The files in this directory test functionality used by F<Configure.pl>.

The tests in this file test auto::jit.

=head1 AUTHOR

James E Keenan

=head1 SEE ALSO

config::auto::jit, F<Configure.pl>.

=cut

# Local Variables:
#   mode: cperl
#   cperl-indent-level: 4
#   fill-column: 100
# End:
# vim: expandtab shiftwidth=4:
