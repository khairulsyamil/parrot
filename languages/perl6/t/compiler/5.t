#!perl
use strict;
use P6C::TestCompiler tests => 5;

##############################
output_is(<<'CODE', <<'OUT', "For 1 -> 2");
sub main() {
    my @a = 1..10;
    for @a -> $a, $b {
	print1($a);
    }
}

CODE
1
3
5
7
9
OUT

##############################
output_is(<<'CODE', <<'OUT', "For 1;1 -> 3");
sub main() {
    my @a = 1..10;
    for @a ; @a -> $a, $b, $c {
	print1($a);
    }
}

CODE
1
2
4
5
7
8
OUT

##############################
output_is(<<'CODE', <<'OUT', "For 1;1 -> 1;1");
sub main() {
    for 1..10 ; 1..10 -> $a ; $b {
	print1($a);
    }
}

CODE
1
2
3
4
5
6
7
8
9
10
OUT

##############################
output_is(<<'CODE', <<'OUT', "For 1;1 -> 1;1 (uneven)");
sub main() {
    for 1..10 ; 1..5 -> $a; $b {
	print1($a);
    }
}

CODE
1
2
3
4
5
OUT

##############################
output_is(<<'CODE', <<'OUT', "For 1;1 -> 1;2");
sub main() {
    for 1..5 ; 1..10 -> $a; $b, $c {
	print1($a _ ' ' _ $c);
    }
}

CODE
1 2
2 4
3 6
4 8
5 10
OUT

