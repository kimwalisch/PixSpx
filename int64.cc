#include"int64.h"
mpz_t tmp0;

int pow25(int64 x) {
  int u=root_n(x,5);
  return u*u;
}

int root_n(int64 x, int n) {
  mpz_import(tmp0,2,-1,4,0,0,&x);
  mpz_root(tmp0,tmp0,n);
  mpz_export(&x,NULL,-1,8,0,0,tmp0);
  return x;
}

int sqrt(int64 x)
{
  int64 n;
  int64 y = x;
  do
    {
      n = y;
      y = (n + x/n)>>1;
    } while (y < n);
  return n;
}

void atolong(int64& x, char* s){
  x=atoll(s);
}


void div(int64& u, int d, int64& q, int& r) {
  q = u/d;
  r = u%d;
}
