# Copyright (C) 2008, The Perl Foundation.
# $Id$

=head1 NAME

namespace.t - testing packages, aka namespaces

=head1 DESCRIPTION

Working with namespaces.

=cut

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/../../../../lib", "$FindBin::Bin/../../lib";

use Parrot::Test tests => 1;

language_output_is( 'Pipp', <<'CODE', <<'OUT', 'namespace with dummy class', todo => 'no implemented yet' );
<?php

namespace A::B;

class Dings {
    
    function bums() {
        echo "The function bums() in class A::Dings has been called.\n";
    }
}
 
$dings = new A::Dings;
$dings->bums();
 
?>
CODE
The function bums() in class A::Dings has been called.
OUT
