#include<iostream>
#include"longgmp.h"
#include<gmp.h>
using namespace std;
const int SIZEBUF=1000;
static char buff[SIZEBUF];

static LongGmp tmp;
static LongGmp tmp1;
static LongGmp tmp2;

gmp_randstate_t randseed;

void atolong(LongGmp&x, char* str) {x = str;}

ostream& operator<<(ostream &os,LongGmp x) {
  char* str=&buff[0];
  mpz_get_str(str,10,x.mp);
  os << str;
  return os;
}

LongGmp& root_n(LongGmp& x, int n) {
  mpz_root(tmp1.mp,x.mp,n);
  return tmp1;
}

/*
int pow25 (LongGmp& x) {
  int u;
  mpz_mul(tmp1.mp,x.mp,x.mp);
  mpz_root(tmp1.mp,tmp1.mp,5);
  mpz_export(&u,NULL,-1,4,0,0,tmp1.mp);
  return u;
}
*/

int pow25 (LongGmp& x) {
  int u;
  mpz_root(tmp1.mp,x.mp,5);
  mpz_mul(tmp1.mp,tmp1.mp,tmp1.mp);
  mpz_export(&u,NULL,-1,4,0,0,tmp1.mp);
  return u;
}

const LongGmp& operator/(LongGmp& x, int y) {
  mpz_tdiv_q_ui(tmp1.mp, x.mp, y);
  return tmp1;
}

const LongGmp& operator/(LongGmp& x, long y) {
  mpz_tdiv_q_ui(tmp1.mp, x.mp, y);
  return tmp1;
}


const LongGmp& operator-(LongGmp& a, LongGmp& b) {
  mpz_sub(tmp1.mp,a.mp,b.mp);
  return tmp1;
}

void addmul_int(LongGmp& res, LongGmp& u, int a) {
  mpz_addmul_ui(res.mp, u.mp, a);
}

void submul_int(LongGmp& res, LongGmp& u, int a) {
  mpz_submul_ui(res.mp, u.mp, a);
}



#if __WORDSIZE==32
const LongGmp& operator/(LongGmp& x, int64 u) {
  mpz_import(tmp2.mp,2,-1,4,0,0,(&u));
  mpz_tdiv_q(tmp1.mp, x.mp, tmp2.mp);
  return tmp1;
}


void LongGmp::operator+= (int64 u) {
  mpz_import(tmp2.mp,1,-1,8,0,0,(&u));
  mpz_add(mp,mp,tmp2.mp);
}

void LongGmp::operator-= (int64 u) {
  //  mpz_import(tmp2.mp,2,-1,4,0,0,(&u));
  mpz_import(tmp2.mp,1,-1,8,0,0,(&u));
  mpz_sub(mp,mp,tmp2.mp);
}

void LongGmp::operator*= (int64 u) {
  //  mpz_import(tmp2.mp,2,-1,4,0,0,(&u));
  mpz_import(tmp2.mp,1,-1,8,0,0,(&u));
  mpz_mul(mp,mp,tmp2.mp);
}

void remdivlong64(int64& r, LongGmp& a, int64 d) {
  mpz_import(tmp2.mp,1,-1,8,0,0,&d);
  mpz_tdiv_r(tmp1.mp,a.mp,tmp2.mp);
  mpz_export(&r,NULL,-1,8,0,0,tmp1.mp);
}

void LongGmp::operator/= (int64 u) {
  mpz_import(tmp2.mp,1,-1,8,0,0,(&u));
  mpz_tdiv_q(mp,mp,tmp2.mp);
}


int64 root(LongGmp& x) {
  int64 res;
  mpz_sqrt(tmp1.mp, x.mp);
  mpz_export(&res,NULL,-1,8,0,0,tmp1.mp);
  return res;
}

/*
void div(LongGmp& u, long d, LongGmp& q, long& r) {
  r = mpz_tdiv_q_ui (q.mp, u.mp, d);
}
*/
#endif


void div(LongGmp& u, int d, LongGmp& q, int& r) {
  r = mpz_tdiv_q_ui(q.mp,u.mp,d);
}


#if __WORDSIZE==64
long root(LongGmp& x) {
  cerr << "longroot ZZZZZZ" << endl;
  mpz_sqrt(tmp1.mp, x.mp);
  return mpz_get_si(tmp1.mp);
}


void remdivlong64(long& r, LongGmp& a, long d) {
  r = mpz_tdiv_r_ui(tmp2.mp,a.mp,d);
}
#endif

static LongGmp tmp_rand;

LongGmp& GmpRandb(long n) {
  mpz_urandomb(tmp_rand.mp, randseed, n);
  return tmp_rand;
}
 
