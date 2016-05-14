#ifndef sievelgmp_h 
#define sievelgmp_h
#include<iostream>
#include"presieve30.h"
#include"btable.h"
#include"primes.h"
#include"int64.h"
#include"iomanip"

using namespace std;

/*
 Une class pour cribler par tranches. La borne superieure d'une tranche
 ne depassant pas INTMAX64 = 2^63-1 = 9223372036854775801 
 Ceci permet d'assurer que tous les nommbres premiers utilises
 pour les crible sont toujours representables sur 64 bits.

 Le cardinal B-A+1 de la fenetre de crible, ne depasse pas INTMAX 

 On precrible par 2 et 3 c'est a dire que ne sont representes dans la
 bit_table Btable que les entiers premiers avec 6. L'intervalle
 courant est l'intervalle [A, B] dont la longueur est un multiple de
 6.  En general on initialisera la fenetre courante avec A=1 et on
 progressera dans le crible de gauche a droite.  Il sera parfois utile
 de cribler de droite a gauche, d'ou la possibilite de revenir en
 arriere (methode .forward()).
*/


class Sievelgmp: public Btable {
public:
  LongGmp A;
  LongGmp B;

  Sievelgmp() {mpz_init(A.mp); mpz_init(B.mp);}
  Sievelgmp(int ws) {setup(ws);}
  void setup(int SIZE);


  void showindow() {
    cout << "Fenetre : [" << setw(20) << A << ", " << B << "]\n";
  }
  void sieve_by(int64 p);
  void sieve_by_long(int64 p);

  void eratosthene();
  LongGmp& first_prime();
  LongGmp& last_prime();
  LongGmp& previous_prime();
  LongGmp& max_prime_upto(LongGmp&);
  LongGmp& min_prime_greater(LongGmp&);
  LongGmp& next_prime();

  void set_upon(LongGmp x);
  void set_at_right(LongGmp x);
  void set_at_left(LongGmp x);
  void forward();
  void backward() {A-=SIZE; B-= SIZE; fill();}
  // index u, defini pour u >= B est le rang dans la table de crible
  // du premier entier <= u qui est premier avec PK

  void display();
  void insert(LongGmp u) {set_bit(index(u));}
  void suppress(LongGmp u) {unset_bit(index(u));}
  inline int index(LongGmp u) {return preKindex((int)(u-A));}
  LongGmp& image(int indx); 

private:
  int cursor;
  int SIZE;
  int max_bit_index; // l'offset dans la Btable du plus grand premier avec
  // PK appartenant a la fenetre courante [A,B]
  LongGmp resimage;
};

#endif

