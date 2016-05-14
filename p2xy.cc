#include"presieve30.h"
#include"data.h"
#include"arith_tools.h"
#include"sieve.h"
#include"f.h"
#include"p2xy.h"
#include"longgmp.h"
#define P2XY_VERBOSE 0

longval& 
compute_p2xy() {
  longval Sqp=0;
  longval Sfp=0;
  longval tmp1;
  cerr << "CALCUL DE P2(x,y)\n\n";
  cerr.flush();
  int sieve_size1 = next_multiple(PK,2*y);
  int sieve_size2 = next_multiple(PK,y/3);
  Sieve<int64> main_sieve(sieve_size1,FINCRIBLE1);
  Sieve<int64> aux_sieve(sieve_size2, x2);
  aux_sieve.eratosthene();

  int64 p = aux_sieve.first_prime(); // p = P4=7
  while (p <= x2)
    {
      Sfp += f64(p);// f=Id
      p = aux_sieve.next_prime();
    }
#if P2XY_VERBOSE > 0      
  cerr << "Somme des f(p) jusqu'a sqrt(x) = " << Sfp << "\n";
#endif
  while (p > x2)
    p =  aux_sieve.previous_prime();
#if P2XY_VERBOSE > 0      
  cerr << "Dernier p avant sqrt(x) " << p << "\n";
#endif
  main_sieve.eratosthene();
#if P2XY_VERBOSE > 1 
  printf("Main sieve first window : \n");
  // main_sieve.display();
#endif
  int64 q = main_sieve.first_prime();
  while (p > y) {
    int64 xp = x/p;
#if P2XY_VERBOSE > 2
    cerr << "pm = " << p << "  -> x/p = " << xp << "\n";
    cerr << "Sfp = " << Sfp << "\n";
#endif
    while(q <= xp)
      {
#if P2XY_VERBOSE > 2
	cerr << "q = " << q << "\n";
#endif
	Sqp += f64(q); // f=Id
	q = main_sieve.next_prime();
      }
#if P2XY_VERBOSE > 1 
      cerr << "q  = " << q << "    Sqp = " << Sqp << "\n";
#endif
    Sfp -= f64(p);// f=Id
    tmp1 = Sqp-Sfp;
    tmp1 *= f64(p);// f=Id
    p2xy += tmp1;
    p = aux_sieve.previous_prime();
    etoile(main_sieve.A, FINCRIBLE1);
  }
  cerr << endl << "p2xy = " << p2xy << endl;
  chronometre();
  un_trait();
  return p2xy;
}
