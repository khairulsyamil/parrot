#! perl
# Copyright (C) 2009, The Perl Foundation.
# $Id: auto_neg_0-01.t 30640 2008-08-29 23:09:28Z rurban $
# auto_neg_0-01.t

use strict;
use warnings;
use Test::More tests => 16;
use Carp;
use lib qw( lib t/configure/testlib );
use_ok('config::auto::neg_0');
use Parrot::Configure;
use Parrot::Configure::Options qw( process_options );
use Parrot::Configure::Test qw(
    test_step_thru_runstep
    rerun_defaults_for_testing
    test_step_constructor_and_description
);
use IO::CaptureOutput qw| capture |;

########### regular ###########

my ($args, $step_list_ref) = process_options(
    {
        argv => [ ],
        mode => q{configure},
    }
);

my $conf = Parrot::Configure->new;

my $pkg = q{auto::neg_0};

$conf->add_steps($pkg);

my $serialized = $conf->pcfreeze();

$conf->options->set( %{$args} );
my $step = test_step_constructor_and_description($conf);
my $ret = $step->runstep($conf);
ok( $ret, "runstep() returned true value" );
ok(defined($step->result()), "A result has been defined");

$conf->replenish($serialized);

##### _evaluate_cc_run() #####

($args, $step_list_ref) = process_options(
    {
        argv => [ ],
        mode => q{configure},
    }
);
$conf->options->set( %{$args} );
$step = test_step_constructor_and_description($conf);

my $d_neg_0;

$d_neg_0 = q{-0};
ok($step->_evaluate_cc_run($conf, $d_neg_0),
    "_evaluate_cc_run() completed satisfactorily");
is($step->result(), q{yes}, "Got expected result");
is($conf->data->get('has_negative_zero'), 1,
    "has_negative_zero set as expected");

$d_neg_0 = q{0};
ok(!$step->_evaluate_cc_run($conf, $d_neg_0),
    "_evaluate_cc_run() completed satisfactorily");
is($step->result(), q{no}, "Got expected result");
is($conf->data->get('has_negative_zero'), 0,
    "has_negative_zero set as expected");

pass("Completed all tests in $0");

################### DOCUMENTATION ###################

=head1 NAME

auto_neg_0-01.t - test auto::neg_0

=head1 SYNOPSIS

    % prove t/steps/auto_neg_0-01.t

=head1 DESCRIPTION

The files in this directory test functionality used by F<Configure.pl>.

The tests in this file test auto::neg_0.

=head1 AUTHOR

Reini Urban

=head1 SEE ALSO

config::auto::neg_0, F<Configure.pl>.

=cut

# Local Variables:
#   mode: cperl
#   cperl-indent-level: 4
#   fill-column: 100
# End:
# vim: expandtab shiftwidth=4:
