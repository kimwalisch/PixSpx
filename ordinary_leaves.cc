#include<iostream>
#include"typedefs.h"
#include"globals.h"
#define VERBOSE 1
using namespace std;
#define DEBUGORDINAIRES 0

extern longval ordinary_sum_pos;
extern longval ordinary_sum_neg;
extern longval ordinary_sum;
static longint xn;

longval& F(longint&);



longval& ordinary_leaves() {
  int * nindex;
  int n;
  ordinary_sum_pos = F(x);
  cerr << "F(x) = " << ordinary_sum_pos << endl;
  ordinary_sum_neg = 0;
  // Les squarefree appartenant à l'une des listes de squarefree
  // c'est a dire dont le plus petit facteur premier p satisfait p^2 <= z
  for (int k=K+1; k <= sqf_list_last_range; k++)
    { 
      nindex= &sqf_list_pos[k][0];
      n=*nindex++;
      while (n < INT_MAX) {
	xn=x/n;
	addmul_int(ordinary_sum_pos,F(xn),fint(n));
#if DEBUGORDINAIRES
	cerr << "n = " << n << " -> xn = " << xn << "   F(xn) = " <<  F(xn) << endl;
	cerr << "ordinary_sum_pos = " << ordinary_sum_pos << endl;
	cerr << "ordinary_sum_neg = " << ordinary_sum_neg << endl;
#endif
	n=*nindex++;
      }
      nindex= &sqf_list_neg[k][0];
      n=*nindex++;
      while (n < INT_MAX){
	xn=x/n;
	addmul_int(ordinary_sum_neg,F(xn),fint(n));
#if DEBUGORDINAIRES
	  cerr << "n = " << -n << " -> " << F(xn) << endl;
	  cerr << "ordinary_sum_pos = " << ordinary_sum_pos << endl;
	  cerr << "ordinary_sum_neg = " << ordinary_sum_neg << endl;
#endif
	n=*nindex++;
      }
    }

      // Les squarefree réduits a un unique facteur premier satisfaisant sqrt(z) <p<=y
  for (int k=max(sqf_list_last_range+1,K+1); k<= pi_y; k++)
	{
	  n=prime(k);
	  xn=x/n;
	  addmul_int(ordinary_sum_neg,F(xn),fint(n));
#if DEBUGORDINAIRES
	  cerr << "n = " << -n << " -> " << F(xn) << endl;
	  cerr << "ordinary_sum_pos = " << ordinary_sum_pos << endl;
	  cerr << "ordinary_sum_neg = " << ordinary_sum_neg << endl;
#endif
	}
      ordinary_sum  = ordinary_sum_pos;
      ordinary_sum -= ordinary_sum_neg;
#if VERBOSE > 0 
      cerr << "ordinary_sum_pos = " << ordinary_sum_pos << endl;
      cerr << "ordinary_sum_neg = " << ordinary_sum_neg << endl;
#endif
      cerr << "S0() = ordinary_sum = " << ordinary_sum << endl;
      //  chronometre();
  return ordinary_sum;
}


