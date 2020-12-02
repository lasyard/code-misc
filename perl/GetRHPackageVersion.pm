package GetRHPackageVersion;

use strict;
use warnings;

sub getRHPackageVersion {
    my ($package) = @_;
    my $stdout = qx/rpm -q $package/;
    my $regVer = qr/\d+(?:\.\d+)*/;
    my $version;
    for (split "\n", $stdout) {
        ($version) = $stdout =~ /$package-($regVer)/;
        last if defined($version);
    }
    return $version;
}

1;
