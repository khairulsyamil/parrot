#! perl -w
#

open INTERP, "> interp_guts.h" or die "Can't open interp_guts.h, $!/$^E";

open OPCODES, "opcode_table" or die "Can't open opcode_table, $!/$^E";

print INTERP <<CONST;
/*
 *
 * interp_guts.h
 *
 * this file is autogenerated by build_interp_starter.pl
 *
 * Best not edit it
 */

#define BUILD_TABLE(x) do { \\
CONST

while (<OPCODES>) {
    chomp;
    s/#.*$//;
    s/^\s+//;
    next unless $_;
    ($num, $name) = split /\s+/;
    print INTERP "\tx[$num] = $name; \\\n";
    $num++;
}
print INTERP "} while (0);\n";
