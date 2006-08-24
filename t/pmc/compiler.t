#!perl
# Copyright (C) 2006, The Perl Foundation.
# $Id$

use strict;
use warnings;
use lib qw( . lib ../lib ../../lib );
use Test::More;
use Parrot::Test tests => 1;

=head1 NAME

t/pmc/compiler.t - test Compiler PMC


=head1 SYNOPSIS

	% prove t/pmc/compiler.t

=head1 DESCRIPTION

Tests the Compiler PMC.

=cut


pir_output_is(<<'CODE', <<'OUT', 'new');
.sub 'test' :main
	new P0, .Compiler
	print "ok 1\n"
.end
CODE
ok 1
OUT


