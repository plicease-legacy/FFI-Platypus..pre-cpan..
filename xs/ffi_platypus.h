#ifndef FFI_PLATYPUS_H
#define FFI_PLATYPUS_H

#include <ffi.h>
#include "ffi_platypus_config.h"

#ifdef HAVE_DLFCN_H
#include <dlfcn.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_STDDEF_H
#include <stddef.h>
#endif
#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif
#ifdef HAVE_INTTYPES_H
#include <inttypes.h>
#endif
#ifdef HAVE_ALLOCA_H
#include <alloca.h>
#endif

#ifndef HAVE_RTLD_LAZY
#define RTLD_LAZY 0
#endif

#ifndef HAVE_dlopen

void *ffi_platypus_dlopen(const char *filename, int flag);
char *ffi_platypus_dlerror(void);
void *ffi_platypus_dlsym(void *handle, const char *symbol);
int ffi_platypus_dlclose(void *handle);

#define dlopen(filename, flag) ffi_platypus_dlopen(filename, flag)
#define dlerror() ffi_platypus_dlerror()
#define dlsym(handle, symbol) ffi_platypus_dlsym(handle, symbol)
#define dlclose(handle) ffi_platypus_dlclose(handle)

#endif

typedef enum _platypus_type {
  FFI_PL_FFI = 0,
  FFI_PL_STRING,
  FFI_PL_CUSTOM
} platypus_type;

typedef struct _ffi_pl_type {
  ffi_type *ffi_type;
  platypus_type platypus_type;
  void *arg_ffi2pl;
  void *arg_pl2ffi;
  void *ret_ffi2pl;
  void *ret_pl2ffi;
} ffi_pl_type;

typedef struct _ffi_pl_function {
  void *address;
  void *sv;  /* really a Perl SV* */
  ffi_cif ffi_cif;
  ffi_pl_type *return_type;
  ffi_pl_type *argument_types[0];
} ffi_pl_function;

typedef const char *ffi_pl_string;

#endif
