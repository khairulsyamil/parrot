## $Id$

=head1 TITLE

Signature - Perl 6 Signature class

=head1 DESCRIPTION

This file sets up the Perl 6 C<Signature> class.

=head1 GUTS

This class will evolve over time as we understand signatures and how we will
expose there insides better. For now, a signature under the hood is just an
array of hashes, with each hash being a "descriptor" for something that is
bindable. Its keys are as follows.

* name - string holding the name of the thing we're binding to, if any
* type - the class or role type of the parameter; this references the actual
  type object rather than just naming it, and may well be parametric (but that
  will have been resolved already)
* constraints - any additional "where" refinement types on the parameter;
  will be a junction of types
* invocant - is this the invocant (as in, self for a method, not multi)
* multi_invocant - is this an invocant for the purpose of MMD
* optional - is this an optional parameter?
* slurpy - is this a slurpy parameter?

Again, this probably isn't definitive either, but it'll get us going.

=cut

.namespace ['Signature']

.sub 'onload' :anon :init :load
    load_bytecode 'PCT.pbc'
    .local pmc p6meta
    p6meta = get_hll_global ['Perl6Object'], '$!P6META'
    p6meta.'new_class'('Signature', 'parent'=>'Any', 'attr'=>'@!params')
.end

=head2 Methods

=over 4

=item !create

Used to create a new signature object with the given paramter descriptors. The
constraints entry that we actually get passed in here contains both class, role
and subset types; we separate them out in here. At some point in the future, we
should be smart enough to do this at compile time.

=cut

.sub '!create' :method
    .param pmc parameters :slurpy

    # Iterate over parameters.
    .local pmc param_iter, cur_param
    param_iter = iter parameters
  param_loop:
    unless param_iter goto param_loop_end
    cur_param = shift param_iter

    # Get constraints list, which may have class and role types as well as
    # subset types. If we have no unique role or class type, they all become
    # constraints; otherwise, we find the unique type. Finally, we turn the
    # list of constraints into a junction.
    .local pmc cur_list, cur_list_iter, constraints, type, test_item
    constraints = 'list'()
    type = null
    cur_list = cur_param["constraints"]
    cur_list_iter = iter cur_list

  cur_list_loop:
    unless cur_list_iter goto cur_list_loop_end
    test_item = shift cur_list_iter
    $I0 = isa test_item, "Role"
    if $I0 goto is_type
    $P0 = getprop "subtype_realtype", test_item
    if null $P0 goto not_refinement
    unless null type goto all_constraints
    type = $P0
    push constraints, test_item
    goto cur_list_loop
  not_refinement:
    $I0 = isa test_item, "P6protoobject"
    if $I0 goto is_type
    push constraints, test_item
    goto cur_list_loop
  is_type:
    unless null type goto all_constraints
    type = test_item
    goto cur_list_loop
  all_constraints:
    type = null
    constraints = cur_list
  cur_list_loop_end:
    unless null type goto have_type
    type = get_hll_global 'Any'
  have_type:
    cur_param["type"] = type
    $I0 = elements constraints
    if $I0 == 0 goto no_constraints
    constraints = 'all'(constraints)
    goto set_constraints
  no_constraints:
    constraints = null
  set_constraints:
    cur_param["constraints"] = constraints

    goto param_loop
  param_loop_end:

    $P0 = self.'new'()
    setattribute $P0, '@!params', parameters
    .return ($P0)
.end

=item params

Get the array of parameter describing hashes.

=cut

.sub 'params' :method
    $P0 = getattribute self, "@!params"
    .return ($P0)
.end

=item perl

Gets a perl representation of the signature.

=cut

.sub 'perl' :method
    .local pmc s
    s = new 'Perl6Str'
    concat s, ':('

    # Output parameters.
    .local pmc params, param_iter, cur_param
    .local int last_was_multi_inv, want_colon, first
    last_was_multi_inv = 1
    want_colon = 0
    first = 1
    params = self.'params'()
    param_iter = iter params
  param_iter_loop:
    unless param_iter goto param_iter_loop_end
    cur_param = shift param_iter

    # If it's the first time, no separator.
    if first goto first_time
    if want_colon goto emit_colon
    $P0 = cur_param["multi_invocant"]
    if $P0 goto emit_comma
    unless last_was_multi_inv goto emit_comma
    concat s, ';; '
    last_was_multi_inv = 0
    goto separator_done
  emit_comma:
    concat s, ', '
    goto separator_done
  emit_colon:
    concat s, ': '
    goto separator_done
  first_time:
    first = 0
  separator_done:

    # First any nominal type.
    $P0 = cur_param["type"]
    if null $P0 goto any_type
    $P0 = $P0.'perl'()
    concat s, $P0
    goto type_done
  any_type:
    concat s, "Any"
  type_done:
    concat s, " "

    # If it's slurpy, the *.
    $P0 = cur_param["slurpy"]
    if null $P0 goto slurpy_done
    unless $P0 goto slurpy_done
    concat s, '*'
  slurpy_done:

    # Now the name.
    $P0 = cur_param["name"]
    concat s, $P0

    # If it's optional, the ?.
    $P0 = cur_param["optional"]
    if null $P0 goto optional_done
    unless $P0 goto optional_done
    concat s, '?'
  optional_done:

    # Now any constraints.
    $P0 = cur_param["constraints"]
    if null $P0 goto constraints_done
    unless $P0 goto constraints_done
    concat s, " where "
    $P0 = $P0.'perl'()
    concat s, $P0
  constraints_done:

    goto param_iter_loop
  param_iter_loop_end:

    # If we just had an invocant, need the colon.
    unless want_colon goto no_trailing_colon
    concat s, ':'
  no_trailing_colon:

    # XXX TODO: Return type, once we support those.

    # Done.
    concat s, ')'
    .return (s)
.end

=back

=cut

# Local Variables:
#   mode: pir
#   fill-column: 100
# End:
# vim: expandtab shiftwidth=4 ft=pir:
