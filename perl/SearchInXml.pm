package SearchInXml;

use strict;
use warnings;

sub SearchInXml {
    my ($xml, $test, $refKey) = @_;
    $refKey //= '';
    return $xml if $test->($xml, $refKey);
    if (ref($xml) eq 'HASH') {
        keys %$xml; # rewind
        while (my ($key, $value) = each %$xml) {
            my $res = SearchInXml($xml->{$key}, $test, $key);
            return $res if $res;
        }
    } elsif (ref($xml) eq 'ARRAY') {
        for (@$xml) {
            my $res = SearchInXml($_, $test, $refKey);
            return $res if $res;
        }
    }
    return '';
}

1;
