#
# Forth interpreter
#

.constant STDIN 0
.constant InterpretPrompt "> "
.constant CompilePrompt ">> "

.constant InterpretMode 0
.constant CompileMode 1
.constant CommentMode 2

.constant Space 32
.constant Tab 9
.constant CellSize 65536

#
# Allocate registers
#

.constant CommandLength I23
.constant WordStart     I24
.constant WordEnd       I25
.constant WordLength    I26
.constant Mode          I28

.constant TempInt       I20
.constant TempInt2	I21
.constant TempInt3      I22

.constant InternalInt	I27

.constant Status	I19

# This may move elsewhere, hence the indirection
.constant NestLevel	I18
.constant PendingElse   I17
.constant LastCellUsed	I16

.macro NewNestLevel
  inc .NestLevel
.endm

.constant IntStack      I31

.constant TempNum	N16
.constant TempNum2	N17
.constant TempNum3	N18

.constant NumStack	N31

#

.constant Commands      S16
.constant CurrentWord   S17
.constant CompileWord   S18
.constant CompileBuffer S19
.constant TempString    S20
.constant WordBody	S21

.constant NewBodyString	S22

.constant TempStr    	S23

#

.constant CoreOps       P16
.constant UserOps       P18
.constant SpecialWords	P19

.constant CompiledWordPMC P20
.constant PASMCompiler	P21
.constant LinePMC	P22

.constant WorkTOS	P17

.constant TempPMC       P23
.constant TempPMC2	P24
.constant TempPMC3      P25

.constant LabelStack	P27
.constant TruePMC	P29
.constant FalsePMC	P28
.constant ReturnStack	P30
.constant PMCStack	P31
.constant CellPMC	P26

VeryBeginning:

    # We need a PMC for the compiler
    compreg .PASMCompiler, "PASM"

    bsr InitializeCoreOps

    set .Mode, .InterpretMode
    getstdin .LinePMC

Prompt:
    eq .Mode, .InterpretMode, InterpretPrompt
    print .CompilePrompt
    branch DonePromptString
InterpretPrompt:
    print .InterpretPrompt
DonePromptString:
    readline .Commands, .LinePMC
    bsr Chop
    bsr Interpret
    branch Prompt
    end

#------------------------------------------------------------------------------
#
# InitializeCoreOps
#
.macro AddCoreOp ( OpAddress, Name )
    set_addr .TempInt, .OpAddress
    set .CoreOps[.Name], .TempInt
.endm

.macro AddUserOp (OpName, OpBody)
    # Put the body definition into the S register that we compile from
    set .WordBody, .OpBody
    # Invoke the compiler
    bsr CompileString
    # Snag the address of the new body
    set .TempInt, .CompiledWordPMC[1]
    # Add the PMC to the user ops slot so it doesn't disappear
#    set .UserOps[.OpName], .CompiledWordPMC
    # Put the actual function address into the core ops hash, since
    # it is now a core op
    set .CoreOps[.OpName], .TempInt
.endm

.macro PopInt
    restore .WorkTOS
    set .IntStack, .WorkTOS    
.endm

.macro PushInt
    new .WorkTOS, .Integer
    set .WorkTOS, .IntStack
    save .WorkTOS
.endm

.macro PushTempInt
    new .WorkTOS, .Integer
    set .WorkTOS, .TempInt
    save .WorkTOS
.endm

.macro PopNum
    restore .WorkTOS
    set .NumStack, .WorkTOS        
.endm

.macro PushNum
    new .WorkTOS, .Float
    set .WorkTOS, .NumStack
    save .WorkTOS
.endm

#.macro PopStr
#
#.endm

#.macro PushStr
#
#.endm

.macro PopPMC
  restore .PMCStack    
.endm

.macro PushPMC
  save .PMCStack    
.endm

.macro PushFalse
  save .FalsePMC
.endm

.macro PushTrue
  save .TruePMC
.endm

InitializeCoreOps:
    #
    # Arithmetic, Single precision
    #
    new .CoreOps, .PerlHash
    new .UserOps, .PerlHash
    new .SpecialWords, .PerlHash
    new .ReturnStack, .PerlArray
    new .TruePMC, .Integer
    set .TruePMC, 1
    new .FalsePMC, .Integer
    set .FalsePMC, 0
    new .CellPMC, .Array
    set .CellPMC, .CellSize   # Our cell area is 64K by default
    set .LastCellUsed, 0
    new .LabelStack, .PerlArray

    set .SpecialWords["if"], 1
    set .SpecialWords["then"], 2
    set .SpecialWords["begin"], 3
    set .SpecialWords["until"], 4
    set .SpecialWords["again"], 5
    set .SpecialWords["exit"], 6
    set .SpecialWords["do"], 7
    set .SpecialWords["loop"], 8
    set .SpecialWords["+loop"], 9
    set .SpecialWords["compile,"], 10

    .AddCoreOp(Int_Dot,".")
    .AddCoreOp(Int_Dot, "u.")
    .AddCoreOp(Int_Dot_Stack,".s")
    .AddCoreOp(Quit,"quit")
    .AddCoreOp(Int_Add,"+")
    .AddCoreOp(Int_One_Plus,"1+")
    .AddCoreOp(Int_Sub,"-")
    .AddCoreOp(Int_One_Minus,"1-")
    .AddCoreOp(Int_Mul,"*")
    .AddCoreOp(Int_Div,"/")
    .AddCoreOp(Int_Mod,"mod")
    .AddCoreOp(Int_Slash_Mod,"/mod")
    .AddCoreOp(Int_Slash_Mod,"um/mod")
    .AddCoreOp(Int_Negate,"negate")
    .AddCoreOp(Int_Abs,"abs")
    .AddCoreOp(Int_Min,"min")
    .AddCoreOp(Int_Max,"max")

    #
    # Arithmetic, Double precision
    #

# s>d
# d>s
# d+
# d-
# dnegate
# dabs
# dmin
# dmax

    #
    # Arithmetic, Bitwise operations
    #

    .AddCoreOp(Int_And, "and")
    .AddCoreOp(Int_Or, "or")
    .AddCoreOp(Int_XOr, "xor")
    .AddCoreOp(Int_Invert, "invert")
    .AddCoreOp(Int_LShift, "lshift")
    .AddCoreOp(Int_RShift, "rshift")
    .AddUserOp("2*", "2 *")
# d2*
    .AddUserOp("2/", "2 /")
# d2/

    #
    # Arithmetic, Numeric comparison
    #

    .AddCoreOp(Int_LT,"<")
    .AddCoreOp(Int_LE,"<=")
    .AddCoreOp(Int_NE,"<>")
    .AddCoreOp(Int_EQ,"=")
    .AddCoreOp(Int_GT,">")
    .AddCoreOp(Int_GE,">=")
    .AddCoreOp(Int_LT0,"0<")
    .AddCoreOp(Int_LE0,"0<=")
    .AddCoreOp(Int_NE0,"0<>")
    .AddCoreOp(Int_EQ0,"0=")
    .AddCoreOp(Int_GT0,"0>")
    .AddCoreOp(Int_GE0,"0>=")
    .AddCoreOp(Int_LT,"u<")
    .AddCoreOp(Int_LE,"u<=")
    .AddCoreOp(Int_GT,"u>")
    .AddCoreOp(Int_GE,"u>=")
    .AddCoreOp(Within, "within")
# d<
# d<=
# d<>
# d=
# d>
# d>=
# d0<
# d0<=
# d0<>
# d0=
# d0>
# d0>=
# du<
# du<=
# du>
# du>=

    #
    # Arithmetic, Floating Point
    #

    .AddCoreOp(D_to_F, "d>f")
    .AddCoreOp(F_to_D, "f>d")
    .AddCoreOp(Float_Add, "f+")
    .AddCoreOp(Float_Sub, "f-")
    .AddCoreOp(Float_Mul, "f*")
    .AddCoreOp(Float_Div, "f/")
# fnegate
# fabs
# fmax
# fmin
# floor
# fround
# f**
# fsqrt
# fexp
# fexpm1
# fln
# flnp1
# flog
# falog
# f2*
# f2/
# 1/f
# precision
# set-precision
# fsin
# fcos
# fsincos
# ftan
# fasin
# facos
# fatan
# fatan2
# fsinh
# fcosh
# ftanh
# fasinh
# facosh
# fatanh
# pi
# f-rel
# f-abs
# f-
# f=
# f<>
# f<
# f<=
# f>
# f>=
# f0<
# f0<=
# f0<>
# f0=
# f0>
# f0>=

    #
    # Stack Manipulation, Data stack
    #

    .AddCoreOp(Int_Drop,"drop")
    .AddUserOp("nip", "swap drop")
    .AddCoreOp(Int_Dup,"dup")
    .AddCoreOp(Int_Over, "over")
    .AddUserOp("tuck", "swap over")
    .AddCoreOp(Int_Swap,"swap")
    .AddCoreOp(Stack_Depth, "depth")
    .AddCoreOp(Pick_Stack, "pick")
    .AddCoreOp(Rot_Stack, "rot")
    .AddCoreOp(Not_Rot_Stack, "-rot")
    .AddCoreOp(Maybe_Dup, "?dup")
    .AddCoreOp(Roll_Stack, "roll")
    .AddUserOp("2drop", "drop drop")
    .AddUserOp("2dup", "over over")
    .AddCoreOp(Two_Over, "2over")
    .AddCoreOp(Two_Swap, "2swap")
    .AddUserOp("2tuck", "2swap 2over")
    .AddUserOp("2nip", "2swap 2drop")
    .AddCoreOp(Two_Rot_Stack, "2rot")

    #
    # Stack Manipulation, Floating point stack
    #

# floating-stack
# fdrop
# fnip
# fdup
# fover
# ftuck
# fswap
# fpick
# frot


    #
    # Arithmetic, Mixed precision
    #

# m+

  .AddUserOp('*/', 'rot rot * swap /')
  .AddUserOp('*/mod', 'rot rot * swap /mod')
  .AddCoreOp(Int_Mul, "m*")
  .AddCoreOp(Int_Mul, "um*")
# m*/
# fm/mod
# sm/rem

    #
    # Stack Manipulation, Return stack
    #

  .AddCoreOp(To_R, ">r")
  .AddCoreOp(From_R, "r>")
  .AddCoreOp(Copy_From_R, "r@")
  .AddCoreOp(RDrop, "rdrop")
  .AddCoreOp(Two_To_R, "2>r")
  .AddCoreOp(Two_From_R, "2r>")
  .AddCoreOp(Two_R_Fetch, "2r@")
  .AddCoreOp(Two_RDrop, "2rdrop")

    #
    # Stack Manipulation, Stack pointer manipulation
    #

# sp0
# sp@
# sp!
# fp0
# fp@
# fp!
# rp@
# rp!
# lp0
# lp@
# lp!

    #
    # Memory, Dictionary allocation
    #

# here
# unused
# allot
# c,
# f,
# ,
# 2,
# align
# falign
# sfalign
# dfalign
# maxalign
# cfalign

    #
    # Memory, Heap allocation
    #

# allocate
# free
# resize

    #
    # Memory, Memory Access
    #

  .AddCoreOp(Store_Cell, "!")
  .AddCoreOp(Add_Cell, "+!")
  .AddCoreOp(Get_Cell, "@")
  .AddUserOp("cell+", "1 +")
  .AddUserOp("2!", "swap over ! cell+ !")
  .AddUserOp("2@", "dup cell+ @ swap @")
  .AddCoreOp(Store_Cell, "c!")
  .AddCoreOp(Get_Cell, "c@")
# f@
# f!
# sf@
# sf!
# df@
# df!

    #
    # Memory, Address arithmetic
    #

  .AddUserOp("chars", "0 +")
  .AddUserOp("char+", "1 +")
  .AddUserOp("cells", "0 +")
# cell
# aligned
# floats
# float+
# faligned
# sfloats
# sfloat+
# sfaligned
# dfloats
# dfloat+
# dfaligned
# maxaligned
# cfaligned
# ADDRESS-UNIT-BITS

    #
    # Memory, Memory Blocks
    #

# move
# erase
# cmove
# cmove>
# fill
# blank
# compare
# search
# -trailing
# /string
# bounds

    #
    # Control Structures, Arbitrary control structures
    #
# IF
# AHEAD
# THEN
# BEGIN
# UNTIL
# AGAIN
# CS-PICK
# CS-ROLL
# ELSE
# WHILE
# REPEAT
# ENDIF
# ?DUP-IF
# ?DUP-0=-IF
# ?DO
# +DO
# U+DO
# -DO
# U-DO
# DO
# FOR
# LOOP
# +LOOP
# -LOOP
# NEXT
# LEAVE
# ?LEAVE
# unloop
# DONE
# case
# endcase
# of
# endof

    #
    # Control Structures, Calls and returns
    #
# recursive
# recurse
# Defer
# EXIT
# ;s

    #
    # Control Structures, Exception Handling
    #
# throw
# exception
# catch
# try
# recover
# endtry
# abort"
# abort

    #
    # Defining Words
    #
# CREATE

    #
    # Variables
    #
# variable
# 2variable
# fvariable
# user

    #
    # Constants
    #
# constant
# 2constant
# fconstant

    #
    # Values
    #

# value
# TO

    #
    # Anonymous definitions
    #

# :noname
# noname
# lastxt

    #
    # Supplying the name of a defined word
    #

# nextname

   #
   # Miscellaneous other stuff
   #
   .AddUserOp("false", "0")
   .AddUserOp("true", "0 invert")
   .AddCoreOp(Print_Space, "space")
   .AddCoreOp(Print_Spaces, "spaces")
   .AddCoreOp(Print_CR, "cr")
   .AddUserOp("bl", "32")
   .AddCoreOp(Emit, "emit")
   .AddCoreOp(Execute, "execute")

    ret

#------------------------------------------------------------------------------
#
# Test Interpret routine
#
Interpret:
    bsr EatLeadingWhitespace
StartInterpret:
    bsr CollectWord
    bsr EatLeadingWhitespace
    ne .CurrentWord, "\\", MaybeComment
    set .Commands, ""
    branch DoneInterpret
MaybeComment:
    ne .CurrentWord, "(", MaybeCompile
    save .Mode
    set .Mode, .CommentMode
    branch DoneSettingMode
MaybeCompile:
    ne .CurrentWord, ":", MaybeInterpret
    set .Mode, .CompileMode
    branch DoneSettingMode
MaybeInterpret:


DoneSettingMode:
    bsr InterpretWord

    length .TempInt, .Commands
    eq .TempInt, 0, DoneInterpret
    branch StartInterpret
DoneInterpret:
    ret

#------------------------------------------------------------------------------
#
# InterpretWord
#
InterpretWord:
    ne .Mode, .CommentMode, MaybeCompileWord
    ne .CurrentWord, ")", DoneInterpretWord
    restore .Mode
    branch DoneInterpretWord
MaybeCompileWord:
    ne .Mode, .CompileMode, MaybeInterpretWord
    eq .CurrentWord, ":", DoneInterpretWord
    ne .CurrentWord, ";", DoCompileStuff
    set .Mode, .InterpretMode

    set .WordBody, .CompileBuffer
    bsr CompileString
    set .TempInt, .CompiledWordPMC[1]
    set .CoreOps[.CompileWord], .TempInt

    set .CompileWord, ""
    set .CompileBuffer, ""
    branch DoneInterpretWord
DoCompileStuff:
    ne .CompileWord, "", FillCompileBuffer
    set .CompileWord, .CurrentWord
    branch EndCompileWord
FillCompileBuffer:
    concat .CompileBuffer, .CurrentWord
    concat .CompileBuffer, " "
EndCompileWord:
    branch DoneInterpretWord
MaybeInterpretWord:
    set .IntStack, .CurrentWord
    length .TempInt, .CurrentWord
    dec .TempInt
    eq .CurrentWord, "", DoneInterpret
    ord .TempInt, .CurrentWord, .TempInt
    lt .TempInt, 48, NotInt
    gt .TempInt, 58, NotInt
    ne .IntStack, 0, PushInt
    eq .CurrentWord, "0", PushInt

NotInt:
    ne .CurrentWord, "'", NotTick
    bsr EatLeadingWhitespace
    eq .Commands, "", DoneInterpretWord
    bsr CollectWord
    set .IntStack, .CoreOps[.CurrentWord]
    .PushInt
    branch DoneInterpretWord
    
NotTick:
    set .TempInt, .CoreOps[.CurrentWord]
    eq .TempInt, 0, UserWord
    jsr .TempInt
    branch DoneInterpretWord

UserWord:
    set .TempString, .UserOps[.CurrentWord]
    concat .TempString, " "
    concat .Commands, .TempString, .Commands

    branch DoneInterpretWord
PushInt:
    .PushInt
    branch DoneInterpretWord

Int_One_Minus:
    .PopInt
    dec .IntStack
    .PushInt
    branch DoneInterpretWord
Int_One_Plus:
    .PopInt 
    inc .IntStack
    .PushInt 
    branch DoneInterpretWord
Int_Dot:
    .PopPMC
    print .PMCStack
    print " "
    branch DoneInterpretWord
Int_Dot_Stack:
    branch DoneInterpretWord
Int_Dup:
    .PopPMC 
    .PushPMC 
    .PushPMC 
    branch DoneInterpretWord
Int_Drop:
    .PopPMC
    branch DoneInterpretWord
Int_Swap:
    rotate_up 2
    branch DoneInterpretWord
Quit:
    end
Int_Abs:
    .PopInt 
    ge .IntStack, 0, DoneIntAbs
    mul .IntStack, .IntStack, -1
DoneIntAbs:
    .PushInt 
    branch DoneInterpretWord
Int_Max:
    .PopInt 
    set .TempInt, .IntStack
    .PopInt 
    ge .IntStack, .TempInt, Done_IntMax
    set .IntStack, .TempInt
Done_IntMax:
    .PushInt 
    branch DoneInterpretWord
Int_Min:
    .PopInt 
    set .TempInt, .IntStack
    .PopInt 
    le .IntStack, .TempInt, Done_IntMin
    .PushInt 
    set .IntStack, .TempInt
Done_IntMin:
    .PushInt 
    branch DoneInterpretWord
Int_Add:
    .PopInt 
    set .TempInt, .IntStack
    .PopInt 
    add .IntStack, .IntStack, .TempInt
    .PushInt 
    branch DoneInterpretWord
Int_Sub:
    .PopInt 
    set .TempInt, .IntStack
    .PopInt 
    sub .IntStack, .IntStack, .TempInt
    .PushInt 
    branch DoneInterpretWord
Int_Negate:
    .PopInt 
    mul .IntStack, .IntStack, -1
    .PushInt 
    branch DoneInterpretWord
Int_Mul:
    .PopInt 
    set .TempInt, .IntStack
    .PopInt 
    mul .IntStack, .IntStack, .TempInt
    .PushInt 
    branch DoneInterpretWord
Int_Div:
    .PopInt 
    set .TempInt, .IntStack
    .PopInt 
    div .IntStack, .IntStack, .TempInt
    .PushInt 
    branch DoneInterpretWord
Int_Mod:
    .PopInt 
    set .TempInt, .IntStack
    .PopInt 
    mod .IntStack, .IntStack, .TempInt
    .PushInt 
    branch DoneInterpretWord
Int_Slash_Mod:
    .PopInt 
    set .TempInt, .IntStack
    .PopInt 
    set .TempInt2, .IntStack
    mod .IntStack, .TempInt2, .TempInt
    .PushInt 
    div .IntStack, .TempInt2, .TempInt
    .PushInt 
    branch DoneInterpretWord
Int_GT:
    .PopInt 
    set .TempInt, .IntStack
    .PopInt 
    gt .TempInt, .IntStack, Int_is_GT
    set .IntStack, 0
    branch Int_GT_end
 Int_is_GT:
    set .IntStack, 1
 Int_GT_end:
    .PushInt 
    branch DoneInterpretWord
Int_GE:
    .PopInt 
    set .TempInt, .IntStack
    .PopInt 
    ge .TempInt, .IntStack, Int_is_GE
    set .IntStack, 0
    branch Int_GE_end
 Int_is_GE:
    set .IntStack, 1
 Int_GE_end:
    .PushInt 
    branch DoneInterpretWord
Int_NE:
    .PopInt 
    set .TempInt, .IntStack
    .PopInt 
    ne .TempInt, .IntStack, Int_is_NE
    set .IntStack, 0
    branch Int_NE_end
 Int_is_NE:
    set .IntStack, 1
 Int_NE_end:
    .PushInt 
    branch DoneInterpretWord
Int_EQ:
    .PopInt 
    set .TempInt, .IntStack
    .PopInt 
    eq .TempInt, .IntStack, Int_is_EQ
    set .IntStack, 0
    branch Int_EQ_end
 Int_is_EQ:
    set .IntStack, 1
 Int_EQ_end:
    .PushInt 
    branch DoneInterpretWord
Int_LT:
    .PopInt 
    set .TempInt, .IntStack
    .PopInt 
    lt .TempInt, .IntStack, Int_is_LT
    set .IntStack, 0
    branch Int_LT_end
 Int_is_LT:
    set .IntStack, 1
 Int_LT_end:
    .PushInt 
    branch DoneInterpretWord
Int_LE:
    .PopInt 
    set .TempInt, .IntStack
    .PopInt 
    le .TempInt, .IntStack, Int_is_LE
    set .IntStack, 0
    branch Int_LE_end
 Int_is_LE:
    set .IntStack, 1
 Int_LE_end:
    .PushInt 
    branch DoneInterpretWord
Int_LT0:
    .PopInt 
    lt .IntStack, 0, Int_is_LT0
    set .IntStack, 0
    branch Int_LT0_end
 Int_is_LT0:
    set .IntStack, 1
 Int_LT0_end:
    .PushInt 
    branch DoneInterpretWord
Int_LE0:
    .PopInt 
    le .IntStack, 0, Int_is_LE0
    set .IntStack, 0
    branch Int_LE0_end
 Int_is_LE0:
    set .IntStack, 1
 Int_LE0_end:
    .PushInt 
    branch DoneInterpretWord
Int_NE0:
    .PopInt 
    ne .IntStack, 0, Int_is_NE0
    set .IntStack, 0
    branch Int_NE0_end
 Int_is_NE0:
    set .IntStack, 1
 Int_NE0_end:
    .PushInt 
    branch DoneInterpretWord
Int_EQ0:
    .PopInt 
    eq .IntStack, 0, Int_is_EQ0
    set .IntStack, 0
    branch Int_EQ0_end
 Int_is_EQ0:
    set .IntStack, 1
 Int_EQ0_end:
    .PushInt 
    branch DoneInterpretWord
Int_GT0:
    .PopInt 
    gt .IntStack, 0, Int_is_GT0
    set .IntStack, 0
    branch Int_GT0_end
 Int_is_GT0:
    set .IntStack, 1
 Int_GT0_end:
    .PushInt 
    branch DoneInterpretWord
Int_GE0:
    .PopInt 
    ge .IntStack, 0, Int_is_GE0
    set .IntStack, 0
    branch Int_GE0_end
 Int_is_GE0:
    set .IntStack, 1
 Int_GE0_end:
    .PushInt 
    branch DoneInterpretWord

Int_And:
    .PopInt 
    set .TempInt, .IntStack
    .PopInt 
    band .IntStack, .TempInt
    .PushInt 
    branch DoneInterpretWord
Int_Or:
    .PopInt 
    set .TempInt, .IntStack
    .PopInt 
    bor .IntStack, .TempInt
    .PushInt 
    branch DoneInterpretWord
Int_XOr:
    .PopInt 
    set .TempInt, .IntStack
    .PopInt 
    bxor .IntStack, .TempInt
    .PushInt 
    branch DoneInterpretWord
Int_Invert:
    .PopInt 
    bnot .IntStack, .IntStack
    .PushInt 
    branch DoneInterpretWord
Int_LShift:
    .PopInt 
    set .TempInt, .IntStack
    .PopInt 
    shl .IntStack, .IntStack, .TempInt
    .PushInt 
    branch DoneInterpretWord
Int_RShift:
    .PopInt 
    set .TempInt, .IntStack
    .PopInt 
    shr .IntStack, .IntStack, .TempInt
    .PushInt 
    branch DoneInterpretWord
Int_Over:
    .PopInt 
    set .TempInt, .IntStack
    .PopInt 
    .PushInt 
    .PushTempInt
    .PushInt 
    branch DoneInterpretWord

Print_Space:
    print " "
    branch DoneInterpretWord

Print_Spaces:
    .PopInt
    lt .IntStack, 1, DoneInterpretWord
  spaceloop:
    print " "
    dec .IntStack
    gt .IntStack, 0, spaceloop
    branch DoneInterpretWord

Stack_Depth:
    depth .IntStack
    .PushInt
    branch DoneInterpretWord

Rot_Stack:
    rotate_up -3
    branch DoneInterpretWord

Two_Rot_Stack:
    rotate_up -6
    rotate_up -6
    branch DoneInterpretWord

Not_Rot_Stack:
    rotate_up 3
    branch DoneInterpretWord

Roll_Stack:
    .PopInt
    sub .IntStack, 0, .IntStack
    rotate_up .IntStack
    branch DoneInterpretWord

Two_Over:
    lookback .PMCStack, 3
    save .PMCStack
    lookback .PMCStack, 3
    save .PMCStack
    branch DoneInterpretWord

Two_Swap:
    rotate_up -4
    rotate_up -4
    branch DoneInterpretWord

Maybe_Dup:
    .PopPMC
    if .PMCStack, dupit
    new .PMCStack, .Integer
    set .PMCStack, 0
    .PushPMC
    branch DoneInterpretWord
    .PushPMC
    .PushPMC
    branch DoneInterpretWord

Print_CR:
    print "\n"
    branch DoneInterpretWord

Emit:
    .PopInt
    chr .TempStr, .IntStack
    print .TempStr
    branch DoneInterpretWord

Execute:
    .PopInt
    jsr .IntStack
    branch DoneInterpretWord

Pick_Stack:
    .PopInt
    dec .IntStack
    lookback .PMCStack, .IntStack
    .PushPMC
    branch DoneInterpretWord

To_R:
    .PopPMC
    push .ReturnStack, .PMCStack
    branch DoneInterpretWord

From_R:
    pop .PMCStack, .ReturnStack
    .PushPMC
    branch DoneInterpretWord

Copy_From_R:
    pop .PMCStack, .ReturnStack
    push .ReturnStack, .PMCStack
    .PushPMC
    branch DoneInterpretWord

Two_To_R:
    restore .TempPMC
    restore .PMCStack
    push .ReturnStack, .PMCStack
    push .ReturnStack, .TempPMC
    branch DoneInterpretWord
  
Two_From_R:
    pop .TempPMC, .ReturnStack
    pop .PMCStack, .ReturnStack
    save .PMCStack
    save .TempPMC
    branch DoneInterpretWord
  
Two_R_Fetch:
    set .TempPMC, .ReturnStack[-2]
    save .TempPMC
    set .TempPMC, .ReturnStack[-1]
    save .TempPMC
    branch DoneInterpretWord

Two_RDrop:
    pop .PMCStack, .ReturnStack
RDrop:
    pop .PMCStack, .ReturnStack
    branch DoneInterpretWord

Within:
    restore .TempPMC3
    restore .TempPMC2
    restore .TempPMC
    le .TempPMC3, .TempPMC2, three_two
 two_three:
    lt .TempPMC, .TempPMC2, Is_not_within
    ge .TempPMC, .TempPMC3, Is_not_within
    branch Is_within
 three_two:
    le .TempPMC2, .TempPMC, Is_within 
    lt .TempPMC, .TempPMC3, Is_within
    branch Is_not_within
 Is_within:
    .PushTrue
    branch DoneInterpretWord
 Is_not_within:
    .PushFalse
    branch DoneInterpretWord

Store_Cell:
    .PopInt
    .PopPMC
    set .CellPMC[.IntStack], .PMCStack
    branch DoneInterpretWord

Get_Cell:
    .PopInt
    set .PMCStack, .CellPMC[.IntStack]
    .PushPMC
    branch DoneInterpretWord

Add_Cell:
    .PopInt
    .PopPMC
    set .TempPMC, .CellPMC[.IntStack]
    set .TempInt2, .TempPMC
    set .TempInt, .PMCStack
    add .TempInt, .TempInt, .TempInt2
    new .TempPMC, .Integer
    set .TempPMC, .TempInt
    set .CellPMC[.IntStack], .TempPMC
    branch DoneInterpretWord

D_to_F:
    .PopInt
    set .NumStack, .IntStack
    .PushNum
    branch DoneInterpretWord

F_to_D:
    .PopNum
    set .IntStack, .NumStack
    .PushInt
    branch DoneInterpretWord

Float_Add:
    .PopNum
    set .TempNum, .NumStack
    .PopNum
    add .NumStack, .TempNum
    .PushNum
    branch DoneInterpretWord

Float_Sub:
    .PopNum
    set .TempNum, .NumStack
    .PopNum
    sub .NumStack, .NumStack, .TempNum
    .PushNum
    branch DoneInterpretWord

Float_Mul:
    .PopNum
    set .TempNum, .NumStack
    .PopNum
    mul .NumStack, .NumStack, .TempNum
    .PushNum
    branch DoneInterpretWord

Float_Div:
    .PopNum
    set .TempNum, .NumStack
    .PopNum
    div .NumStack, .NumStack, .TempNum
    .PushNum
    branch DoneInterpretWord




DoneInterpretWord:
    ret

#------------------------------------------------------------------------------
#
# CollectWord
#
CollectWord:
    length .TempInt, .Commands
    eq .TempInt, 0, DoneCollectWord
    set .TempInt3, 0
NextCharCollectWord:
    eq .TempInt3, .TempInt, EndDarkspace
    ord .TempInt2, .Commands, .TempInt3
    eq .TempInt2, .Space, EndDarkspace
    eq .TempInt2, .Tab, EndDarkspace
    inc .TempInt3
    branch NextCharCollectWord
EndDarkspace:
    substr .CurrentWord, .Commands, 0, .TempInt3, ""
DoneCollectWord:
    ret

#------------------------------------------------------------------------------
#
# EatLeadingWhitespace
#
EatLeadingWhitespace:
    length .TempInt, .Commands
    eq .TempInt, 0, DoneLeadingWhitespace
    set .TempInt3, 0
    ord .TempInt2, .Commands, .TempInt3
    eq .TempInt2, .Space, StartLeadingWhitespace
    eq .TempInt2, .Tab, StartLeadingWhitespace
    branch DoneLeadingWhitespace
StartLeadingWhitespace:
    inc .TempInt3
    eq .TempInt, .TempInt, FinishLeadingWhitespace
    ord .TempInt2, .Commands, .TempInt3
    eq .TempInt2, .Space, StartLeadingWhitespace
    eq .TempInt2, .Tab, StartLeadingWhitespace
FinishLeadingWhitespace:
    substr .Commands, 0, .TempInt3, ""
DoneLeadingWhitespace:
    ret

#------------------------------------------------------------------------------
#
# Chop
#
Chop:
    length .TempInt, .Commands
    dec .TempInt
    substr .Commands, .Commands, 0, .TempInt
    ret

#------------------------------------------------------------------------------
#
# CompileString
#
# This little sub takes the string in .WordBody and compiles it, returning
# a PMC that corresponds to the newly compiled word. This is pretty si
#
CompileString:
    # In case someone's using it
    save .NewBodyString
    # Probably ultimately going to go
    save .Commands
    set .Commands, .WordBody
    set .NewBodyString, ""

#    print "Being asked to compile:"
#    print .WordBody
#    print ":\n"

CompileWord:
    # No space!
    bsr EatLeadingWhitespace

    # If we're out of stuff, just leave
    eq .Commands, "", DoTheCompile

    # Get the next word in the command buffer
    bsr CollectWord

    # Identify it and add the text for it into the 
    bsr IdentifyAndCompileWord

    # If the buffer's not empty, then go back and process it
    length .TempInt, .Commands    
    if .TempInt, CompileWord

 DoTheCompile:
    # Add in the return
    concat .NewBodyString, "ret\n"

    # Compile the string
#    print "Compiling:\n"
#    print .NewBodyString
    compile .CompiledWordPMC, .PASMCompiler, .NewBodyString

    # And we're done
    restore .Commands
    restore .NewBodyString
    ret

IdentifyAndCompileWord:
    bsr CheckForWord
    if .Status, NotWord
    bsr AddPlainWord
    ret
NotWord:
    bsr CheckForSpecialWord
    if .Status, NotSpecial
    bsr AddSpecialWord
    ret
NotSpecial:
    bsr CheckForInt
    if .Status, NotAnInt
    bsr AddIntConstant
    ret
NotAnInt:
    bsr CheckForFloat
    if .Status, NotFloat
    bsr AddFloatConstant
    ret
NotFloat:
    bsr CheckForString
    if .Status, NotString
    bsr AddStringConstant
    ret
NotString:
    # Just ignore it
    ret

CheckForWord:
    set .TempInt, .CoreOps[.CurrentWord]
    set .Status, 0
    if .TempInt, GoodWord
    set .Status, 1
  GoodWord:
    ret

CheckForSpecialWord:
    set .TempInt, .SpecialWords[.CurrentWord]
    set .Status, 0
    if .TempInt, GoodSpecialWord
    set .Status, 1
  GoodSpecialWord:
    ret
# We cheat and do an string->int->string conversion and see
# if the results are the same. If so, it's an integer. (This is, I should
# note, very very wrong for non-decimal bases, which Forth is happy
# to do)
CheckForInt:
    set .TempInt, .CurrentWord
    set .TempString, .TempInt
    set .Status, 0
    eq .TempString, .CurrentWord, LeaveIntCheck
    set .Status, 1
  LeaveIntCheck:
    ret

CheckForFloat:
    # No float for you!
    set .Status, 1
    ret
CheckForString:
    set .Status, 1
    ret

# Control flow and such, where a simple substitution won't do
AddSpecialWord:
    ne .CurrentWord, "if", NotIf
    .NewNestLevel
    concat .NewBodyString, "restore P17\n"
    concat .NewBodyString, "unless P17, endif"
    set .TempString, .NestLevel
    concat .NewBodyString, .TempString
    concat .NewBodyString, "\n" 
    concat .TempString, "endif", .TempString
    push .LabelStack, .TempString
    branch EndSpecWord
  NotIf:
    ne .CurrentWord, "then", NotThen
    pop .TempString, .LabelStack
    concat .NewBodyString, .TempString
    concat .NewBodyString, ":\n" 
    branch EndSpecWord
  NotThen:
    ne .CurrentWord, "else", NotElse
    branch EndSpecWord    
  NotElse:
    ne .CurrentWord, "exit", NotExit
    concat .NewBodyString, "ret\n"
    branch EndSpecWord    
  NotExit:
    ne .CurrentWord, "begin", NotBegin
    .NewNestLevel
    concat .NewBodyString, "begin"
    set .TempString, .NestLevel
    concat .NewBodyString, .TempString
    concat .NewBodyString, ":\n" 
    concat .TempString, "begin", .TempString
    push .LabelStack, .TempString
    branch EndSpecWord    
  NotBegin:
    ne .CurrentWord, "again", NotAgain
    concat .NewBodyString, "branch "
    pop .TempString, .LabelStack
    concat .NewBodyString, .TempString
    concat .NewBodyString, "\n"
    branch EndSpecWord    
  NotAgain:
    ne .CurrentWord, "until", NotUntil
    concat .NewBodyString, "restore P17\n"
    concat .NewBodyString, "unless P17, "
    pop .TempString, .LabelStack
    concat .NewBodyString, .TempString
    concat .NewBodyString, "\n"
    branch EndSpecWord    
  NotUntil:
    ne .CurrentWord, "do", NotDo
    .NewNestLevel
    concat .NewBodyString, "restore P31\n"
    concat .NewBodyString, "restore P23\n"
    concat .NewBodyString, "push P30, P23\n"
    concat .NewBodyString, "push P30, P31\n"
    set .TempString, .NestLevel
    concat .TempString, "dolabel", .TempString
    push .LabelStack, .TempString
    concat .NewBodyString, .TempString
    concat .NewBodyString, ":\n"    
    branch EndSpecWord    
  NotDo:
    ne .CurrentWord, "loop", NotLoop
    concat .NewBodyString, "pop P23, P30\n"
    concat .NewBodyString, "inc P23\n"
    concat .NewBodyString, "pop P31, P30\n"
    concat .NewBodyString, "push P30, P31\n"
    concat .NewBodyString, "push P30, P23\n"
    concat .NewBodyString, "ne P23, P31, "
    pop .TempString, .LabelStack
    concat .NewBodyString, .TempString
    concat .NewBodyString, "\n"
    concat .NewBodyString, "pop P31, P30\npop P31, P30\n"
    branch EndSpecWord    
  NotLoop:
    ne .CurrentWord, "+loop", NotPlusLoop
    concat .NewBodyString, "pop P23, P30\n"
    concat .NewBodyString, "restore P24\n"
    concat .NewBodyString, "add P23, P23, P24\n"
    concat .NewBodyString, "pop P31, P30\n"
    concat .NewBodyString, "push P30, P31\n"
    concat .NewBodyString, "push P30, P23\n"
    concat .NewBodyString, "ne P23, P31, "
    pop .TempString, .LabelStack
    concat .NewBodyString, .TempString
    concat .NewBodyString, "\n"
    concat .NewBodyString, "pop P31, P30\npop P31, P30\n"
    branch EndSpecWord    
  NotPlusLoop:
    ne .CurrentWord, "compile,", NotCompileComma
    concat .NewBodyString, "restore P31\n"
    concat .NewBodyString, "set I31, P31\n"
    concat .NewBodyString, "jsr I31\n"
    branch EndSpecWord

  NotCompileComma:
    branch EndSpecWord    


EndSpecWord:
    ret

AddIntConstant:
    concat .NewBodyString, "new P17, .Integer\n"
    concat .NewBodyString, "set P17, "
    concat .NewBodyString, .CurrentWord
    concat .NewBodyString, "\n"
    concat .NewBodyString, "save P17\n"
    ret

AddFloatConstant:
    concat .NewBodyString, "new P17, .Float\n"
    concat .NewBodyString, "set P17, "
    concat .NewBodyString, .CurrentWord
    concat .NewBodyString, "\n"
    concat .NewBodyString, "save P17\n"
    ret

AddStringConstant:
    # Should really be a String, but we don't have that yet
    concat .NewBodyString, "new P17, .PerlString\n"
    concat .NewBodyString, "set P17, "
    concat .NewBodyString, .CurrentWord
    concat .NewBodyString, "\n"
    concat .NewBodyString, "save P17\n"
    ret

AddPlainWord:
    set .TempInt, .CoreOps[.CurrentWord]
    concat .NewBodyString, "set I27, "
    set .TempString, .TempInt
    concat .NewBodyString, .TempString
    concat .NewBodyString, "\njsr I27"
    concat .NewBodyString, "\n"
    ret

AddControlStruct:
    ret

VeryEnd:
    end
