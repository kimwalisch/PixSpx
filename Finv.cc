#include<iostream>
#include<mpfr.h>
#include"globals.h"
#include"longreal.h"
using namespace std;

// La fonction F = sum(f(n) | n <= u, (n,PK)=1)
// lorsque f est la fonction
// f= n-> 1
// f= n-> n
// f= n-> 1/n
// Ici c'est f(n)= 1/n

void div(longint&, int, int64&, int&);
void inverse(LongReal& res, LongGmp& u);

static longint q;
int r;


/*
G(q,k,p) = {
 local(t1,somp);
 t1 = log(30.0*q+cvec[k])/30.0 + 1.0/(60*q+2*cvec[k]);
 somp = sum(j=1,p,bvec[2*j]/(2*j)*(30.0^(2*j-1))/(30.0*q+cvec[k])^(2*j));
 return(t1+gvec[k]-somp)
}
*/

longval& G(int64 q);
void inverse(longval&, longint&);
//  LongReal& inverse(longint& u);

static longint t1;
static longint t2;

char gmstr[95] = "0.59254092477441549583241511021557033635274802340764880247252170241748086460895421630324046325";

longval gamma30;

longval bern[5];  
// 1/30 [bernoulli[1],bernoulli[2]/2,bernoulli[4]/4,bernoulli[6]/6]



longval c_PK[FK]; // Tableau contenant les valeurs reelles c/30
                  // pour c parcourant les 8 classes inversibles
                  // 1,7,11,13,17,19,23,29 modulo 30.   

void make_c_PK() {
  for (int i=0; i < FK; i++)
    {
      c_PK[i] = CLASS[i];
      c_PK[i] /= PK;
    }
}

void init_Finv() {
  mpf_set_str(gamma30.mp,gmstr,10);
  //cout << "gamma30 = " << gamma30 << endl;

  bern[0]  =       +1;
  bern[0] /=     2*PK;
  bern[1]  =       -1;
  bern[1] /=   6*PK*2;
  bern[2]  =       +1;
  bern[2] /=  30*PK*4;
  bern[3]  =       -1;
  bern[3] /=  42*PK*6;
  bern[4]  =       +1;
  bern[4] /=  30*PK*8;
  //cout << "bern[0] = " << bern[0] << endl;
  //cout << "bern[1] = " << bern[1] << endl;
  //cout << "bern[2] = " << bern[2] << endl;
  //cout << "bern[3] = " << bern[3] << endl;
  make_c_PK();
}


static longval t0,tk,Tk,uk,uk2;
static longval gres,som,reslog,somlog;

longval& G(longint& q) {
  //cout << "In res avec q= " << q << endl;
  gres = gamma30;
  somlog = 0;
  t0  = q;
  //cout << "Apres t0 = q t0 = " << t0 << endl;
  t0 -= 1;
  //cout << "Apres t0 -= 1 t0 = " << t0 << endl;
  for (int k=0; k < FK; k++) {
    //cout << "\nPour k = " << k << endl;
    som = 0;
    tk   = t0;
    tk  += c_PK[k];
    //cout << "tk = " << tk << endl;
    Tk   = tk;
    Tk  *= PK;
    //cout << "Tk = " << Tk << endl;
    log(reslog,Tk);
    //cout << "Son log est " << reslog << endl;
    somlog += reslog;
    inverse(uk,tk);            // uk = 1/(q+ck/30);
    uk2   = uk;
    uk2  *= uk;                  // uk2 = uk^2
    //cout << "uk = " << uk << endl;
    //cout << "uk2 = " << uk2 << endl;
    som   += bern[4];
    som  *= uk2;
    som   += bern[3];
    som  *= uk2;
    som  += bern[2];
    som  *= uk2;
    som  += bern[1];
    som  *= uk;
    som  += bern[0];
    som  *= uk;
    gres += som;    
  }
  somlog /= PK;
  gres += somlog;
  //cout << "Va rendre " << gres << endl;
  return gres;
}


static longint tmp1;
static longval tmp2;
static longval res;

longval& F(longint& u) {
  div(u,PK,q,r);  
  res = G(q);
  if (r) {
    for (int k=0; CLASS[k] <= r; k++)
      {
	tmp1 = q;
	tmp1 *= PK;
	tmp1 += CLASS[k];
	inverse(tmp2,tmp1);
	res  += tmp2;
      }
  }
  //cout << "F va renvoyer " << res << endl;
  return res;
}

