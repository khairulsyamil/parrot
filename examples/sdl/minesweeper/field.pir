# $Id$

=head1 NAME

Mines::Field - A minesweeper field

=head1 SYNOPSIS

    # setup field properties
    $P0 = new 'Hash'
    $P0['width']  = 40
    $P0['height'] = 28
    $P0['mines']  = 0.1075
    $P0['level']  = 123
    $P0['screen'] = screen
    $P0['debug']  = debug

    # create the field
    field = new "Mines::Field", $P0

    # draw the field
    field.'draw'()

=head1 DESCRIPTION

This is an implementation of a Minesweeper game field.
It draws the field onto a SDL surface.

=head1 METHODS

An Mines::Field object has the following methods:

=over 4

=cut

.include "iterator.pasm"
.namespace ["Mines::Field"]

# size of a single mine field, in pixels
.const int FIELD_WIDTH  = 16
.const int FIELD_HEIGHT = 16

# mine field values
.const int VAL_INVALID            = -1
.const int VAL_FREE               =  0
.const int VAL_1                  =  1
.const int VAL_2                  =  2
.const int VAL_3                  =  3
.const int VAL_4                  =  4
.const int VAL_5                  =  5
.const int VAL_6                  =  6
.const int VAL_7                  =  7
.const int VAL_8                  =  8
.const int VAL_MINE_EXPLODED      =  9
.const int VAL_NO_MINE            = 10
.const int VAL_MINE               = 11
.const int VAL_FLAG_NO_MINE       = 12
.const int VAL_FLAG_MINE          = 13
.const int VAL_UNSURE_NO_MINE     = 14
.const int VAL_UNSURE_MINE        = 15
.const int VAL_UNEXPLORED_NO_MINE = 16
.const int VAL_UNEXPLORED_MINE    = 17
.const int VAL_MARK_NO_MINE       = 18
.const int VAL_MARK_MINE          = 19

# game status
.const int STATUS_PLAYING  = 0
.const int STATUS_CHOOSING = 1
.const int STATUS_LOST     = 2
.const int STATUS_SLEEPING = 3
.const int STATUS_WON      = 4


=item __init( hash )

The constructor. You have to pass a hash filled with
the following values:

=over 4

=item width

Number of horizontal units the field should have.

=item height

Number of vertical units the field should have.

=item level

Initial seed for the PRNG that is used to calculate the field.

=item mines

The amount of mines. 0.0 means no mines, 1.0 means mines everywhere.

=item screen

SDL surface to use for drawing.

=item debug

0 = normal mode
1 = use debug image (position of mines are visible)

=back

=cut

.sub __init :method
    .param pmc args
    .local pmc field
    .local pmc screen
    .local pmc cache
    .local int width
    .local int height
    .local int level
    .local num mines
    .local int val
    .local int debug
    .local pmc lcd
    .local pmc watch

    # get the arguments
    width  = args['width']
    height = args['height']
    level  = args['level']
    mines  = args['mines']
    screen = args['screen']
    debug  = args['debug']
    field  = new 'ResizablePMCArray'
    cache  = new 'ResizablePMCArray'

    watch = new ['SDL'; 'StopWatch'], screen
    watch.'xpos'( 515 )
    watch.'ypos'( 5 )

    lcd = new ['SDL'; 'LCD']
    # This seems to call __init() with too many parameters
    # lcd = 0
    lcd.'_digits'( 4 )
    lcd.'xpos'( 5 )
    lcd.'ypos'( 5 )

    setattribute self, 'field', field
    setattribute self, 'cache', cache
    setattribute self, 'screen', screen
    setattribute self, 'mines_lcd', lcd
    setattribute self, 'watch', watch

    $P0 = new 'Integer'
    $P0 = width
    setattribute self, 'width', $P0

    $P0 = new 'Integer'
    $P0 = height
    setattribute self, 'height', $P0

    $P0 = new 'Float'
    $P0 = mines
    setattribute self, 'mines', $P0

    $P0 = new 'Integer'
    $P0 = -1
    setattribute self, 'markpos', $P0

    $P0 = new 'Integer'
    $P0 = debug
    setattribute self, 'debug', $P0

    # button
    $P0 = new 'String'
    $P0 = "examples/sdl/minesweeper/smiley.png"
    $P0 = new ['SDL'; 'Button'], $P0
    $P0.'states'( 5 )
    $P0.'pos'( 305, 2 )
    $P0.'size'( 30, 30 )

    $P1 = get_hll_global [ 'Mines::Field' ], '_button_clicked'
    $P0.'setAction'( STATUS_PLAYING, $P1 )
    $P0.'setAction'( STATUS_WON, $P1 )
    $P0.'setAction'( STATUS_LOST, $P1 )

    setattribute self, 'status_button', $P0

    self.'newLevel'( level )
.end

=item newLevel( level )

Creates a new level, with the given number as initial seed for the PRNG.

=cut

.sub newLevel :method
    .param int level
    .local pmc field
    .local pmc cache
    .local int size
    .local int width
    .local int height
    .local int val
    .local num mines

    field  = getattribute self, 'field'
    cache  = getattribute self, 'cache'

    $P0    = getattribute self, 'witdh'
    width  = $P0

    $P0    = getattribute self, 'height'
    height = $P0

    $P0    = getattribute self, 'mines'
    mines  = $P0

    size   = width * height

    field  = 0
    cache  = 0

    # fill the field
LOOP:
    level += size

    $I0 = level
    shl $I0, 13
    $I0 = or $I0, level

    $I1 = $I0 * $I0
    $I1 *= 15731
    $I1 += 789221

    $I1 *= $I0
    $I1 += 1376312589

    $N0 = $I1
    $N0 = $N0 / 1073741824.0
    $N0 = 100.0 + $N0
    $N0 *= 100.0
    $I0 = $N0
    $N0 = $N0 - $I0
    level += $I0

    val = VAL_UNEXPLORED_NO_MINE
    ge $N0, mines, NO_MINE
    val = VAL_UNEXPLORED_MINE
NO_MINE:

    push field, val
    push cache, VAL_INVALID

    dec size
    if size <= 0 goto END
    branch LOOP
END:
    # set the game status
    self.'setStatus'( STATUS_PLAYING )
    # reset the watch
    $P0 = getattribute self, "Mines::Field\x0watch"
    $P0.'reset'()
.end

=item draw()

Draws the field, then the LCDs and the smiley button.

=cut

.sub draw :method
    .local pmc screen
    .local pmc image
    .local pmc dest_rect
    .local pmc src_rect
    .local int width
    .local int height
    .local int size
    .local int i
    .local pmc field
    .local pmc cache
    .local pmc cacheit
    .local int debug
    .local int minx
    .local int miny
    .local int maxx
    .local int maxy
    .local pmc mines_lcd
    .local pmc watch
    .local pmc status

    getattribute field, self, 'field'
    field   = iter field
    field   = .ITERATE_FROM_START

    cache   = getattribute self, 'cache'
    cacheit = iter cache
    cacheit = .ITERATE_FROM_START

    screen  = getattribute self, 'screen'

    $P0     = getattribute self, 'width'
    width   = $P0

    $P0     = getattribute self, 'height'
    height  = $P0

    $P0     = getattribute self, 'debug'
    debug   = $P0

    minx    = width  * FIELD_WIDTH
    miny    = height * FIELD_HEIGHT
    maxx    = 0
    maxy    = 0

    if debug goto DEBUG
    image = get_hll_global [ "Mines::Field" ], "field"
    branch IMAGE_OK
DEBUG:
    image = get_hll_global [ "Mines::Field" ], "field_debug"
IMAGE_OK:
    $P0 = new 'Hash'
    $P0['x'] = 0
    $P0['y'] = 0
    $P0['width']  = 0
    $P0['height'] = 0
    dest_rect = new ['SDL'; 'Rect'], $P0
    $P0['width']  = FIELD_WIDTH
    $P0['height'] = FIELD_HEIGHT
    src_rect = new ['SDL'; 'Rect'], $P0

    set size, width
    mul size, height

    i = 0
LOOP:
    if i >= size goto END

    $P0 = shift field
    $I0 = $P0
    $P0 = shift cacheit
    $I1 = $P0

    # current field already drawn?
    if $I0 == $I1 goto NEXT

    cache[i] = $I0

    $I1 = cmod i, width
    $I2 = div i, width

    mul $I1, FIELD_WIDTH
    mul $I2, FIELD_HEIGHT

    add $I1, 0
    add $I2, 32

    dest_rect.'x'( $I1 )
    dest_rect.'y'( $I2 )

    if $I1 > minx goto SKIP1
    minx = $I1
SKIP1:

    if $I2 > miny goto SKIP2
    miny = $I2
SKIP2:

    if $I1 < maxx goto SKIP3
    maxx = $I1
SKIP3:

    if $I2 < maxy goto SKIP4
    maxy = $I2
SKIP4:

    $I1 = cmod $I0, 5
    $I2 = div $I0, 5

    mul $I1, FIELD_WIDTH
    mul $I2, FIELD_HEIGHT

    src_rect.'x'( $I1 )
    src_rect.'y'( $I2 )

    screen.'blit'( image, src_rect, dest_rect )
NEXT:
    inc i
    branch LOOP
END:

    add maxx, FIELD_WIDTH
    add maxy, FIELD_HEIGHT

    if maxx <= minx goto NO_SCREEN_UPDATE
    if maxy <= miny goto NO_SCREEN_UPDATE

    dest_rect.'x'( minx )
    dest_rect.'y'( miny )
    $I0 = maxx - minx
    dest_rect.'width'( $I0 )
    $I0 = maxy - miny
    dest_rect.'height'( $I0 )

    screen.'update_rect'( dest_rect )
NO_SCREEN_UPDATE:

    # update the LCDs
    self.'update_stats'()

    $P0 = getattribute self, "Mines::Field\x0mines_lcd"
    $P0.'draw'( screen )

    $P0 = getattribute self, "Mines::Field\x0watch"
    $P0.'draw'( screen )

    $P0 = getattribute self, "Mines::Field\x0status_button"
    $P0.'draw'( screen )
.end

=item reveal( x, y )

Reveals the field at the specified location.

Returns 1 if successful, 0 otherwise.

=cut

.sub reveal :method
    .param int x
    .param int y
    .local int width
    .local int height
    .local pmc watch

    self."undo_mark"()

    $P0    = getattribute self, 'width'
    width  = $P0

    $P0    = getattribute self, 'height'
    height = $P0

    watch  = getattribute self, 'watch'

    $P0    = getattribute self, 'status'
    if $P0 > STATUS_CHOOSING goto END

    x -= 0
    y -= 32

    if x < 0 goto END
    if y < 0 goto END

    x /= FIELD_WIDTH
    y /= FIELD_HEIGHT

    watch.'start'()
    self.'reveal_recursive'( x, y, width, height )
    self.'check_end'()
    self.'draw'()

    .return (1)

END:
    .return (0)
.end

=item setFlag( x, y )

Sets a flag at the specified location.

Returns 1 if successful, 0 otherwise.

=cut

.sub setFlag :method
    .param int x
    .param int y
    .local int width
    .local pmc field
    .local pmc watch
    .local int pos
    .local int v

    self."undo_mark"()

    $P0   = getattribute self, 'field'
    field = $P0

    $P0   = getattribute self, 'width'
    width = $P0

    watch = getattribute self, 'watch'

    $P0   = getattribute self, 'status'
    if $P0 > STATUS_CHOOSING goto END

    x -= 0
    y -= 32

    if x < 0 goto END
    if y < 0 goto END

    x /= FIELD_WIDTH
    y /= FIELD_HEIGHT

    pos = y * width
    pos += x

    v = field[pos]

    if v == VAL_FLAG_NO_MINE       goto PLUS2
    if v == VAL_FLAG_MINE          goto PLUS2
    if v == VAL_UNSURE_NO_MINE     goto PLUS2
    if v == VAL_UNSURE_MINE        goto PLUS2
    if v == VAL_UNEXPLORED_NO_MINE goto MINUS4
    if v == VAL_UNEXPLORED_MINE    goto MINUS4
    branch END

PLUS2:
    v += 2
    branch DRAW

MINUS4:
    v -= 4

DRAW:
    field[pos] = v

    watch.'start'()
    self."check_end"()
    self."draw"()

    .return (1)

END:
    .return (0)
.end

=item undo_mark( i ) B<(internal)>

Removes the field mark.

Parameters:

=over 4

=item i

Optional. The value does not matter. If you pass an integer value,
the game status is not set. If you pass no integer, the game status
will be set.

Just do not pass an integer, it is for internal use only.
(C<setStatus()> calls undo_mark, which in turn calls setStatus; this
argument is used to avoid recursion)

=back

This method returns nothing.

=cut

.sub undo_mark :method
    .param int i      :optional
    .param int has_i  :opt_flag

    .local pmc markpos
    .local pmc field
    .local pmc status

    $P0     = getattribute self, 'field'
    field   = $P0

    markpos = getattribute self, 'markpos'
    status  = getattribute self, 'status'

    $I0     = markpos

    if $I0 == -1 goto UNDO_DONE
    $I1 = field[$I0]
    $I1 -= 2
    field[$I0] = $I1
UNDO_DONE:
    markpos = -1

    if has_i goto END
    if status != STATUS_CHOOSING goto END
    self."setStatus"( STATUS_PLAYING )
END:
.end

=item mark( x, y )

Sets a mark on the specified field.
This is used to give feedback which field will be revealed.
Only one field is marked at any time, a previous mark will be
removed if you call this method.

=cut

.sub mark :method
    .param int x
    .param int y
    .local int width
    .local pmc markpos
    .local pmc field
    .local pmc watch
    .local int pos
    .local int v

    self."undo_mark"()

    $P0     = getattribute self, 'field'
    field   = $P0

    $P0     = getattribute self, 'width'
    width   = $P0

    markpos = getattribute self, 'markpos'

    x -= 0
    y -= 32

    watch = getattribute self, 'watch'

    $P0   = getattribute self, 'status'
    if $P0 >= STATUS_CHOOSING goto END

    if x < 0 goto END
    if y < 0 goto END

    x /= FIELD_WIDTH
    y /= FIELD_HEIGHT

    pos = y * width
    pos += x

    v = field[pos]

    if v == VAL_UNEXPLORED_NO_MINE goto MARK
    if v == VAL_UNEXPLORED_MINE goto MARK
    branch END
MARK:
    self."setStatus"( STATUS_CHOOSING )
    markpos = pos
    v += 2
    field[pos] = v
DRAW:
    watch.'start'()
    self."check_end"()
    self."draw"()

    .return (1)

END:
    .return (0)
.end

=item click( x, y, b )

This method is used to send mouse click events to the smiley button.

Parameters:

=over 4

=item x

The vertical mouse position.

=item y

The horizontal mouse position.

=item b

0 = mouse button not pressed

1 = mouse button pressed

=back

=cut

.sub click :method
    .param int x
    .param int y
    .param int b

    if y > 32 goto END

    $P0 = getattribute self, 'status_button'
    $I0 = $P0.'click'( x, y, b, self )
    unless $I0 goto END

    $P1 = getattribute self, 'screen'

    $P0."draw"( $P1 )
END:

.end

=item reveal_recursive( x, y, width, height ) B<(internal)>

Reveals the specified field recursively.

The width and height are the dimensions of the board, they
have to be specified for performance reasons.

=cut

.sub reveal_recursive :method
    .param int x
    .param int y
    .param int width
    .param int height
    .local pmc field
    .local int pos

    if x < 0 goto END
    if y < 0 goto END
    if x >= width goto END
    if y >= height goto END

    pos = y * width
    pos += x

    $P0   = getattribute self, 'field'
    field = $P0

    $I0 = field[pos]
    if $I0 == VAL_FREE goto END
    if $I0 == VAL_UNEXPLORED_NO_MINE goto UNEXPLORED
    if $I0 == VAL_UNEXPLORED_MINE goto UNEXPLORED_MINE
    branch END

UNEXPLORED:
    $I0 = _mines_near( field, x, y, width, height )
    field[pos] = $I0
    if $I0 != 0 goto END

    dec y
    dec x
    self.'reveal_recursive'( x, y, width, height )
    inc x
    self.'reveal_recursive'( x, y, width, height )
    inc x
    self.'reveal_recursive'( x, y, width, height )

    inc y
    dec x
    dec x
    self.'reveal_recursive'( x, y, width, height )
    inc x
    self.'reveal_recursive'( x, y, width, height )
    inc x
    self.'reveal_recursive'( x, y, width, height )

    inc y
    dec x
    dec x
    self.'reveal_recursive'( x, y, width, height )
    inc x
    self.'reveal_recursive'( x, y, width, height )
    inc x
    self.'reveal_recursive'( x, y, width, height )
    branch END

UNEXPLORED_MINE:
    field[pos] = VAL_MINE_EXPLODED
    self.'lost'()

END:
    .return ()
.end

=item lost()

Called if a mine is revealed.
Shows the position of all mines on the field.

=cut

.sub lost :method
    .local pmc field
    .local int i
    .local int max

    self."setStatus"( STATUS_LOST )

    field = getattribute self, 'field'
    max   = field
    i     = 0

LOOP:
    if i >= max goto END

    $I1 = field[i]

    if $I1 == VAL_UNEXPLORED_MINE goto MINE
    if $I1 == VAL_UNSURE_MINE goto MINE
    if $I1 == VAL_FLAG_NO_MINE goto NO_MINE
    branch NEXT

MINE:
    $I1 = VAL_MINE
    branch NEXT

NO_MINE:
    $I1 = VAL_NO_MINE
    branch NEXT

NEXT:
    field[i] = $I1
    inc i
    branch LOOP
END:
.end

=item won()

Called when you have won.

=cut

.sub won :method
    self."setStatus"( STATUS_WON )
.end

=item check_end()

Checks if you have won.

=cut

.sub check_end :method
    .local pmc field

    field = getattribute self, 'field'
    field = iter field
    field = .ITERATE_FROM_START
LOOP:
    unless field goto WON

    $I0 = shift field

    if $I0 <= 8 goto LOOP

    if $I0 == VAL_MINE goto END
    if $I0 == VAL_MINE_EXPLODED goto END
    if $I0 == VAL_UNSURE_MINE goto END
    if $I0 == VAL_FLAG_NO_MINE goto END
    if $I0 == VAL_UNEXPLORED_MINE goto END

    branch LOOP

WON:
    self."won"()
    .return (1)
END:
    .return (0)
.end

=item setStatus( newStatus )

Sets a new game status.

=cut

.sub setStatus :method
    .param int s
    .local pmc screen
    .local pmc watch
    .local pmc status

    screen = getattribute self, 'screen'
    watch  = getattribute self, 'watch'
    status = getattribute self, 'status'

    if s == STATUS_PLAYING goto OK
    if s == STATUS_CHOOSING goto OK

    # not playing at the moment, stop the watch
    watch.'stop'()
OK:
    # no need to start the watch here

    status = s
    self."undo_mark"( 1 )
    watch.'draw'( screen )

DONE:
.end

=item update_stats()

Counts the unrevealed mines and updates the LCD.

=cut

.sub update_stats :method
    .local pmc field
    .local int size
    .local pmc count
    .local pmc mines_lcd

    field     = getattribute self, 'field'
    mines_lcd = getattribute self, 'mines_lcd'

    size  = field
    field = iter field
    field = .ITERATE_FROM_START
    count = new 'ResizablePMCArray'

LOOP:
    unless field goto END
    $I0 = shift field
    $I1 = count[$I0]
    inc $I1
    count[$I0] = $I1
    branch LOOP
END:

    $I0 = count[VAL_UNEXPLORED_MINE]
    $I1 = count[VAL_UNSURE_MINE]
    $I2 = count[VAL_FLAG_NO_MINE]
    $I3 = count[VAL_MINE]
    $I4 = count[VAL_MINE_EXPLODED]
    $I5 = count[VAL_MARK_MINE]

    $I0 += $I1
    $I0 -= $I2
    $I0 += $I3
    $I0 += $I4
    $I0 += $I5
    mines_lcd = $I0
.end

=back

=head1 INTERNAL FUNCTIONS

=over 4

=item __onload()

Loads necessary modules and creates the B<Mines::Field> class.
This method is called automatically when this module is loaded.

=cut

.sub __onload :load
    .local pmc class
    class = get_class "Mines::Field"
    unless null class goto END

    .local pmc tmp
    .local pmc size
    .local pmc size_rect
    .local pmc prop
    .local pmc from_rect
    .local pmc image
    .local int rect_type
    .local int surface_type

    load_bytecode "examples/sdl/minesweeper/eventhandler.pir"
    load_bytecode "library/SDL/Button.pir"
    load_bytecode "library/SDL/StopWatch.pir"
    load_bytecode "library/SDL/Image.pir"

    # XXX: remove
    load_bytecode "library/Data/Dumper.pir"

    $P0 = new 'String'
    $P0 = "examples/sdl/minesweeper/mines.png"
    image = new ['SDL'; 'Image'], $P0
    set_hll_global [ "Mines::Field" ], "field", image

    $P0 = new 'String'
    $P0 = "examples/sdl/minesweeper/mines_debug.png"
    image = new ['SDL'; 'Image'], $P0
    set_hll_global [ "Mines::Field" ], "field_debug", image

    newclass $P0, "Mines::Field"
    addattribute $P0, 'field'
    addattribute $P0, 'cache'
    addattribute $P0, 'screen'
    addattribute $P0, 'width'
    addattribute $P0, 'height'
    addattribute $P0, 'mines'
    addattribute $P0, 'markpos'
    addattribute $P0, 'debug'
    addattribute $P0, 'mines_lcd'
    addattribute $P0, 'watch'
    addattribute $P0, 'status_button'
END:
.end

=item _mines_near( field, x, y, width, height )

Returns the number of mines in the neighbourhood
of the field at the specified location.

The width and height are the dimensions of the board.

=cut

.sub _mines_near
    .param pmc field
    .param int x
    .param int y
    .param int width
    .param int height
    .local int mines
    .local int i
    .local int i1
    .local int i2
    .local int j
    .local int j2
    .local int pos

    mines = 0

    set i1, x
    dec i1
    set i2, x
    inc i2

    set j, y
    dec j
    set j2, y
    inc j2

LOOPj:
    i = i1
LOOPi:
    if i > i2 goto ENDi
    if j < 0 goto ENDi
    if j >= height goto ENDi
    if i < 0 goto NEXTi
    if i >= width goto NEXTi

    pos = j * width
    pos += i

    $I0 = _mine_at( field, pos )
    unless $I0 goto NEXTi

    inc mines

NEXTi:
    inc i
    branch LOOPi
ENDi:
    inc j
    if j <= j2 goto LOOPj

    .return (mines)
.end

=item _mine_at( field, pos )

Returns 1 if a mine is in the given field
at the specified position, 0 otherwise.

=cut

.sub _mine_at
    .param pmc field
    .param int pos
    .local int v

    v = field[pos]
    if v == VAL_MINE goto MINE
    if v == VAL_MINE_EXPLODED goto MINE
    if v == VAL_FLAG_MINE goto MINE
    if v == VAL_UNSURE_MINE goto MINE
    if v == VAL_UNEXPLORED_MINE goto MINE
    if v == VAL_MARK_MINE goto MINE
    .return (0)
MINE:
    .return (1)
.end

=item _button_clicked( onField )

Called if you click the smiley button.
It starts a new level.

=cut

.sub _button_clicked
    .param pmc field

    $I0 = time
    field.'newLevel'( $I0 )
    field.'draw'()
.end

=back

=head1 AUTHOR

Jens Rieks E<lt>parrot at jensbeimsurfen dot deE<gt> is the author
and maintainer.
Please send patches and suggestions to the Perl 6 Internals mailing list.

=head1 COPYRIGHT

Copyright (C) 2004-2008, Parrot Foundation.

=cut

# Local Variables:
#   mode: pir
#   fill-column: 100
# End:
# vim: expandtab shiftwidth=4 ft=pir:
