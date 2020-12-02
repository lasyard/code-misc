package ParseConfigs;

use strict;
use warnings;

sub parseConfigs {
    my ($text) = @_;
    my %configs;
    my $words = qr/\S+(?: +\S+)*/;
    for (split("\n", $text)) {
        my ($key, $value) = $_ =~ /^\s*($words)\s*=\s*($words)\s*$/;
        next unless defined($key) and defined($value);
        $configs{$key} //= [ ];
        push @{$configs{$key}}, $value;
    }
    return \%configs;
}

1;
