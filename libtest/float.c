#include "libtest.h"
#include "ffi_platypus.h"

EXTERN float
float_add(float a, float b)
{
  return a + b;
}

EXTERN float*
float_inc(float *a, float b)
{
  *a += b;
  return a;
}

EXTERN float
float_sum(float list[10])
{
  int i;
  float total;
  for(i=0,total=0; i<10; i++)
  {
    total += list[i];
  }
  return total;
}

EXTERN void
float_array_inc(float list[10])
{
  int i;
  for(i=0; i<10; i++)
  {
    list[i]++;
  }
}

EXTERN float *
float_static_array(void)
{
  static float foo[] = { -5.5, 5.5, -10, 10, -15.5, 15.5, 20, -20, 25.5, -25.5 };
  return foo;
}

