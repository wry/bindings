#!/usr/bin/perl -W

use strict;
use warnings;

use lib 'obj';
use hellob;

my $arg = $ARGV[0] || 0;

print hellob::hello($arg), "\n";
