package My::AutoConf;

use strict;
use warnings;
use Config::AutoConf;
use Config;
use File::Spec;
use FindBin;

my $root = $FindBin::Bin;

my $prologue = <<EOF;
#ifdef HAVE_DLFCN_H
#include <dlfcn.h>
#endif
#ifdef HAVE_ALLOCA_H
#include <alloca.h>
#endif
EOF

my @probe_types = split /\n/, <<EOF;
char
short
int
long
long long
size_t
dev_t
ino_t
mode_t
nlink_t
uid_t
gid_t
off_t
blksize_t
blkcnt_t
time_t
uint8_t
int8_t
uint16_t
int16_t
uint32_t
int32_t
uint64_t
int64_t
int_least8_t
int_least16_t
int_least32_t
int_least64_t
uint_least8_t
uint_least16_t
uint_least32_t
uint_least64_t
ptrdiff_t
wchar_t
wint_t
float
double
long double
EOF

sub build_configure
{
  my($mb) = @_;
  
  my $ac = Config::AutoConf->new;

  $ac->check_prog_cc;
  
  foreach my $header (qw( stdlib stdint sys/types sys/stat unistd alloca dlfcn limits stddef wchar signal inttypes ))
  {
    $ac->check_header("$header.h");
  }
  
  if($ac->check_decl('RTLD_LAZY', { prologue => $prologue }))
  {
    $ac->define_var( HAVE_RTLD_LAZY => 1 );
  }
  
  if($ac->check_decl('alloca', { prologue => $prologue }))
  {
    $ac->define_var( HAVE_ALLOCA => 1 );
  }
  
  foreach my $lib (map { s/^-l//; $_ } split /\s+/, $Config{perllibs})
  {
    if($ac->check_lib($lib, 'dlopen'))
    {
      $ac->define_var( 'HAVE_dlopen' => 1 );
      last;
    }
  }

  my %size;
  
  foreach my $type (@probe_types)
  {
    my $size = $ac->check_sizeof_type($type);
    $size{$type} = $size if $size;
  }
  
  $ac->write_config_h( File::Spec->rel2abs( File::Spec->catfile( 'xs', 'ffi_platypus_config.h' )));  
}

1;
