package t::APL;

# Fail a little more gracefully for those without Test::Base installed.

BEGIN {
  eval {
    require Test::Base;
    import Test::Base qw/ -Base /;
  };
  if ($@) {
    plan(skip_all => "APL tests require Test::Base.;");
    exit 0;
  }
}

use Parrot::Config;
use Parrot::Test;

our @EXPORT = qw(run_apl_is);

BEGIN {
  # APL *really* needs unicode to function, bail out if we don't have it.
  if (!$PConfig{has_icu}) {
    plan skip_all => "No unicode library available.";
    exit 0;
  }
}

filters {
  output => qw/ chomp /
};


# Note - we don't just use the special SKIP entry in the DATA stream because
# it doesn't actually output the skipped test in the TAP output. It just
# fails to run the test.

# mark todo tests with TODO - but, unless an environment variable is set,
# skip the tests - speed things up for end users, give developers the ability
# to easily see if anything new is passing.

sub run_apl_is() {
  foreach my $block (blocks) {
    my $apl    = $block->APL;
    my $output = $block->out . "\n"; # XXX a slight hack
    my $todo   = $block->todo;
    if (defined($todo)) {
      if (! $todo) {
        $todo = "not implemented";
      }
      if ($ENV{APLDEV}) {
        TODO: {
          local $TODO = $todo;
          Parrot::Test::language_output_is('APL', $apl, $output, $block->name);
        }
      } else {
        SKIP: {
          skip("not implemented", 1);
          Parrot::Test::language_output_is('APL', $apl, $output, $block->name);
        }
      }
    } else {
      Parrot::Test::language_output_is('APL', $apl, $output, $block->name);
    }
  }
}
