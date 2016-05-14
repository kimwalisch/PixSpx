#ifndef _sieveext_h
#define _sieveext_h

template<typename INT> class Sieve_ext:
  public sieve<INT>
{
public:
  void eratosthene();
private:
  Sieve<int64> auxprimes;
};

template<class INT>
void
Sieve_ext<INT>::eratosthene() {
  int p;
  int ip = K+1; // Le rang du premier premier non precrible 
  int64 sqrt_B = root(B); // QUEL SQRT
  if (sqrt_B > max_prime()) {
    cerr << "Dans eratoshene : pas assez de nombres premiers\n";
    cerr << "SQRT_B = " << sqrt_B << " maxp = " << max_prime() << "\n";
    cerr << "Crible aux. pour enumerer les premiers manquants " << endl;
    cerr <<" SIZE = " << SIZE << endl;
    auxprimes.setup(SIZE,MAX64);
    auxprimes.set_at_left(max_prime());
    auxprimes.eratosthene();
    cerr << "auxprime eratosthene is done" << endl;
    auxprimes.set_cursor_on(max_prime());
    cerr << "auxprime cursor is on maxprime() = " 
	 << auxprimes.current_prime() << endl;
    int64 p = auxprimes.next_prime();
    cerr << "Premier nombre premier complementaire  " << p << endl;
  }

  if (A <= 1)
    unset_bit(0);
  p = prime(ip++);
  cerr << "Crible 1 jusqu'a p= " <<  min(sqrt_B,max_prime()) << endl;
  while (p  <= min(sqrt_B,max_prime()))
    {
      sieve_by(p);
      if (A <= p){ // Il est de toute facon <= LMAX
	set_bit(index(p));
      }
      p = prime(ip++);
    } 
  int cnt = 0;
  if (sqrt_B > max_prime()) {
    cerr << "Crible complementaire " << endl;
    int64 p = auxprimes.current_prime();
    while (p <= sqrt_B) {
      cnt++;
      if (p > SIZE)
	sieve_by_long(p);
      else sieve_by(p);
      p =  auxprimes.next_prime();
    }
    cerr << "Fin du crible complementaire" << endl;
  }
  cursor  = 0;
#if SIEVE_LNG_VERBOSE > 0
  cerr << "Nombre de premiers complementaires = " << cnt << endl;
#endif
}


#endif
