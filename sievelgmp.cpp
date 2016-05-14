#include<iostream>
#include<iomanip>
#include"sieve.h"
#include"sievelgmp.h"
#define SIEVE_LNG_VERBOSE 1


Sieve<int64> auxprimes;

LongGmp& Sievelgmp::image(int indx) {
  resimage = A;
  resimage+=preKimage(indx);
  return resimage;
} 

void Sievelgmp::setup(int size)
{
  mpz_init(A.mp); 
  mpz_init(B.mp);
  if (size % PK) {
    cout << "Erreur: creation d'un Sievelgmp size = " << size
	 << " doit etre un multiple de " << PK << endl;
    exit(0);
  }
  A=1; 
  B=size;
  SIZE=size;
  int bit_size = (SIZE/PK)*FK;
  Btable::setup(bit_size);
  max_bit_index = index(B);
  fill();
}


void
Sievelgmp::display(void)  {
  cout << "Fenetre [" << A << "," << B << "]" << endl;
  for (int i = 0; i <= max_bit_index; i++)
    if (is_set_bit(i))
      cout << setw(16) << image(i); 
    else cout << setw(16) << " _ ";
  cout << endl;
}


void
Sievelgmp::set_upon(LongGmp x) {
  B = x;
  B-=1;
  B/=SIZE;
  B+=1;
  B*=SIZE;
  A = B;
  A -= (SIZE-1);
}

static LongGmp tmp1;

void
Sievelgmp::sieve_by(int64 p) {
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

static LongGmp qs;

void
Sievelgmp::sieve_by_long(int64 p) {
  //  cout << "sieve_by_long p = " << p << endl;
  qs = B;
  qs /= p;
  int r = (qs % 30);
  if ((r % 2 == 0) || (r % 3 == 0) || (r % 5) == 0)
    return;
  qs*=p;  // qs est le plus grand multiple de p ne depassant pas B  
  if(A < qs) {
    // cout << "On supprime " << qs << endl;
    unset_bit(index(qs));
  }
  else {
    //cout << "Pas de multiple de p dans l'intervalle courant" << endl;
    //    cout << "p = " << p << endl;
  }
}


void
Sievelgmp::eratosthene() {
  cout << "In eratosthene A = " << A << "   B = " << B << endl;
  int p;
  int ip = K+1; // Le rang du premier premier non precrible 
  int64 sqrt_B = root(B); // QUEL SQRT
  cout << "sqrt_B = " << sqrt_B << endl;
  
  if (sqrt_B > max_prime()) {
    cout << "Dans eratoshene : pas assez de nombres premiers\n";
    //    cout << "SQRT_B = " << sqrt_B << " maxp = " << max_prime() << "\n";
    cout << "Crible aux. pour enumerer les premiers manquants " << endl;
    auxprimes.setup(100000020,MAX64);
    auxprimes.eratosthene();
    auxprimes.set_cursor_on(max_prime());
    int64 p = auxprimes.next_prime();
    cout << "auxprime current prime " << p << endl;
  }

  if (A <= 1)
    unset_bit(0);
  p = prime(ip++);
  cout << "Crible 1 jusqu'a p= " <<  min(sqrt_B,max_prime()) << endl;
  while (p  <= min(sqrt_B,max_prime()))
    {
      sieve_by(p);
      //cout << "sieve by " << p << endl;
      if (A <= p){ // Il est de toute facon <= LMAX
	set_bit(index(p));
      }
      p = prime(ip++);
    } 
  int cnt = 0;
  if (sqrt_B > max_prime()) {
      cout << "Crible complementaire " << endl;
      int64 p = auxprimes.current_prime();
      while (p <= sqrt_B) {
	cnt++;
	//	cout << "Crible par p p = " << p << endl;
	if (p > SIZE)
	  sieve_by_long(p);
	else sieve_by(p);
	p =  auxprimes.next_prime();
      }
      cout << "Fin du crible complementaire" << endl;
      // cout << "p = " << p << endl;
    }
  cursor  = 0;
#if SIEVE_LNG_VERBOSE > 0
  cout << "Apres eratosthene : \n";
  cout << "Nombre de premiers complementaires = " << cnt << endl;

#endif
}


LongGmp&
Sievelgmp::previous_prime()
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


LongGmp& 
Sievelgmp::next_prime()
{
  for (;;) {
    //    cout << "Cursor = max_bit_index" << endl;
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
	    //    cout << "Ok cursor = " << cursor << "  image(cursor) = "
	    //	 << image(cursor) << endl;
	    return image(cursor);
	  }
	else cursor++;
      }
  } 
}


LongGmp& 
Sievelgmp::first_prime()
{
  eratosthene();
  cursor = -1;
  return next_prime();
}


LongGmp&
Sievelgmp::last_prime()
{
  eratosthene();
  cursor = 1+index(B);
  return previous_prime();
}




void
Sievelgmp::forward() {
  A +=SIZE; 
  B += SIZE; 
  fill();
}

void
Sievelgmp::set_at_right(LongGmp x) {
  B = x;
  int r = x%PK;
  if (r)
    B += PK-r;
  A = B;
  A -= (SIZE-1);
}


void
Sievelgmp::set_at_left(LongGmp x) {
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
