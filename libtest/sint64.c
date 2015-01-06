/*
 * DO NOT MODIFY THIS FILE.
 * Thisfile generated from similar file libtest/sint8.c
 * all instances of "int8" have been changed to "int64"
 */
#include "ffi_platypus.h"

extern int64_t
sint64_add(int64_t a, int64_t b)
{
  return a + b;
}

extern int64_t*
sint64_inc(int64_t *a, int64_t b)
{
  *a += b;
  return a;
}

extern int64_t
sint64_sum(int64_t list[10])
{
  int i;
  int64_t total;
  for(i=0,total=0; i<10; i++)
  {
    total += list[i];
  }
  return total;
}

extern void
sint64_array_inc(int64_t list[10])
{
  int i;
  for(i=0; i<10; i++)
  {
    list[i]++;
  }
}

extern int64_t *
sint64_static_array(void)
{
  static int64_t foo[] = { -1,2,-3,4,-5,6,-7,8,-9,10 };
  return foo;
}

