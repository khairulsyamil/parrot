
package Configure::Step;

use strict;
use vars qw($description @args);
use Parrot::Configure::Step ':auto';

$description = "Determining some signal stuff...";

@args=qw(miniparrot);

sub runstep {
    my ($miniparrot) = @_;
    Configure::Data->set(
	has___sighandler_t => undef,
	has_sigaction    => undef,
	has_setitimer    => undef
    );
    if (defined $miniparrot) {
	return;
    }

    if (Configure::Data->get('i_malloc')) {
	Configure::Data->set('malloc_header', 'malloc.h');
    }
    else {
	Configure::Data->set('malloc_header', 'stdlib.h');
    }

    cc_gen('config/auto/signal/test_1.in');
    eval { cc_build(); };
    unless ($@ || cc_run() !~ /ok/) {
	Configure::Data->set(
	    has___sighandler_t => 'define'
	);
	print " (__sighandler_t)";
    }
    cc_clean();

    cc_gen('config/auto/signal/test_2.in');
    eval { cc_build(); };
    unless ($@ || cc_run() !~ /ok/) {
	Configure::Data->set(
	    has_sigaction => 'define'
	);
	print " (sigaction)";
    }
    cc_clean();

    Configure::Data->set('malloc_header', undef);

    cc_gen('config/auto/signal/test_itimer.in');
    eval { cc_build(); };
    unless ($@ || cc_run() !~ /ok/) {
	Configure::Data->set(
	    has_setitimer    => 'define'
	);
	print " (setitimer) ";
    }
    cc_clean();
    # now generate signal constants
    open O, ">runtime/parrot/include/signal.pasm" or die
    "Cant write runtime/parrot/include/signal.pasm";
    print O <<"EOF";
# DO NOT EDIT THIS FILE.
#
# This file is generated automatically by config/auto/signal.pl
#
# Any changes made here will be lost.
#
EOF
    use Config;
    my ($i, $name);
    $i = 0;
    foreach $name (split(' ', $Config{sig_name})) {
	print O ".constant SIG$name\t$i\n" if $i;
	$i++;
    }
    close O;
}
1;
