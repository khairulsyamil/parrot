#
# Type.pm
#
# Copyright (C) 2002-2003 Gregor N. Purdy. All rights reserved.
# This program is free software. It is subject to the same license
# as the Parrot interpreter.
#
# $Id$
#

use strict;
eval "use warnings";

package Jako::Construct::Type;

use Carp;

use overload
  "=="  => sub { $_[0]->code eq $_[0]->code },
  "!="  => sub { $_[0]->code ne $_[0]->code },
  "eq"  => sub { $_[0]->code eq $_[0]->code },
  "ne"  => sub { $_[0]->code ne $_[0]->code },
  q{""} => sub { $_[0]->name }
;

use Jako::Token;

use Jako::Construct::Type::Integer;
use Jako::Construct::Type::Number;
use Jako::Construct::Type::Object;
use Jako::Construct::Type::String;

my %types = ( 'I' => 'int', 'N' => 'num', 'P' => 'obj', 'S' => 'str');

sub new
{
  my $class = shift;
  my ($type) = @_;

  my $token;

  if (UNIVERSAL::isa($type, 'Jako::Token')) {
    $token = $type;
    $type = $type->text;
  }
  else {
    $type = $types{$type};
  }

  return Jako::Construct::Type::Integer->new($token) if $type eq 'int';
  return Jako::Construct::Type::Number->new($token)  if $type eq 'num';
  return Jako::Construct::Type::Object->new($token)  if $type eq 'obj';
  return Jako::Construct::Type::String->new($token)  if $type eq 'str';

  confess "Unable to create object for type '$type'!";
}

sub token
{
  return shift->{TOKEN};
}

sub code
{
  return shift->{CODE};
}

sub name
{
  return shift->{NAME};
}

sub imcc
{
  return shift->{IMCC};
}

1;

