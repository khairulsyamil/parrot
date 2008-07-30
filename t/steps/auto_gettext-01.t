#! perl
# Copyright (C) 2007, The Perl Foundation.
# $Id$
# auto_gettext-01.t

use strict;
use warnings;
use Test::More tests =>  39;
use Carp;
use lib qw( lib t/configure/testlib );
use_ok('config::init::defaults');
use_ok('config::auto::gettext');
use Parrot::Configure;
use Parrot::Configure::Options qw( process_options );
use Parrot::Configure::Test qw(
    test_step_thru_runstep
    rerun_defaults_for_testing
    test_step_constructor_and_description
);
use IO::CaptureOutput qw( capture );

########## --without-gettext ##########

my $args = process_options(
    {
        argv => [ q{--without-gettext} ],
        mode => q{configure},
    }
);

my $conf = Parrot::Configure->new;

test_step_thru_runstep( $conf, q{init::defaults}, $args );

my $pkg = q{auto::gettext};

$conf->add_steps($pkg);

my $serialized = $conf->pcfreeze();

$conf->options->set( %{$args} );
my $step = test_step_constructor_and_description($conf);
my $ret = $step->runstep($conf);
ok( $ret, "runstep() returned true value" );
is($conf->data->get('has_gettext'), 0,
    "Got expected value for 'has_gettext'");
is($step->result(), q{no}, "Expected result was set");

$conf->replenish($serialized);

########## _add_to_libs() ##########

$args = process_options( {
    argv => [ ],
    mode => q{configure},
} );
$conf->options->set( %{$args} );
$step = test_step_constructor_and_description($conf);

# Mock values for OS and C-compiler
my ($osname, $cc, $initial_value);
$osname = 'mswin32';
$cc = 'gcc';
$initial_value = $conf->data->get( 'libs' );
ok($step->_add_to_libs( {
    conf            => $conf,
    osname          => $osname,
    cc              => $cc,
    win32_gcc       => '-lintl',
    win32_nongcc    => 'intl.lib',
    default         => defined $conf->data->get('glibc') ? '' : '-lintl',
} ),
    "_add_to_libs() returned true value");
like($conf->data->get( 'libs' ), qr/-lintl/,
    "'libs' modified as expected");
# Restore value for next test.
$conf->data->set( 'libs' => $initial_value );

$osname = 'mswin32';
$cc = 'cc';
ok($step->_add_to_libs( {
    conf            => $conf,
    osname          => $osname,
    cc              => $cc,
    win32_gcc       => '-lintl',
    win32_nongcc    => 'intl.lib',
    default         => defined $conf->data->get('glibc') ? '' : '-lintl',
} ),
    "_add_to_libs() returned true value");
like($conf->data->get( 'libs' ), qr/intl.lib/,
    "'libs' modified as expected");
# Restore value for next test.
$conf->data->set( 'libs' => $initial_value );

$osname = 'foobar';
$cc = 'cc';
$conf->data->set( glibc => 1 );
ok($step->_add_to_libs( {
    conf            => $conf,
    osname          => $osname,
    cc              => $cc,
    win32_gcc       => '-lintl',
    win32_nongcc    => 'intl.lib',
    default         => defined $conf->data->get('glibc') ? '' : '-lintl',
} ),
    "_add_to_libs() returned true value");
unlike($conf->data->get( 'libs' ), qr/-lintl/,
    "'libs' modified as expected");
# Restore value for next test.
$conf->data->set( 'libs' => $initial_value );

$osname = 'foobar';
$cc = 'cc';
$conf->data->set( glibc => undef );
ok($step->_add_to_libs( {
    conf            => $conf,
    osname          => $osname,
    cc              => $cc,
    win32_gcc       => '-lintl',
    win32_nongcc    => 'intl.lib',
    default         => defined $conf->data->get('glibc') ? '' : '-lintl',
} ),
    "_add_to_libs() returned true value");
like($conf->data->get( 'libs' ), qr/-lintl/,
    "'libs' modified as expected");

########## _evaluate_cc_run() ##########

my ($test, $verbose);
my $has_gettext;

$test = "Hello, world!\n";
$verbose = undef;
$has_gettext = $step->_evaluate_cc_run($test, $verbose);
is($has_gettext, 1, "Got expected value for has_gettext");
is($step->result(), 'yes', "Expected result was set");
# Prepare for next test
$step->set_result(undef);

{
    my $stdout;
    $test = "Hello, world!\n";
    $verbose = 1;
    capture(
        sub {
            $has_gettext = $step->_evaluate_cc_run($test, $verbose);
        },
        \$stdout,
    );
    is($has_gettext, 1, "Got expected value for has_gettext");
    is($step->result(), 'yes', "Expected result was set");
    like($stdout, qr/\(yes\)/, "Got expected verbose output");
    # Prepare for next test
    $step->set_result(undef);
}

$test = "Foobar\n";
$verbose = undef;
$has_gettext = $step->_evaluate_cc_run($test, $verbose);
is($has_gettext, 0, "Got expected value for has_gettext");
ok(! defined $step->result(), "As expected, result is not yet defined");

$conf->replenish($serialized);

########## --without-gettext; _handle_gettext() ##########

$args = process_options( {
    argv => [ q{--without-gettext} ],
    mode => q{configure},
} );
$conf->options->set( %{$args} );
$step = test_step_constructor_and_description($conf);

$verbose = undef;
$conf->data->set( ccflags => q{} );
ok(auto::gettext::_handle_gettext($conf, $verbose),
    "_handle_gettext() returned true value");
like($conf->data->get( 'ccflags' ), qr/-DHAS_GETTEXT/,
    "HAS_GETTEXT was added to 'ccflags'");

{
    my ($stdout, $rv);
    $verbose = 1;
    capture(
        sub { $rv = auto::gettext::_handle_gettext($conf, $verbose); },
        \$stdout,
    );
    ok($rv, "_handle_gettext() returned true value");
    like($conf->data->get( 'ccflags' ), qr/-DHAS_GETTEXT/,
        "HAS_GETTEXT was added to 'ccflags'");
    like($stdout,
        qr/ccflags:\s.*-DHAS_GETTEXT/,
        "Got expected verbose output"
    );
}

pass("Completed all tests in $0");

################### DOCUMENTATION ###################

=head1 NAME

auto_gettext-01.t - test auto::gettext

=head1 SYNOPSIS

    % prove t/steps/auto_gettext-01.t

=head1 DESCRIPTION

The files in this directory test functionality used by F<Configure.pl>.

The tests in this file test auto::gettext.

=head1 AUTHOR

James E Keenan

=head1 SEE ALSO

config::auto::gettext, F<Configure.pl>.

=cut

# Local Variables:
#   mode: cperl
#   cperl-indent-level: 4
#   fill-column: 100
# End:
# vim: expandtab shiftwidth=4:
