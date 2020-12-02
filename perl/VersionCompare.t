use strict;
use warnings;

use Test::More;

use VersionCompare;

can_ok('VersionCompare', qw(versionCompare));

my @checks = (
    ['9.0.1', '9.0.2', -1],
    ['9.0.1', '10.0.2', -1],
    ['9.0.1.2', '9.0.2', -1],
    ['9.0.1', '9.0.2.2', -1],
    ['9', '8.0.1.2', 1],
    ['9.0.1', '9.0.1', 0],
    ['9.1alpha', '9.1', 0],
);

for (@checks) {
    is(
        VersionCompare::versionCompare($_->[0], $_->[1]),
        $_->[2],
        $_->[0].' cmp '.$_->[1].' = '.$_->[2]
    );
}

done_testing();
