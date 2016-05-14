#ifndef sieve_h 
#define sieve_h
#include<iostream>
#include"typedefs.h"
#include"presieve30.h"
#include"btable.h"
#include"primes.h"
#include"int64.h"
#include"iomanip"

using namespace std;

/*
 Une class pour cribler par tranches. On precrible par 2 et 3
 c'est a dire que ne sont representes dans la bit_table Btable
 que les entiers premiers avec 6. L'intervalle courant est l'intervalle
 [LMIN, LMAX] dont la longueur est un multiple de 6. 
 En general on initialisera la fenetre
 courante avec LMIN=1 et on progressera dans le crible de gauche a droite. 
 Il sera parfois utile de cribler de droite a gauche, d'ou la possibilite
*/

template<class MEDINT>
class Sieve: public Btable {
public:
  MEDINT A;
  MEDINT B;
  MEDINT END;

  Sieve() {fcounters=NULL;last_ftotal=0;};
  Sieve(int ws) {setup(ws,MAX64);}
  Sieve(int ws, MEDINT end) {setup(ws,end);}

  ~Sieve();

  void setup(int SIZE, MEDINT end);
  inline int done() {return (A > END);}

  void showindow() {
    cout << "Fenetre : [" << setw(6) << A << ", " << B << "]\n";
  }
  void sieve_by(int p);
  void eratosthene();
  MEDINT first_prime();
  MEDINT last_prime();
  MEDINT previous_prime();
  MEDINT next_prime();
  MEDINT current_prime() {return image(cursor);}

  void set_upon(MEDINT x);
  void set_cursor_on(MEDINT x);
  void set_at_left(MEDINT x);
  void forward();
  void backward() {A-=SIZE; B-= SIZE; fill();}
  // index u, defini pour u >= B est le rang dans la table de crible
  // du premier entier <= u qui est premier avec PK

  void display();
  void insert(MEDINT u) {set_bit(index(u));}
  void suppress(MEDINT u) {unset_bit(index(u));}
  //  int count(MEDINT u) {return Btable::count(index(u));}
  inline int index(MEDINT u) {return preKindex((int)(u-A));}
  inline MEDINT image(int indx) {return A+preKimage(indx);} 
  void set_fcounters();
  void init_fcounters();
  void count_f(longval& res, MEDINT u);

private:
  unsigned cursor;
  unsigned SIZE;
  unsigned max_bit_index; // l'offset dans la Btable du plus grand premier avec
  // PK appartenant a la fenetre courante [A,B]
  longval *fcounters;
  longval last_ftotal;
};

#include"sieve.cpp"
#endif

