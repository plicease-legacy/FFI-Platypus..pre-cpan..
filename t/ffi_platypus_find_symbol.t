use strict;
use warnings;
use Test::More tests => 2;
use File::Spec;
use FFI::Platypus;
use FFI::CheckLib;

my $ffi = FFI::Platypus->new;
$ffi->lib(find_lib lib => 'test', symbol => 'f0', libpath => 'libtest');

my $good = $ffi->find_symbol('f0');
ok $good, "ffi.find_symbol(f0) = $good";

my $bad  = $ffi->find_symbol('bogus');
is $bad, undef, 'ffi.find_symbol(bogus) = undef';
