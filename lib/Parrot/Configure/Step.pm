package Parrot::Configure::Step;

use strict;
use Exporter;
use File::Copy ();
use vars qw(@ISA @EXPORT @EXPORT_OK %EXPORT_TAGS);

@ISA=qw(Exporter);

@EXPORT=();

@EXPORT_OK=qw(prompt genfile copy_if_diff move_if_diff
              cc_gen cc_build cc_run cc_clean cc_run_capture);

%EXPORT_TAGS=(
	inter => ['prompt'],
	auto  => [qw(cc_gen cc_build cc_run cc_clean cc_run_capture)],
	gen   => [qw(genfile copy_if_diff move_if_diff)]
);

my $redir_err = (($ENV{COMSPEC} || "")=~ /command\.com/i) ? "" : "2>&1";

#Configure::Data->get('key')
#Configure::Data->set('key', 'value')
#Configure::Data->keys()
#Configure::Data->dump()

sub prompt {
	my($message, $value)=@_;

	print("$message [$value] ");

	chomp(my $input=<STDIN>);

	while($input =~ s/:add\{([^}]+)\}//) {
		$value .= $1;
	}

	while($input =~ s/:rem\{([^}]+)\}//) {
		$value =~ s/\Q$1\E//;
	}

	if($input) {
		$value =  $input;
	}

	return $value;
}

sub file_checksum {
    my ($filename, $ignorePattern) = @_;
    open(FILE, "< $filename") or die "Can't open $filename: $!";
    my $sum = 0;
    while (<FILE>) {
        next if defined($ignorePattern) && /$ignorePattern/;
        $sum += unpack("%32C*", $_);
    }
    close FILE;
    return $sum;
}

sub copy_if_diff {
    my ($from, $to, $ignorePattern) = @_;

    # Don't touch the file if it didn't change (avoid unnecessary rebuilds)
    if (-r $to) {
        my $from_sum = file_checksum($from, $ignorePattern);
        my $to_sum = file_checksum($to, $ignorePattern);
        return if $from_sum == $to_sum;
    }

    File::Copy::copy($from, $to);

    # Make sure the timestamp is updated
    my $now=time;
    utime $now, $now, $to;
}

sub move_if_diff {
    my ($from, $to, $ignorePattern) = @_;
    copy_if_diff($from, $to, $ignorePattern);
    unlink $from;
}

sub genfile {
	my($source, $target, %options)=@_;

	open IN , "< $source" or die "Can't open $source: $!";
	# don't change the name of the outfile handle
	# feature.pl / feature_h.in need OUT
	open OUT, "> $target.tmp" or die "Can't open $target.tmp: $!";

        if ($options{commentType}) {
            my @comment = ("DO NOT EDIT THIS FILE",
                           "Generated by lib/Parrot/Configure/Step.pm from $source");
            if ($options{commentType} eq '#') {
                $_ = "# $_\n" foreach (@comment);
            } elsif ($options{commentType} eq '/*') {
                $_ = " * $_\n" foreach (@comment);
                $comment[0] =~ s!^ \*!/*!;
                $comment[-1] =~ s!$! */!;
            } else {
                die "Unknown comment type '$options{commentType}'";
            }

            foreach (@comment) { print OUT $_; }
        }

	while(<IN>) {
		if (/^#perl/ && $options{feature_file}) {
			local $/ = undef;
			$_ = <IN>;
			s{
			    \$\{(\w+)\}
			}{Configure::Data->get("$1")}gx;
			eval;
			die $@ if $@;
			last;

		}
		s{
                    \$\{(\w+)\}
                }{Configure::Data->get($1)}egx;
		print OUT;
	}

	close IN  or die "Can't close $source: $!";
	close OUT or die "Can't close $target: $!";

        move_if_diff("$target.tmp", $target, $options{ignorePattern});
}

sub cc_gen {
	my($source)=@_;

	genfile($source, "test.c");
}

sub cc_build {
	my($cc, $ccflags, $ldout, $o, $link, $linkflags, $cc_exe_out, $exe, $libs)=
		Configure::Data->get( qw(cc ccflags ld_out o link linkflags cc_exe_out exe libs) );

	system("$cc $ccflags -I./include -c test.c >test.cco $redir_err") and die "C compiler failed (see test.cco)";

	system("$link $linkflags test$o ${cc_exe_out}test$exe $libs >test.ldo $redir_err") and die "Linker failed (see test.ldo)";
}

sub cc_run {
	my $exe=Configure::Data->get('exe');
    my $slash=Configure::Data->get('slash');
    if (defined($_[0]) && length($_[0])) {
	    `.${slash}test$exe $_[0]`;
    }
    else {
	    `.${slash}test$exe`;
    }
}

sub cc_run_capture {
	my $exe=Configure::Data->get('exe');
    my $slash=Configure::Data->get('slash');
    if (defined($_[0]) && length($_[0])) {
	    `.${slash}test$exe $_[0] $redir_err`;
    }
    else {
	    `.${slash}test$exe $redir_err`;
    }
}

sub cc_clean {
	unlink map "test$_",
		qw( .c .cco .ldo ),
		Configure::Data->get( qw( o exe ) );
}

1;
