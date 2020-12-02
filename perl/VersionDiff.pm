package VersionDiff;

use strict;
use warnings;

sub versionDiff {
    my ($a, $b) = @_;
    my @aa = split(/\./, $a);
    my @bb = split(/\./, $b);
    my $count = @aa;
    if ($count < @bb) {
        $count = @bb;
        @aa[@aa..$count-1] = (0)x$count;
    } else {
        @bb[@bb..$count-1] = (0)x$count;
    }
    return [map {$aa[$_]-$bb[$_]} 0..$count-1];
}

1;
