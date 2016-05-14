#ifndef __GNUC__
#error Doit etre compile avec GNUC
#endif
#include<limits.h>
#include<stdlib.h>
#include<gmp.h>
#ifndef int64_h
#define int64_h

#if __WORDSIZE == 64
typedef long int64;
#define MAX64 922337203685477580
#else
typedef long long int64;
#define MAX64 9223372036854775807LL
#endif

int root_n(int64,int);

inline int64 root(int64 x)  {return root_n(x,2);}

inline int min(int u, int v) {
  if (v < u)
    return v;
  else return u;
}

inline int min(int64 u, int v) {
  if (v < u)
    return v;
  else return u;
}

inline int min(int u, int64 v) {
  if (v < u)
    return v;
  else return u;
}

inline int64  min(int64 u, int64 v) {
  if (v < u)
    return v;
  else return u;
}

inline int max(int u, int v) {
  if (v < u)
    return u;
  else return v;
}

inline int64  max(int u, int64 v) {
  if (v < u)
    return u;
  else return v;
}

inline int64  max(int64 u, int v) {
  if (v < u)
    return u;
  else return v;
}

inline int64  max(int64 u, int64 v) {
  if (v < u)
    return u;
  else return v;
}

int sqrt(int64 x);

void atolong(int64& x, char* s);

/*
inline void div(int64& u, int d, int64& q, int& r) {
  q = u/d;
  r = u%d;
}
*/
void div(int64& u, int d, int64& q, int& r);

inline int non_zero(int64 u) {return u != 0;}
//int root_n(int64,int);
int pow25(int64 x);
int64 root(int64);

void inline submul_int(int64& res, int64& x, int a) {
  res -= x*a;
}

void inline addmul_int(int64& res, int64& x, int a) {
  res += x*a;
}

inline void remdivlong64(int64& r, int64& u, int64 d) {
  int64 q = u/d;
  r = u -q*d;
} 
#endif

