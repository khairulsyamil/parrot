#!/usr/bin/perl
# Copyright (C) 2008, The Perl Foundation.
# $Id: 03-boolean.t 33314 2008-11-28 16:28:50Z bernhard $

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/../../../../lib", "$FindBin::Bin/../../lib";

use Parrot::Test tests => 3;

language_output_is( 'JS', <<'CODE', <<'OUT', 'empty object', todo => 'toString broken' );
var a = {};
print(a);
CODE
[object Object]
OUT

language_output_is( 'JS', <<'CODE', <<'OUT', 'object with primitive fields', todo => 'fields broken' );
var a = { 0: 1, 1: 2, };
print(a);
CODE
[object Object]
OUT

language_output_is( 'JS', <<'CODE', <<'OUT', 'nested objects', todo => 'fields broken' );
var a = { a: { aa: "duh" },
          b: { bb: "huh" },
          c: { cc: "wuh" },
          };
print(a);
CODE
[object Object]
OUT

# Local Variables:
#   mode: cperl
#   cperl-indent-level: 4
#   fill-column: 100
# End:
# vim: expandtab shiftwidth=4:

