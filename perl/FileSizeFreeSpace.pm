package FileSizeFreeSpace;

use strict;
use warnings;

# Pick strings from an ARRAY of strings, with a limit of joined length
# $words: ref to ARRAY of strings
# $spl: integer, as the lenghth of separator
# $limit: integer, as the length limit
# RETURN: ARRAY of the picked strings, which are shift out from $words
sub _pickWords (\@$$) {
    my ($words, $spl, $limit) = @_;
    my @picked;
    my $length = 0;
    return @picked if length(${$words}[0]) > $limit;
    my $word = shift @$words;
    push @picked, $word;
    $length += length($word);
    while (@$words > 0 and $length+$spl+length(${$words}[0]) < $limit) {
        $word = shift @$words;
        push @picked, $word;
        $length += $spl+length($word);
    }
    return @picked;
}

sub getFileSizeFreeSpace {
    my ($allFiles) = @_;
    my @files = @$allFiles;
    my @trueFiles;
    while (@files) {
        my @picked = _pickWords(@files, 3, 200);
        # ksh's test has no -e parameter, so use -f $f -o -d $f
        my $cmd = 'for f in "'.join('" "', @picked).'"; do test -f $f -o -d $f && echo $f; done';
        my $stdout = qx/$cmd/;
        push @trueFiles, $_ for split "\n", $stdout;
    }
    my %items = map {$_ => undef} @trueFiles;
    @files = @trueFiles;
    while (@files) {
        my @picked = _pickWords(@files, 3, 200);
        my $cmd = 'du -s -k -L "'.join('" "', @picked).'"';
        my $stdout = qx/$cmd/;
        for (split "\n", $stdout) {
            $items{$2}{size} = $1+0 if /^(\d+)\s+(.+)$/;
        }
    }
    @files = @trueFiles;
    while (@files) {
        my @picked = _pickWords(@files, 3, 200);
        my $cmd = 'df -k -P "'.join('" "', @picked).'"';
        my $stdout = qx/$cmd/;
        my $index = 0;
        for (split "\n", $stdout) {
            if (/^\S+\s+\d+\s+\d+\s+(\d+)\s+\S+\s+(\S+)$/) {
                $items{$picked[$index]}{freeSpace} = $1+0;
                $items{$picked[$index]}{mountPoint} = $2;
                $index++;
            }
        }
    }
    return \%items;
}

1;
