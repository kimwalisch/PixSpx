//#include"longint.h"
#include"globals.h"
#include"S2.h"
//-------------------------------------------------------------------------
//
//    La contribution des feuilles speciales non criblees
//    celles pour lequele x^(1/4) < p <= x^(1/3)
//
//-------------------------------------------------------------------------
longval Somme2;

longval& S2() {
  cerr << "CALCUL DE S2\n";
  Somme2 += compute_U();
  Somme2 += compute_V();
  cerr << "S2() = sommeU + sommeV = " << Somme2 << endl <<endl;
  chronometre();
  un_trait();
  return Somme2;
}

//-------------------------------------------------------------------------
//   SommeU feullles speciales bianires avec x^(1/4) < p <= x^(1/3)
//   et m=q > x/p^2
//
//   Contribution des feuiles speciales de plus petit facteur p
//   x^(1/4)  < p <= x^(1/3) et telles que m > x/p^2
//   ce qui implique que m est premier, m=q. 
//   Cette contribution est donc   U = sum_{x^(1/4) < p <= x^(1/3) 
//          f(p) sum_{p < q <= y, x/p^2 < q} f(q) Phi(x/pq,p-1)
//   La condition q > x/p^2 implique p^2 > x/q >= x/y, donc
//   p > (x/y)^(1/2)
//   On a donc U = sum_{(x/y)(1/2) < p <= x^(1/3)
//        f(p) sum_{x/p^2 < q <= y} f(q) Phi(x/pq,p-1)
//   et enfin, puisque x/pq < p chaque valeur de Phi est reduite a 1
//   U = sum_{(x/y)(1/2) < p <= x^(1/3) f(p) sum_{x/p^2 < q <= y} f(q)
//   U = sum_{(x/y)(1/2) < p <= x^(1/3) f(p) S(y) - S(x/p^2)
//
//-------------------------------------------------------------------------

static longval SommeU;
static longint xp2_long;

longval& compute_U() {
  SommeU  = Sx[pi_x3];
  SommeU -= Sx[pi_sqrt_x_y];
  SommeU *= Sx[pi_y];
  for (int k = 1+pi_sqrt_x_y; k <= pi_x3; k++)
    {
      int p = prime(k);
      xp2_long =x/p;
      int xp2 = xp2_long/p;
      submul_int(SommeU,Sx[pi(xp2)],fint(p));
    }
  cerr << "SommeU = " << SommeU << endl;
  return SommeU;
}
