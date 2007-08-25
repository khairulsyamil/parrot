# Copyright (C) 2001-2006, The Perl Foundation.
# $Id$
package Parrot::Configure::Options::Reconf;
use strict;
use warnings;
use base qw( Exporter );
our @EXPORT_OK = qw( @valid_options $script %options_components );

our @valid_options = qw{
        ask
        debugging
        help
        languages
        lex
        maintainer
        step
        target
        verbose
        yacc
};

our $script = q{tools/dev/reconfigure.pl};

my %short_circuits = (
    help        => \&print_help,
);

our %options_components = (
    'valid_options'     => \@valid_options,
    'script'            => $script,
    'short_circuits'    => \%short_circuits,
    'conditionals'      => \&conditional_assignments,
);

sub conditional_assignments {
    my $argsref = shift;
    $argsref->{debugging} = 1
        unless ( ( exists $argsref->{debugging} ) && !$argsref->{debugging} );
    $argsref->{maintainer} = 1
        if defined $argsref->{lex} or defined $argsref->{yacc};
    return $argsref;
}

sub print_help {
    print <<"EOT";
$script

General Options:

   --help               Show this text
   --verbose            Output extra information
   --step=(gen::languages)
                        Execute a single configure step
   --target=(Makefile)  Needed if --step=gen::makefiles
   --languages="list of languages"
                        Specify a list of languages to process

   --ask                Have Configure ask for commonly-changed info

Compile Options:

   --debugging=0        Disable debugging, default = 1
   --lex=(lexer)        Use the given lexical analyzer generator
   --yacc=(parser)      Use the given parser generator
EOT
    return 1;
}

1;

# Local Variables:
#   mode: cperl
#   cperl-indent-level: 4
#   fill-column: 100
# End:
# vim: expandtab shiftwidth=4:
