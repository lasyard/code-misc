use strict;
use warnings;

use Test::More;

use VersionDiff;

can_ok('VersionDiff', qw(versionDiff));

my @checks = (
    ['9.0.1', '9.0.2', [0, 0, -1]],
    ['9.0.1', '10.0.2', [-1, 0, -1]],
    ['9.0.1.2', '9.0.2', [0, 0, -1, 2]],
    ['9.0.1', '9.0.2.2', [0, 0, -1, -2]],
    ['9', '8.0.1.2', [1, 0, -1, -2]],
);

for (@checks) {
    is_deeply(
        VersionDiff::versionDiff($_->[0], $_->[1]),
        $_->[2],
        $_->[0].' - '.$_->[1].' = '."[@{$_->[2]}]"
    );
}

done_testing();
