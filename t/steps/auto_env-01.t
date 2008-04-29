#! perl
# Copyright (C) 2007, The Perl Foundation.
# $Id$
# auto_env-01.t

use strict;
use warnings;
use Test::More tests =>  11;
use Carp;
use lib qw( lib t/configure/testlib );
use_ok('config::init::defaults');
use_ok('config::auto::env');
use Parrot::Configure;
use Parrot::Configure::Options qw( process_options );
use Parrot::Configure::Test qw( test_step_thru_runstep);

my $args = process_options( {
    argv            => [],
    mode            => q{configure},
} );

my $conf = Parrot::Configure->new();

test_step_thru_runstep($conf, q{init::defaults}, $args);

my ($task, $step_name, $step, $ret);
my $pkg = q{auto::env};

$conf->add_steps($pkg);
$conf->options->set(%{$args});
$task = $conf->steps->[1];
$step_name   = $task->step;

$step = $step_name->new();
ok(defined $step, "$step_name constructor returned defined value");
isa_ok($step, $step_name);
ok($step->description(), "$step_name has description");

ok($step->runstep($conf), "runstep() returned true value");


pass("Completed all tests in $0");

################### DOCUMENTATION ###################

=head1 NAME

auto_env-01.t - test config::auto::env

=head1 SYNOPSIS

    % prove t/steps/auto_env-01.t

=head1 DESCRIPTION

The files in this directory test functionality used by F<Configure.pl>.

The tests in this file test subroutines found in config::auto::env in
its most ordinary usage.

=head1 AUTHOR

James E Keenan

=head1 SEE ALSO

config::auto::env, F<Configure.pl>.

=cut

# Local Variables:
#   mode: cperl
#   cperl-indent-level: 4
#   fill-column: 100
# End:
# vim: expandtab shiftwidth=4:
