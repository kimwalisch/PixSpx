#ifndef arith_tools_h 
#define arith_tools_h 
#include<limits.h>
#include<stdlib.h>

inline long long next_multiple(long long p, long long a) {
  long long r = a % p;
  return (r) ? a + p-r : a;
}

inline long long next_multiple(int p, long long a) {
  long long r = a % p;
  return (r) ? a + p-r : a;
}

inline long long next_multiple(int p, long a) {
  int r = a % p;
  return (r) ? a + p-r : a;
}

inline long long next_multiple(int p, int a) {
  int r = a % p;
  return (r) ? a + p-r : a;
}

inline int compare_abs(int a, int b)
{
  int abs_a = abs(a);
  int abs_b = abs(b);
  if (abs_a == abs_b) return 0;
  return (abs_a < abs_b) ? -1 : 1;
}

void itoa(int n, int Base, char* str);

#endif

