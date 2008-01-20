## $Id$

=head1 NAME

src/classes/List.pir - Perl 6 List class

=head1 Methods

=over 4

=cut

.namespace ['List']

.sub 'onload' :anon :load :init
    $P0 = subclass 'ResizablePMCArray', 'List'
    $P1 = get_hll_global ['Perl6Object'], 'make_proto'
    $P1($P0, 'List')
.end


=item get_string()    (vtable method)

Return the elements of the list joined by spaces.

=cut

.sub 'get_string' :vtable :method
    $S0 = join ' ', self
    .return ($S0)
.end


=item elems()

Return the number of elements in the list.

=cut

.sub 'elems' :method
    $I0 = elements self
    .return ($I0)
.end

=item unshift(ELEMENTS)

Prepends ELEMENTS to the front of the list.

=cut

.sub 'unshift' :method
    .param pmc args :slurpy
    .local int narg
    .local int i

    narg = args
    i = 0

    .local pmc tmp
  loop:
    if i == narg goto done
    pop tmp, args
    unshift self, tmp
    inc i
    goto loop
  done:	
.end

=item keys()

Returns a List containing the keys of the List.

=cut

.sub 'keys' :method
    .local pmc elem
    .local pmc res
    .local int len
    .local int i
	
    res = new 'List'
    len = elements self
    i = 0
	
  loop:
    if i == len goto done

    elem = new Integer
    elem = i
    res.'push'(elem)

    inc i
    goto loop
	
  done:	
    .return(res)
.end

=item values()

Returns a List containing the values of the List.

=cut

.sub 'values' :method
    .local pmc elem
    .local pmc res
    .local int len
    .local int i
	
    res = new 'List'
    len = elements self
    i = 0
	
  loop:
    if i == len goto done

    elem = new Integer
    elem = self[i]
    res.'push'(elem)

    inc i
    goto loop
	
  done:	
    .return(res)
.end

=item shift()

Shifts the first item off the list and returns it.

=cut

.sub 'shift' :method
    .local pmc x
    x = shift self
    .return (x)
.end

=item pop()

Treats the list as a stack, popping the last item off the list and returning it.

=cut

.sub 'pop' :method
    .local pmc x
    .local int len

    len = elements self

    if len == 0 goto empty
    pop x, self
    goto done
    
  empty:
    x = undef()
    goto done

  done:	
    .return (x)
.end

=item push(ELEMENTS)

Treats the list as a stack, pushing ELEMENTS onto the end of the list.  Returns the new length of the list.

=cut

.sub 'push' :method
    .param pmc args :slurpy
    .local int len
    .local pmc tmp
    .local int i

    len = args
    i = 0

  loop:
    if i == len goto done
    shift tmp, args
    push self, tmp
    inc i
    goto loop
  done:
    len = elements self
    .return (len)
.end

=item join(SEPARATOR)

Returns a string comprised of all of the list, separated by the string SEPARATOR.  Given an empty list, join returns the empty string.

=cut

.sub 'join' :method
    .param string sep
    .local string res
    .local string tmp
    .local int len
    .local int i
	
    res = ""

    len = elements self
    if len == 0 goto done

    len = len - 1
    i = 0

  loop:
    if i == len goto last

    tmp = self[i]
    concat res, tmp
    concat res, sep
    
    inc i
    goto loop

  last:
    tmp = self[i]
    concat res, tmp
  
  done:
    .return(res)	
.end

=item reverse()

Returns a list of the elements in revese order.

=cut

.sub 'reverse' :method
    .local pmc res
    .local int len
    .local int i
    
    res = new 'List'

    len = elements self
    if len == 0 goto done
    i = 0

    .local pmc elem
loop:
    if len == 0 goto done

    dec len
    elem = self[len]
    res[i] = elem
    inc i
    
    goto loop

done:	
    .return(res)
.end

=item delete()

Deletes the given elements from the List, replacing them with Undef.  Returns a List of removed elements.

=cut

.sub delete :method
    .param pmc indices :slurpy
    .local pmc newelem
    .local pmc elem
    .local int last
    .local pmc res
    .local int ind
    .local int len
    .local int i

    newelem = undef()
    res = new 'List'

    # Index of the last element in the array
    last = elements self
    dec last

    len = elements indices
    i = 0

  loop:
    if i == len goto done

    ind = indices[i]

    if ind == -1 goto endofarray
    if ind == last goto endofarray
    goto restofarray
    
  endofarray:
    # If we're at the end of the array, remove the element entirely
    elem = pop self
    res.push(elem)
    goto next
    
  restofarray:	
    # Replace the element with undef.
    elem = self[ind]
    res.push(elem)

    self[ind] = newelem
    
  next:	
    inc i
    goto loop
  done:	
    .return(res)
.end

=item exists(INDEX)

Checks to see if the specified index or indices have been assigned to.  Returns a Bool value.

=cut

.sub exists :method
    .param pmc indices :slurpy
    .local int test
    .local int len
    .local pmc res
    .local int ind
    .local int i

    len = elements indices
    i = 0
      
  loop:
    if i == len goto true

    ind = indices[i]   

    test = exists self[ind]
    if test == 0 goto false
    
    inc i
    goto loop
    
  true:
    res = get_hll_global ['Bool'], 'True'
    goto done
    
  false:
    res = get_hll_global ['Bool'], 'False'
    goto done
    
  done:	
    .return(res)
.end

=item kv()

=cut

.sub kv :method
    .local pmc elem
    .local pmc res
    .local int len
    .local int i
    
    res = new 'List'
    len = elements self
    i = 0
    
  loop:
    if i == len goto done

    elem = new Integer
    elem = i
    res.'push'(elem)

    elem = self[i]
    res.'push'(elem)
    
    inc i
    goto loop
    
  done:	
    .return(res)
.end

=back

=cut

# Local Variables:
#   mode: pir
#   fill-column: 100
# End:
# vim: expandtab shiftwidth=4:
