# $Id$
# Copyright (C) 2009, Parrot Foundation.

=head1 Builtins

Variour helper builtins.

=cut
.namespace []

.sub 'uc'
    .param string arg
    $S0 = upcase arg
    .return ($S0)
.end

.sub 'join'
    .param string joiner
    .param pmc args

    unless args goto done
    $S0 = join joiner, args
  done:
    .return ($S0)
.end

.sub 'defined'
    .param pmc thing
    $I0 = defined thing
    .return ($I0)
.end

.sub 'exists'
    .param pmc where
    .param pmc what
    $I0 = exists where[what]
    .return ($I0)
.end

.sub 'clone'
    .param pmc what
    $P0 = clone what
    .return ($P0)
.end

.sub 'substr'
    .param string orig
    .param int    from
    .param int    len
    $S0 = substr orig, from, len
    .return ($S0)
.end


# Extend various Parrot's PMCs to play nicely with NQP.
.namespace ['Hash']

.sub 'keys' :method
    .local pmc res, it
    res = new 'ResizableStringArray'
    it = iter self
  loop:
    unless it goto done
    $P0 = shift it
    $S0 = $P0
    say $S0
    push res, $S0
    goto loop
  done:

    .return(res)

.end

# Local Variables:
#   mode: pir
#   fill-column: 100
# End:
# vim: expandtab shiftwidth=4 ft=pir:
