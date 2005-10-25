use strict;
use warnings;
use Parrot::Test tests => 53;
use Parrot::Test::PGE;


# character class
p6rule_is  ('abcdef', '<[c]>', 'character class');
p6rule_is  ('abcdef', '<[dcb]>**{3}', 'repeated character class');
p6rule_is  ('abcdef', '^<[a]>', 'anchored character class');
p6rule_is  ('abcdef', '<-[e]>', 'negated character class');
p6rule_is  ('abcdef', '<[c]>', 'optional character class');
p6rule_is  ('abcdef', '<[dcb]>**{3}?', 'repeated optional character class');
p6rule_is  ('abcdef', '^<[a]>?', 'anchored optional character class');
p6rule_is  ('abcdef', '<-[e]>?', 'negated optional character class');
p6rule_isnt('abcdef', '<-[dcb]>**{3}', 'repeated negated character class');
p6rule_is  ('abcdef', '^<-[e]>', 'anchored negated character class');
p6rule_isnt('abcdef', '^<-[a]>', 'anchored negated character class');

# character class range
p6rule_is  ('abcdef', '<[b..d]>', 'character range');
p6rule_is  ('abxxef', '<[b..d]>', 'character range');
p6rule_is  ('axcxef', '<[b..d]>', 'character range');
p6rule_is  ('axxdef', '<[b..d]>', 'character range');
p6rule_isnt('axxxef', '<[b..d]>', 'character range');
p6rule_is  ('abcdef', '<-[b..d]>', 'negated character range');
p6rule_isnt('bbccdd', '<-[b..d]>', 'negated character range');

# optional character class range
p6rule_is  ('abcdef', '<[b..d]>?', 'optional character range');
p6rule_is  ('abxxef', '<[b..d]>?', 'optional character range');
p6rule_is  ('axcxef', '<[b..d]>?', 'optional character range');
p6rule_is  ('axxdef', '<[b..d]>?', 'optional character range');
p6rule_is  ('axxxef', '<[b..d]>?', 'optional character range');
p6rule_is  ('abcdef', '<-[b..d]>?', 'negated optional character range');
p6rule_is  ('bbccdd', '<-[b..d]>?', 'negated optional character range');

# escaped hyphen
p6rule_is  ('ab-def', '<[\-]>', 'escaped hyphen');
p6rule_isnt('abcdef', '<[\-]>', 'escaped hyphen');
p6rule_is  ('ab-def', '<[\-]>?', 'optional escaped hyphen');
p6rule_is  ('abcdef', '<[\-]>?', 'optional escaped hyphen');
p6rule_is  ('---x--', '<-[\-]>', 'negated escaped hyphen');
p6rule_isnt('------', '<-[\-]>', 'negated escaped hyphen');
p6rule_is  ('---x--', '<-[\-]>?', 'negated optional escaped hyphen');
p6rule_is  ('------', '<-[\-]>?', 'negated optional escaped hyphen');

# escaped hyphen in range
p6rule_is  ('ab-def', '<[\-+]>', 'escaped hyphen in range');
p6rule_is  ('ab+def', '<[\-+]>', 'escaped hyphen in range');
p6rule_isnt('abcdef', '<[\-+]>', 'escaped hyphen in range');
p6rule_is  ('ab-def', '<[+\-]>', 'escaped hyphen in range');
p6rule_is  ('ab+def', '<[+\-]>', 'escaped hyphen in range');
p6rule_isnt('abcdef', '<[+\-]>', 'escaped hyphen in range');
p6rule_is  ('---x--', '<-[\-+]>', 'negated escaped hyphen in range');
p6rule_isnt('------', '<-[\-+]>', 'negated escaped hyphen in range');
p6rule_is  ('---x--', '<-[+\-]>', 'negated escaped hyphen in range');
p6rule_isnt('------', '<-[+\-]>', 'negated escaped hyphen in range');

# optional escaped hyphen in range
p6rule_is  ('ab-def', '<[\-+]>?', 'optional escaped hyphen in range');
p6rule_is  ('ab+def', '<[\-+]>?', 'optional escaped hyphen in range');
p6rule_is  ('abcdef', '<[\-+]>?', 'optional escaped hyphen in range');
p6rule_is  ('ab-def', '<[+\-]>?', 'optional escaped hyphen in range');
p6rule_is  ('ab+def', '<[+\-]>?', 'optional escaped hyphen in range');
p6rule_is  ('abcdef', '<[+\-]>?', 'optional escaped hyphen in range');
p6rule_is  ('---x--', '<-[\-+]>?', 'negated optional escaped hyphen in range');
p6rule_is  ('------', '<-[\-+]>?', 'negated optional escaped hyphen in range');
p6rule_is  ('---x--', '<-[+\-]>?', 'negated optional escaped hyphen in range');
p6rule_is  ('------', '<-[+\-]>?', 'negated optional escaped hyphen in range');

# dont forget to change the number of tests :-)
