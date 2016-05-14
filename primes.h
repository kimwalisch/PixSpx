#ifndef primes_h 
#define primes_h
#include"vector.h"
#include"btable.h"
#include"presieve30.h"

extern int _nb_primes;
extern Vector<int> _primes;
extern Vector<int> _pi;

void make_primes(int borne_sup, int with_counter=1);

inline int prime(int i)        {return _primes[i];}
inline int max_prime()         {return _primes[_nb_primes];}
inline int number_of_primes()  {return _nb_primes;}
inline int pi(int u);
inline int index_of_first_prime_bigger_than(int x);



/* Definitions en lignes */

inline int index_of_first_prime_bigger_than(int x)
{
  return _primes.index_of_first_bigger_than(x);
}

inline int pi(int u)
{
  if (u < PRK1)
    return tout_petit_pi[u];
  else return K +  _pi[preKindex(u-1)];
}

extern int tiny_pi[];
#endif
