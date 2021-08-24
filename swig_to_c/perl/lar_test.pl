#!/usr/local/bin/perl -W

use strict;
use warnings;
use Scalar::Util qw( reftype );

use lib 'build';
use Lar;

my $lar = Lar::Lar_new();

my $release = Lar::Lar_first_release_item($lar, "/tmp/releases.rss");

if (ref($release) ne '_p_Release')
{
    print("Error : $release\n");
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


