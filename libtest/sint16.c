/*
 * DO NOT MODIFY THIS FILE.
 * Thisfile generated from similar file libtest/sint8.c
 * all instances of "int8" have been changed to "int16"
 */
#include "ffi_platypus.h"

extern int16_t
sint16_add(int16_t a, int16_t b)
{
  return a + b;
}

extern int16_t*
sint16_inc(int16_t *a, int16_t b)
{
  *a += b;
  return a;
}

extern int16_t
sint16_sum(int16_t list[10])
{
  int i;
  int16_t total;
  for(i=0,total=0; i<10; i++)
  {
    total += list[i];
  }
  return total;
}

extern void
sint16_array_inc(int16_t list[10])
{
  int i;
  for(i=0; i<10; i++)
  {
    list[i]++;
  }
}

extern int16_t *
sint16_static_array(void)
{
  static int16_t foo[] = { -1,2,-3,4,-5,6,-7,8,-9,10 };
  return foo;
}

