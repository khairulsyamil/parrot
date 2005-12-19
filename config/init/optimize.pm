# Copyright: 2001-2005 The Perl Foundation.  All Rights Reserved.
# $Id$

=head1 NAME

config/init/optimize.pm - Optimization

=head1 DESCRIPTION

Enables optimization by adding the appropriate flags for the local
platform to the C<CCFLAGS>.
Should this be part of config/inter/progs.pm ? XXX

=cut

package init::optimize;

use strict;
use vars qw($description $result @args);

use base qw(Parrot::Configure::Step::Base);

use Parrot::Configure::Step;

$description="Enabling optimization...";

@args=qw(verbose optimize);

sub runstep {
    my ($self, $conf) = (shift, shift);

  my ($verbose, $optimize) = @_;
  if ($conf->data->get('optimize')) {
    my($ccflags, $optimize) =
      $conf->data->get(qw(ccflags optimize));
    $ccflags .= " $optimize -DDISABLE_GC_DEBUG=1 -DNDEBUG";

    $conf->data->set(
                         ccflags => $ccflags,
                        );
  }
  else {
    print "(none requested) " if $verbose;
  }
}

1;
