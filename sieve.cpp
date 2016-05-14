#include<iostream>
#include<iomanip>
using namespace std;
#include"sieve.h"
#include"f.h"
#define SIEVE_VERBOSE 1

template<class MEDINT>
void 
Sieve<MEDINT>::setup(int size, MEDINT end)
{
  if (size % PK) {
    cout << "Erreur: creation d'un Sieve size = " << size\
	 << " doit etre un multiple de " << PK << endl;
    exit(0);
  }
  A=1; 
  B=size;
  END = end;
  SIZE=size;
  fcounters=NULL;
  int bit_size = (SIZE/PK)*FK;
  last_ftotal = 0;
  Btable::setup(bit_size);
  max_bit_index = index(B);
  fill();
}

template<class MEDINT>
void
Sieve<MEDINT>::display(void)  {
  cout << "Fenetre [" << A << "," << B << "]" << endl;
  for (int i = 0; i <= max_bit_index; i++)
    if (is_set_bit(i))
      cout << setw(16) << image(i); 
    else cout << setw(16) << " _ ";
  cout << endl;

  if (fcounters != NULL) {
    cout <<  "last_ftotal " << last_ftotal << endl;
    cout << "Les compteurs \n";
    for (int i=0; i <= max_bit_index; i++)
      cout << setw(8) << fcounters[i];
    cout << endl;
  } 
}

template<class MEDINT>
void
Sieve<MEDINT>::set_upon(MEDINT x) {
  B = MEDINT(SIZE)*((x-1)/SIZE+1);
  A = B-SIZE+1;
}



template<class MEDINT>
void
Sieve<MEDINT>::sieve_by(int p) {
  MEDINT q = inversePK(p);// De l'ordre de grandeur de p
  int increment = FK*p;
  int debut=(A-1) % p;  // De l'ordre de grandeur de p
  for (int k=0; k < FK; k++) {
    int i0 = q*(debut+CLASS[k]) % p; // La multiplication se fait
    // sur 64 bits parce que debut est un intt64.
    // Avec une multiplication sur 32bits il y a debordement
    // pour p^2 > 2*10^9, c'est a dire pour B > 2*10^9
    // puisque la plus grande valeur de p est B^(1/2)
    if (i0) 
      i0 = p-i0;
    int ibase = k + FK*i0;
    for (unsigned  i = ibase ; i <= max_bit_index ; i += increment) 
	unset_bit(i);
  }
}

template<class MEDINT>
void
Sieve<MEDINT>::eratosthene() {
  int p;
  int ip = K+1; // Le rang du premier premier non precrible 
  int sqrt_B = sqrt(B); // QUEL SQRT

  if (sqrt_B > max_prime()) {
    cout << "Erreur dans eratoshene : pas assez de nombres premiers\n";
    cout << "SQRT_B = " << sqrt_B << " maxp = " << max_prime() << "\n";
    exit(0);
  }
  if (sqrt_B > 357000000){
    cout << "Erreur dans eratoshene : B trop grand\n";
    exit(0);
  }
  if (A == 1)
    unset_bit(0);
  p = prime(ip++);
  while (p  <= sqrt_B)
    {
      sieve_by(p);
      // cout << "sieve by " << p << endl;
      if (p >= A){ // Il est de toute facon <= LMAX
	set_bit(index(p));
      }
      p = prime(ip++);
    } 
  cursor  = 0;
  if (fcounters != NULL)
    {
      init_fcounters();
    }
#if SIEVE_VERBOSE > 1
  cout << "Apres eratosthene : \n";
  display();
#endif
}

template<class MEDINT>
void
Sieve<MEDINT>::set_fcounters()
{
  //  cout << "In set_fcounters bsize() = " << bsize() << "\n";
  fcounters = new longval[bsize()];
  if (fcounters == NULL)
    {
      cout << "Not enough memory to make fcounters" << endl;
      exit(0);
    }
}

template<class MEDINT>
void
Sieve<MEDINT>::init_fcounters()
{
  //  cout << "in init_fcounters\n";
  fcounters[0] = last_ftotal;
  if (is_set_bit(0))
    fcounters[0] += f64(image(0));
  for (unsigned i=1; i < bsize(); i++) {
    fcounters[i] = fcounters[i-1];
    if (is_set_bit(i))
      fcounters[i] += f64(image(i));
  }
}

template<class MEDINT>
void
Sieve<MEDINT>::count_f(longval& res, MEDINT u)
{
  //cout << "In Sieve<MEDINT>::count_f u = " << u << " index(u) = " <<index(u) <<endl; 
  //  res = last_ftotal;
  res = fcounters[index(u)];
}

template<class MEDINT>
MEDINT
Sieve<MEDINT>::previous_prime()
{
  for (;;) {
    if (cursor == UINT_MAX) {
      if (A == 1) return 1;
      else
	{
	  backward();
	  eratosthene();
	  cursor = Btable::bsize()-1;
	}
    }
    else cursor--;
    while (cursor < UINT_MAX)
      {
	if (is_set_bit(cursor))
	  {
	    return image(cursor);
	  }
	cursor--;
      }
  } 
}

template<class MEDINT>
MEDINT 
Sieve<MEDINT>::next_prime()
{
  for (;;) {
    if (cursor == bsize()) {
      forward();
      eratosthene();
      cursor = 0;
    }
    else cursor++;

    while (cursor < bsize())
      {
	if (is_set_bit(cursor))
	  {
	    return image(cursor);
	  }
	else cursor++;
      }
  } 
}


template<class MEDINT>
MEDINT 
Sieve<MEDINT>::first_prime()
{
  eratosthene();
  cursor = 0;
  return next_prime();
}

template<class MEDINT>
MEDINT 
Sieve<MEDINT>::last_prime()
{
  eratosthene();
  cursor = index(B);
  return previous_prime();
}



template<class MEDINT>
void
Sieve<MEDINT>::forward() {
  if ((fcounters != NULL) && (B < END))
    last_ftotal =  fcounters[index(B)];
  A +=SIZE; 
  B += SIZE; 
  fill();
}

template<class MEDINT>
void
Sieve<MEDINT>::set_cursor_on(MEDINT x) {
  cursor = index(x);
}

template<class MEDINT>
void
Sieve<MEDINT>::set_at_left(MEDINT x) {
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

template<class MEDINT>
Sieve<MEDINT>::~Sieve() {
  if (fcounters != NULL)
    delete [] fcounters;
}

