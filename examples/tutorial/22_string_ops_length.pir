=head1 String Operations (continued)

To find the length of a string in PIR, use the length function.

=cut


.sub main :main

    $S0 = "Hello"
    $I0 = length $S0
    print $I0
    print "\n"

.end

# Local Variables:
#   mode: pir
#   fill-column: 100
# End:
# vim: expandtab shiftwidth=4:

