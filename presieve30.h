#ifndef presieve_h
#define presieve_h
#include"int64.h"
#define WITH_COUNTERS 1

/**************************************************************************

			INVERSION MODULO PK

***************************************************************************/
#define K   3  // Precrible par p1 = 2 , p2 = 3, et p3 = 5
#define PK 30
#define FK  8
#define PRK1 7
#define SK 120 // La sommes des classes inversibles

const int tout_petit_pi[PRK1] = {0,0,1,2,2,3,3};

static int ua[PK] = {0, 29, 0, 0, 0, 0, 0, 17, 0, 0,\
		     0, 19, 0, 23, 0, 0, 0, 7, 0, 11,\
		     0, 0,  0, 13, 0, 0, 0, 0, 0, 1 };

static int ub[PK] = {0, 1, 0, 0,  0, 0, 0, 4, 0, 0,\
		     0, 7, 0, 10, 0, 0, 0, 4, 0, 7,\
		     0, 0, 0, 10, 0, 0, 0, 0, 0, 1 };

// PRED[u] est le rang du plus grand entier inferieur à u
// qui est premier avec PK

static int PRED[PK] =  {0, 0, 0, 0, 0, 0, 1, 1, 1, 1,\
			2, 2, 3, 3, 3, 3, 4, 4, 5, 5,\
			5, 5, 6, 6, 6, 6, 6, 6, 7, 7};


static int CLASS[FK] = {1,7,11,13,17,19,23,29};


// L'inverse de 30 modulo x, lorsque $x$ est un entier premier
// avec 30

inline int inversePK(int x)
{
  register int r = x % PK;
  return (x/PK)*ua[r] + ub[r];
}

inline int64 inversePK64(int64 x) 
{
  register int r = x % PK;
  return (x/PK)*ua[r] + ub[r];
}

inline long preKindex(long u) {return  FK*(u/PK) + PRED[u % PK];};

inline int preKimage(int indx) {
    int q = indx/FK;
    int r = indx%FK;
    return  q*PK+CLASS[r]-1;
}
#endif

