use strict;
use warnings;

use Test::More;

use GetRHPackageVersion;

can_ok('GetRHPackageVersion', qw(getRHPackageVersion));

my @checks = (
    ['glibc', 1],
    ['glib', 1],
    ['foo', undef],
);

for (@checks) {
    my $package = $_->[0];
    my $version = GetRHPackageVersion::getRHPackageVersion($package);
    if ($_->[1]) {
        if (ok(defined($version), 'Version exists for '.$package.'.')) {
            diag('Version of '.$package.' is '.$version.'.');
            like($version, qr/\d+(?:\.\d+)*/, 'Version is number and dot.');
        }
    } else {
        is($version, undef, 'Version is undef for '.$package.'.');
    }
}

done_testing();
