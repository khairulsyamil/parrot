#! perl -w
################################################################################
# Copyright: 2001-2003 The Perl Foundation.  All Rights Reserved.
# $Id$
################################################################################

=head1 NAME

build_tools/ops2pm.pl - Generate Perl module from operation definitions

=head1 SYNOPSIS

    % perl build_tools/ops2pm.pl ops/core.ops ops/bit.ops ...

=head1 DESCRIPTION

The first .ops file on the command line is read in and its name is used
to determine the name of the Perl module that will contain the op info.

Any remaining .ops files on the command line are read in, and their op
info objects are appended, in order, to the op info array obtained from
the first .ops file.

=head2 WARNING

Generating a combined Perl module for a set of .ops files that you do
not later turn into a combined opcode table with the same content and
order is a recipe for disaster.

XXX: The original design of the .ops processing code was intended to be
a read-only representation of what was in a particular .ops file. It was
not originally intended that it was a mechanism for building a bigger
virtual .ops file from multiple physical .ops files. This code does half
of that job (the other half is getting them to compile together instead
of separately in a *_ops.c file). You can see evidence of this by the
way this code reaches in to the internal OPS hash key to do its
concatenation, and the way it twiddles each op's CODE hash key after
that. If the op and oplib Perl modules are going to be used for
modifying information read from .ops files in addition to reading it,
they should be changed to make the above operations explicitly
supported. Otherwise, the Parrot build and interpreter start-up logic
should be modified so that it doesn't need to concatenate separate .ops
files.

=head1 SEE ALSO

F<build_tools/ops2c.pl>.

=cut

################################################################################

use strict;
use lib 'lib';
use Parrot::OpsFile;

use Data::Dumper;
$Data::Dumper::Useqq  = 1;
#$Data::Dumper::Terse  = 1;
#$Data::Dumper::Indent = 0;

my $moddir  = "lib/Parrot/OpLib";

sub Usage {
    print STDERR <<_EOF_;
usage: $0 input.ops [input2.ops ...]
_EOF_
    exit;
}

Usage() unless @ARGV;


#
# Use the first .ops file to determine the output file name, and read in its
# ops:
#

my $file = shift @ARGV;

my ($base)  = ($file =~ m{(\w+)\.ops$});
my $package = "core";
my $module  = "lib/Parrot/OpLib/core.pm";

die "$0: Could not find ops file '$file'!\n" unless -e $file;
my $ops = new Parrot::OpsFile $file;
die "$0: Could not read ops file '$file'!\n" unless defined $ops;


#
# Copy the ops from the remaining .ops files to the object just created.
#

my %seen;

for $file (@ARGV) {
    if ($seen{$file}) {
      print STDERR "$0: Ops file '$file' mentioned more than once!\n";
      next;
    }
    $seen{$file} = 1;

    die "$0: Could not find ops file '$file'!\n" unless -e $file;
    my $temp_ops = new Parrot::OpsFile $file;
    die "$0: Could not read ops file '$file'!\n" unless defined $temp_ops;

    die "OPS invalid for $file" unless ref $temp_ops->{OPS};
    push @{$ops->{OPS}}, @{$temp_ops->{OPS}};
    $ops->{PREAMBLE} .= "\n" . $temp_ops->{PREAMBLE};
}


# Renumber the ops based on ops.num
#

&load_op_map_file;

my $cur_code = 0;
for(@{$ops->{OPS}}) {
    $_->{CODE} = find_op_number($_->full_name);
}

my @sorted = sort { $a->{CODE} <=> $b->{CODE} } (@{$ops->{OPS}} );
@{$ops->{OPS}} = @sorted;

#
# Open the output file:
#

if (! -d $moddir) {
    mkdir($moddir, 0755) or die "$0: Could not mkdir $moddir: $!!\n";
}
open MODULE, ">$module"
  or die "$0: Could not open module file '$module' for writing: $!!\n";


#
# Print the preamble for the MODULE file:
#

my $version = $ops->version;

my $preamble = <<END_C;
#! perl -w
#
# !!!!!!!   DO NOT EDIT THIS FILE   !!!!!!!
#
# This file is generated automatically from '$file'.
# Any changes made here will be lost!
#

use strict;

package Parrot::OpLib::$package;

use vars qw(\$VERSION \$ops \$preamble);

\$VERSION = "$version";

END_C

print MODULE $preamble;
print MODULE Data::Dumper->Dump([ $ops->preamble, [$ops->ops ]],
          [ qw($preamble $ops) ]);

print MODULE <<END_C;

1;
END_C

sub find_op_number {
  my $opname = shift;
  if (exists $ParrotOps::optable{$opname}) {
    return $ParrotOps::optable{$opname};
  } else {
    my $n = $ParrotOps::optable{$opname} = ++$ParrotOps::max_op_num;
    warn "$opname\t$n\tnot mentioned in ops.num\n";
    return $n;
  }
}

sub load_op_map_file {
  my $file = shift;

  if (!defined $file) {
    $file = "ops/ops.num";
  }

  my ($name, $number);

  if (!defined $ParrotOps::max_op_num) {
    $ParrotOps::max_op_num = 0;
  }

  local *OP;
  open OP, "< $file" or die "Can't open $file, error $!";

  while (<OP>) {
    chomp;
    s/#.*$//;
    s/\s*$//;
    s/^\s*//;
    next unless $_;
    ($name, $number) = split(/\s+/, $_);
    $ParrotOps::optable{$name} = $number;
    if ($number > $ParrotOps::max_op_num) {
      $ParrotOps::max_op_num = $number;
    }
  }
  close OP;
  return;
}

exit 0;

