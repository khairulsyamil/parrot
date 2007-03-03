=head1 TclProc

A .Sub with attributes

=cut

.include "languages/tcl/src/returncodes.pir"
.include "languages/tcl/src/macros.pir"

.HLL 'parrot', ''
.namespace [ 'TclProc' ]

.cloneable()

=head2 __class_init

Define the attributes required for the class.

=cut

.sub __class_init :load

  $P0 = getclass 'Sub'
  $P1 = subclass $P0, 'TclProc'

  addattribute $P1, 'PIR_source'
  addattribute $P1, 'namespace'
  addattribute $P1, 'HLL'         # In our case, Tcl...
  addattribute $P1, 'HLL_source'
  addattribute $P1, 'args'
  addattribute $P1, 'defaults'    # Should combine this with 'args' for a more Perl-sixy way of specifying args.
.end
