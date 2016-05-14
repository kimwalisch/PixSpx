#include"typedefs.h"
#include"globals.h"
static longval SommeV1;
static longval tmpv1;
static longval tmpv2;
extern longval* Sx;

static longint tmpl1;
static longint xp2_long;

longval& sommeV1(){
  for (int k = max(1+pi_x4,K+1); k <= pi_x3; k++)
    {
      int p = prime(k);
      int min_x_p2_y;
      tmpl1 = x/p;
      xp2_long = tmpl1/p;
      min_x_p2_y = min(xp2_long,y);
      tmpv1 = Sx[pi(min_x_p2_y)];
      tmpv1 -= Sx[k];
      tmpv2 = Sx[k-1];
      tmpv2 -= 1;
      tmpv1 *= tmpv2;
      addmul_int(SommeV1,tmpv1,fint(p));
    }
  cerr << "SommeV1 = " << SommeV1  << "\n";
  return SommeV1;
}
