#include<iostream>
#include<gmp.h>
#include"longreal.h"
#include"globals.h"

using namespace std;
const int SIZEBUF=1000;
static char buff[SIZEBUF];

static LongReal tmp;
LongReal tmp1;
LongReal tmp2;
LongReal tmp3;

void atolong(LongReal&x, char* str) {x = str;}

ostream& operator <<(ostream &os,LongReal x) {
  os << x.str();
  return os;
}

const char* LongReal::str(int sz) {
  mp_exp_t exponent;
  buff[0] = '0';
  buff[1] = '.';
  mpf_get_str(&buff[2],&exponent,10,sz,mp);
  buff[sz+1] = '*';
  buff[sz+2] = '1';
  buff[sz+3] = '0';
  buff[sz+4] = '^';
  itoa(exponent,10,&buff[sz+5]);
  return(buff);
}



const LongReal& operator -(LongReal& a, LongReal& b) {
  mpf_sub(tmp1.mp,a.mp,b.mp);
  return tmp1;
}

void addmul_int(LongReal& res, LongReal& u, LongReal& a) {
  mpf_mul(tmp1.mp,u.mp,a.mp);
  mpf_add(res.mp,res.mp,tmp1.mp);
}

void submul_int(LongReal& res, LongReal& u, LongReal& a) {
  mpf_mul(tmp1.mp,u.mp,a.mp);
  mpf_sub(res.mp,res.mp,tmp1.mp);
}

LongReal fres;

LongReal& fint(int n) {
  mpf_set_si(tmp3.mp,n);
  mpf_ui_div(fres.mp,1,tmp3.mp);
  return fres;
}

LongReal& f64(int n) {
  mpf_set_si(tmp3.mp,n);
  mpf_ui_div(fres.mp,1,tmp3.mp);
  return fres;
}

LongReal& f64(int64 n) {
  double nd = n;
  mpf_set_d(tmp3.mp,nd);
  mpf_ui_div(fres.mp,1,tmp3.mp);
  return fres;
}

static LongReal invtmp;

void inverse (LongReal & res, LongGmp& u) {
  mpf_set_z(invtmp.mp, u.mp);
  mpf_ui_div(res.mp, 1, invtmp.mp);
}
