## $Id$

=head1 TITLE

Bool - Perl 6 boolean class

=head1 DESCRIPTION

This file sets up the Perl 6 C<Bool> class, and initializes
symbols for C<Bool::True> and C<Bool::False>.

=cut

.namespace ['Bool']

.sub 'onload' :anon :init :load
    .local pmc p6meta, boolproto
    p6meta = get_hll_global ['Perl6Object'], '$!P6META'
    boolproto = p6meta.'new_class'('Bool', 'parent'=>'Boolean Any')
    p6meta.'register'('Boolean', 'parent'=>boolproto, 'protoobject'=>boolproto)

    $P0 = boolproto.'new'()
    $P0 = 0
    set_hll_global ['Bool'], 'False', $P0

    $P0 = boolproto.'new'()
    $P0 = 1
    set_hll_global ['Bool'], 'True', $P0
.end


=item Scalar

This is a value type, so just returns itself.

=cut

.sub 'Scalar' :method
    .return (self)
.end


.sub 'ACCEPTS' :method
    .param pmc topic
    .return (self)
.end


.sub 'perl' :method
    if self goto false
    .return ('Bool::False')
  false:
    .return ('Bool::True')
.end


.sub 'succ' :method :vtable('increment')
    self = 1
.end


.sub 'pred' :method :vtable('decrement')
    self = 0
.end

=item

Bool.pick - returns True or False

=cut

.sub 'pick' :method
    .local pmc rand
    rand = get_hll_global ['Any'], '$!random'
    $N0 = rand
    if $N0 < 0.5 goto ret_true
    $P0 = get_hll_global ['Bool'], 'False'
    goto done
  ret_true:
    $P0 = get_hll_global ['Bool'], 'True'
  done:
    .tailcall 'list'($P0)
.end


# Local Variables:
#   mode: pir
#   fill-column: 100
# End:
# vim: expandtab shiftwidth=4 ft=pir:
