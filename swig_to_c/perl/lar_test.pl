#!/usr/local/bin/perl -W

use strict;
use warnings;

use lib 'build';
use Lar;

my $lar = Lar::Lar_new();

# will crash if path incorrect, should pass a char**
my $error = undef;
my $release = Lar::Lar_first_release_item($lar, "/tmp/releases.rss", $error);

if (!defined($release))
{
    print("Error : $error");
    free($error);
    exit 1;
}

my $crelease = new Lar::CRelease();
Lar::Release_copy_into($release, $crelease);

my $title = Larc::CRelease_title_get($crelease);
my $link = Larc::CRelease_link_get($crelease);
my $description = Larc::CRelease_description_get($crelease);
my $pub_date = Larc::CRelease_pub_date_get($crelease);
print("$title, $link, $description, $pub_date\n");

Lar::Release_delete($release);

Lar::Lar_delete($lar);


