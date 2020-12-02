use strict;
use warnings;

use Test::More;

use ParseConfigs;

can_ok('ParseConfigs', qw(parseConfigs));

my $text = <<'EOS'
key1 = value1
 key2 = value2
key3=value3
 key1 = value4
 key4
 key5 =
= value6
key 7 = value 8
EOS
;

my $configs = ParseConfigs::parseConfigs($text);
is_deeply(
    $configs,
    {
        key1 => ['value1', 'value4'],
        key2 => ['value2'],
        key3 => ['value3'],
        'key 7' => ['value 8'],
    },
    'parseConfigs should return a correct hash reference'
);

done_testing();
