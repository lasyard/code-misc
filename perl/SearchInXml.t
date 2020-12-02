use strict;
use warnings;

use Test::More;
use XML::Simple;

use SearchInXml;

can_ok('SearchInXml', qw(SearchInXml));

my $xml = XMLin(<<END
    <xml>
    <section><section label="foo"></section></section>
    <section>
    </section>
    <section label="bar"><section></section></section>
    </xml>
END
);

diag(explain $xml);

is(SearchInXml::SearchInXml($xml, sub {
            my ($x, $ref) = @_;
            return 1 if $ref eq 'section' and ref($x) eq 'HASH' and exists($x->{label}) and $x->{label} eq 'foo';
            return '';
        }), $xml->{section}[0]{section}, 'Search for section with label "foo"');

is(SearchInXml::SearchInXml($xml, sub {
            my ($x, $ref) = @_;
            return 1 if $ref eq 'section' and ref($x) eq 'HASH' and exists($x->{label}) and $x->{label} eq 'bar';
            return '';
        }), $xml->{section}[2], 'Search for section with label "bar"');

done_testing();
