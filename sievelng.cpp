#include"sieve.h"
#define SIEVE_LNG_VERBOSE 0

void remdivlong64(int64&,longint&,int64); 

Sieve<int64> auxprimes;

template<class longint>
longint& 
Sievelng<longint>::image(int indx) {
  resimage = A;
  resimage+=preKimage(indx);
  return resimage;
} 

template<class longint>
void Sievelng<longint>::setup(int64 size)
{
  //  mpz_init(A.mp); 
  //  mpz_init(B.mp);
  //  A(0);
  //  B(0);
  A = 1;
  B = size;
  SIZE=size;
  if (size % PK) {
    cerr << "Erreur: creation d'un Sievelng size = " << size
	 << " doit etre un multiple de " << PK << endl;
    exit(0);
  }
  int bit_size = (SIZE/PK)*FK;
  Btable::setup(bit_size);
  max_bit_index = index(B);
  fill();
}

template<class longint>
void
Sievelng<longint>::display(void)  {
  cerr << "Fenetre [" << A << "," << B << "]" << endl;
  for (int i = 0; i <= max_bit_index; i++)
    if (is_set_bit(i))
      cerr << setw(16) << image(i); 
    else cerr << setw(16) << " _ ";
  cerr << endl;
}

template<class longint>
void
Sievelng<longint>::set_upon(longint x) {
  B = x;
  B-=1;
  B/=SIZE;
  B+=1;
  B*=SIZE;
  A = B;
  A -= (SIZE-1);
}

static longint tmp1;


template<class longint>
void
Sievelng<longint>::sieve_by(int64 p) {
  //  void remdivlong64(int64&, longint&, int64);
  int64 q = inversePK64(p);// De l'ordre de grandeur de p
  int64 increment = FK*p;
  int64 debut = 0;

  tmp1 = A;
  tmp1-= 1;
  remdivlong64(debut,tmp1,p); 
  //debut =(A-1)%p de l'ordre de grandeur de p
  for (int k=0; k < FK; k++) {
    int64 i0 = q*(debut+CLASS[k]) % p; 
    if (i0) 
      i0 = p-i0;
    int64 ibase = k + FK*i0;
    for (int64  i = ibase ; i <= max_bit_index ; i += increment) 
      unset_bit((int)i);
  }
}

static longint qs;

template<class longint>
void
Sievelng<longint>::sieve_by_long(int64 p) {
  //cout << "sieve_by_long p = " << p << endl;
  qs = B;
  qs /= p;
  int r = (qs % 30);
  if ((r % 2 == 0) || (r % 3 == 0) || (r % 5) == 0)
    return;
  qs*=p;  // qs est le plus grand multiple de p ne depassant pas B  
  if(A < qs) {
    unset_bit(index(qs));
  }
}


template<class longint>
void
Sievelng<longint>::eratosthene() {
  int p;
  int ip = K+1; // Le rang du premier premier non precrible 
  int64 sqrt_B = root(B); // QUEL SQRT
  cerr << "size of sqrt_B = " << sizeof(sqrt_B) << endl;
  if (sqrt_B > max_prime()) {
    cerr << "Dans eratoshene,,, : pas assez de nombres premiers\n";
    cerr << "SQRT_B = " << sqrt_B << " maxp = " << max_prime() << "\n";
    cerr << "Crible aux. pour enumerer les premiers manquants " << endl;
    //    auxprimes.setup(100000020,MAX64);
    cerr <<" SIZE == " << SIZE << endl;
    int szx;
    if (SIZE > INT_MAX)
      szx = 2000000010;
    else szx = SIZE;
    cout << "szx = " << szx << endl;
    auxprimes.setup(szx,MAX64);
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
  cerr << "premier p = " << p << endl;
  while (p  <= min(sqrt_B,max_prime()))
    {
      //cerr << "sieve by " << p << endl;
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

template<class longint>
longint&
Sievelng<longint>::previous_prime()
{
  for (;;) {
    if (cursor < 0) {
      if (A <= 1) {
	resimage = 1;
	return resimage;
      }
      else
	{
	  backward();
	  eratosthene();
	  cursor = Btable::bsize()-1;
	}
    }
    else cursor--;

    while (cursor >= 0)
      {
	if (is_set_bit(cursor))
	  {
	    return image(cursor);
	  }
	cursor--;
      }
  } 
}

template<class longint>
longint& 
Sievelng<longint>::next_prime()
{
  for (;;) {
    //    cerr << "Cursor = max_bit_index" << endl;
    if (cursor >= max_bit_index) {
      forward();
      eratosthene();
      cursor = 0;
    }
    else cursor++;

    while (cursor <= max_bit_index)
      {
	if (is_set_bit(cursor))
	  {
	    //    cerr << "Ok cursor = " << cursor << "  image(cursor) = "
	    //	 << image(cursor) << endl;
	    return image(cursor);
	  }
	else cursor++;
      }
  } 
}

template<class longint>
longint& 
Sievelng<longint>::first_prime()
{
  eratosthene();
  cursor = -1;
  return next_prime();
}

template<class longint>
longint&
Sievelng<longint>::last_prime()
{
  eratosthene();
  cursor = 1+index(B);
  return previous_prime();
}

template<class longint>
void
Sievelng<longint>::forward() {
  A +=SIZE; 
  B += SIZE; 
  fill();
}

template<class longint>
void
Sievelng<longint>::set_at_right(longint x) {
  B = x;
  int r = x%PK;
  if (r)
    B += PK-r;
  A = B;
  A -= (SIZE-1);
}

template<class longint>
void
Sievelng<longint>::set_at_left(longint x) {
  int r = x%PK;
  A = x;
  if (r==0)
    {
      A-=(PK-1);
    }
  else
    {
      A-= (r-1);
    }
  B = A;
  B += (SIZE-1);
}
