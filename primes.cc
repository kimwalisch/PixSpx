#include<iomanip>
#include"presieve30.h"
#include"btable.h"
#include"vector.h"
#include"sieve.h"
#include"arith_tools.h"
#include"primes.h"
extern int _small_primes[];

int _nb_primes;
Vector<int> _primes;
Vector<int> _pi;
int tiny_pi[30] = {0,0,1,2,2,3,3,4,4,4};


void make_primes(int borne_sup, int with_counter) {

  cerr << "In make_primes with borne_sup = " << borne_sup
       << " et with_counter = " << with_counter << endl;

  int sieve_size = next_multiple(PK,borne_sup);

  Sieve<int> sieve_primes(sieve_size,0);
  for (int i=4; ; i++)
    {
      int p = _small_primes[i];
      if (p > borne_sup/p)
	break;
      sieve_primes.sieve_by(p);
      sieve_primes.insert(p);
    }
  
  _nb_primes = K;
  for (int i=1; i <= sieve_primes.index(borne_sup); i++) 
    if (sieve_primes.is_set_bit(i)) {
      _nb_primes++;
    }
  _primes.set_dim(_nb_primes+2);

  int j=0;
  for (int i=0; i <= K; i++)
    _primes[j++] = _small_primes[i];

  for (int i=1; i <= sieve_primes.index(borne_sup); i++) 
    if (sieve_primes.is_set_bit(i)) {
      _primes[j++] = sieve_primes.image(i);
      //cout << "newprimes " << sieve_primes.image(i) << endl;
  }
  _primes[j] = INT_MAX;

  if (with_counter == 1) 
    {
      _pi.set_dim(sieve_primes.bsize());
      _pi[0] = 0;    
      for (unsigned i = 1 ; i < sieve_primes.bsize() ; i++)
	{
	  _pi[i] = (sieve_primes.is_set_bit(i))? 
	    _pi[i-1] + 1 : _pi[i-1];
	}
    }
  cerr << "Number of primes = " << number_of_primes() << endl;
  cerr << "max_prime()      = " << max_prime() << endl;
}

