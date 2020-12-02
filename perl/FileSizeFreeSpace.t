use strict;
use warnings;

use Test::More;

use FileSizeFreeSpace;

can_ok('FileSizeFreeSpace', qw(getFileSizeFreeSpace));

my $files = [qw(FileSizeFreeSpace.pm FileSizeFreeSpace.t abc)];

my $results = FileSizeFreeSpace::getFileSizeFreeSpace($files);

diag(explain $results);

ok(exists $results->{'FileSizeFreeSpace.t'} and exists $results->{'FileSizeFreeSpace.pm'},
    'getFileSizeFreeSpace should have all files');
ok(exists $results->{'FileSizeFreeSpace.t'}{size},
    'getFileSizeFreeSpace should have size for files');
ok(exists $results->{'FileSizeFreeSpace.t'}{freeSpace},
    'getFileSizeFreeSpace should have freeSpace for files');
ok(exists $results->{'FileSizeFreeSpace.t'}{mountPoint},
    'getFileSizeFreeSpace should have mountPoint for files');
like($results->{'FileSizeFreeSpace.t'}{size}, qr/^\d+$/,
    'size of files should be numerical');
like($results->{'FileSizeFreeSpace.t'}{freeSpace}, qr/^\d+$/,
    'size of spaces should be numerical');

done_testing();
