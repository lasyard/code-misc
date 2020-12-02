#!/usr/bin/perl

use strict;
use warnings;
use Data::Dumper;

my @m = (
    [8, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 3, 6, 0, 0, 0, 0, 0],
    [0, 7, 0, 0, 9, 0, 2, 0, 0],
    [0, 5, 0, 0, 0, 7, 0, 0, 0],
    [0, 0, 0, 0, 4, 5, 7, 0, 0],
    [0, 0, 0, 1, 0, 0, 0, 3, 0],
    [0, 0, 1, 0, 0, 0, 0, 6, 8],
    [0, 0, 8, 5, 0, 0, 0, 1, 0],
    [0, 9, 0, 0, 0, 0, 4, 0, 0]
);

sub row_include {
    my ($m, $i, $x) = @_;
    for (@{$m->[$i]}) {
        return 1 if $_ == $x;
    }
    undef;
}

sub col_include {
    my ($m, $j, $x) = @_;
    for (@$m) {
        return 1 if $_->[$j] == $x;
    }
    undef;
}

sub sqr_include {
    my ($m, $i, $j, $x) = @_;
    for my $row (@$m[int($i/3)*3 .. int($i/3)*3+2]) {
        for (@$row[int($j/3)*3 .. int($j/3)*3+2]) {
            return 1 if $_ == $x;
        }
    }
    undef;
}

sub available {
    my ($m, $i, $j) = @_;
    grep !(row_include($m, $i, $_) || col_include($m, $j, $_) ||
        sqr_include($m, $i, $j, $_)), (1..9);
}

sub next_pos {
    my ($m, $i, $j) = @_;
    do {
        $j++;
        if ($j == 9) {
            $i++;
            $j = 0;
        }
        return () if $i == 9;
    } until $m->[$i][$j] == 0;
    ($i, $j);
}

sub solve {
    my ($m, $i, $j) = @_;
    my @n = next_pos($m, $i, $j);
    if (!@n) {
        print Dumper $m;
        return;
    }
    my @a = available($m, $n[0], $n[1]);
    for (@a) {
        $m->[$n[0]][$n[1]] = $_;
        solve($m, $n[0], $n[1]);
        $m->[$n[0]][$n[1]] = 0;
    }
}

my $t1 = time;
solve \@m, 0, -1;
my $t2 = time;
print $t2-$t1;
