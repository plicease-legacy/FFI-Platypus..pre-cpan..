#include "libtest.h"
#include "ffi_platypus.h"

EXTERN int8_t
sint8_add(int8_t a, int8_t b)
{
  return a + b;
}

EXTERN int8_t*
sint8_inc(int8_t *a, int8_t b)
{
  *a += b;
  return a;
}

EXTERN int8_t
sint8_sum(int8_t list[10])
{
  int i;
  int8_t total;
  for(i=0,total=0; i<10; i++)
  {
    total += list[i];
  }
  return total;
}

EXTERN void
sint8_array_inc(int8_t list[10])
{
  int i;
  for(i=0; i<10; i++)
  {
    list[i]++;
  }
}

EXTERN int8_t *
sint8_static_array(void)
{
  static int8_t foo[] = { -1,2,-3,4,-5,6,-7,8,-9,10 };
  return foo;
}

