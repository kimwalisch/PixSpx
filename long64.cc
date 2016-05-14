// -*- C++ -*-
#include<iostream>
using namespace std;
#include"long64.h"
#include"globals.h"
#include<gmp.h>

//static mpz_t tmp1;

static int64 tmp;

#if FUNCTION == 1
int64& F(int64& u) {
  tmp=u/PK;
  int r = u%PK;
  tmp *=FK;
  if (r)
    tmp += 1+PRED[r-1];
  return tmp;
}
#elif FUNCTION == 2
static int64 tmp1;
static int64 tmp2;
int64& F(int64& u)  {
  tmp=u/PK;
  int r = u%PK;
  //  cout << "u = " << u << "    q = " << tmp << "  r = " << r << "\n";
  tmp2 = tmp;
  tmp2 -= 1;
  tmp2 *= PK*(FK/2) ;
  tmp2 += SK;
  tmp2 *= tmp;
  //  cout << "tmp2 = " << tmp << endl;
  if (r) {
    tmp1 = tmp;
    tmp1 *=PK;
    for (int k=0; CLASS[k] <= r; k++)
      {
	tmp2 += tmp1;
	tmp2 += CLASS[k];
      }
  }
  return tmp2;
}
#else
#error FUNCTION n est pas defini
#endif



