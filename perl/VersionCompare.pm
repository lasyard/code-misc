package VersionCompare;

use strict;
use warnings;

sub versionCompare{
    my ($a, $b) = @_;
    my @aa = split(/\./, $a);
    my @bb = split(/\./, $b);
    my $i = 0;
    while (1) {
        if (!defined($aa[$i])) {
            return 0 if !defined($bb[$i]);
            return -1;
        }
        return 1 if !defined($bb[$i]) or $aa[$i] > $bb[$i];
        return -1 if $aa[$i] < $bb[$i];
        $i++;
    }
}

1;
