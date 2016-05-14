#include"globals.h"

//-------------------------------------------------------------------------
//
//   S1 : feuilles speciales binaires avec x^(1/3) < m=p <= y
//
//-------------------------------------------------------------------------

static longval Somme1;
longval* Sx;

longval& S1() {
  Sx = new longval[1+pi_y];
  Sx[K] = 0;
  for (int k=K+1; k <= pi(y); k++) {
    Sx[k]  = Sx[k-1];
    Sx[k] += fint(prime(k));
  }

  Somme1  = Sx[pi(y)];
  Somme1 -= Sx[pi_x3];
  Somme1 *= Sx[pi(y)];
  // Reste a retrancher la somme des f(p)S(p) x^(1/3) < p \le y
  for (int k = 1+pi_x3; k <= pi(y); k++)
    {
      submul_int(Somme1,Sx[k],fint(prime(k)));
    }
  cerr << "S1() = " << Somme1 << endl;
  chronometre();
  un_trait();
  return Somme1;
}

//-------------------------------------------------------------------------
