#!perl

# Copyright (C) 2006, The Perl Foundation.
# $Id$

use strict;
use warnings;
use lib qw(tcl/lib ./lib ../lib ../../lib ../../../lib);

use Parrot::Test tests => 2;
use Test::More;
use File::Spec;

language_output_is( "tcl", <<'TCL', <<OUT, "pwd too many args" );
 pwd fish
TCL
wrong # args: should be "pwd"
OUT

use Cwd;
my $dir = File::Spec->canonpath( getcwd );

language_output_is( "tcl", <<'TCL', <<"OUT", "pwd simple" );
 puts [pwd]
TCL
$dir
OUT

# Local Variables:
#   mode: cperl
#   cperl-indent-level: 4
#   fill-column: 100
# End:
# vim: expandtab shiftwidth=4:
