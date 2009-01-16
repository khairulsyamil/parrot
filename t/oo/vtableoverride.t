#! parrot
# Copyright (C) 2007, The Perl Foundation.
# $Id$

=head1 NAME

t/oo/vtableoverride.t - test various vtable overrides from PIR

=head1 SYNOPSIS

    % prove t/oo/vtableoverride.t

=head1 DESCRIPTION

Tests the behavior of VTABLE interfaces that have been overriden from PIR.

=cut

.sub main :main
    .include 'test_more.pir'
    plan(4)
    
    $P1 = new 'MyObject'
    
    # Test get_string
    $S0 = $P1
    is($S0, "[MyObject]", "get_string VTABLE override")
    $P0 = getattribute $P1, "message"
    $S0 = $P0
    is($S0, "[MyObject]", "attribute sideeffect of get_string")
    
    # Test morph (doesn't actually perform a morph)
    morph $P1, "String"
    $P0 = getattribute $P1, "message"
    $S0 = $P0
    is($S0, "Morphing [MyObject] to type String", "Morph VTABLE override 1")
    
    morph $P1, "Integer"
    $P0 = getattribute $P1, "message"
    $S0 = $P0
    is($S0, "Morphing [MyObject] to type Integer", "Morph VTABLE override 1")
.end

.namespace [ 'MyObject' ]

.sub '__onload' :anon :init
    $P0 = newclass "MyObject"
    addattribute $P0, "message"
.end

.sub 'get_string' :vtable
    $S0 = "[MyObject]"
    $P0 = box $S0
    setattribute self, "message", $P0
    .return($S0)
.end

.sub 'morph' :vtable
    .param pmc class
    .local string type
    $S0 = self
    $S1 = "Morphing " . $S0
    $S1 = $S1 . " to type "
    type = class.'name'()
    $S1 = $S1 . type
    $P0 = box $S1
    setattribute self, "message", $P0
.end
    

# Local Variables:
#   mode: pir
#   fill-column: 100
# End:
# vim: expandtab shiftwidth=4 ft=pir:
