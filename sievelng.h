#ifndef sievelng_h 
#define sievelng_h
#include<iostream>
#include<iomanip>
#include"presieve30.h"
#include"btable.h"
#include"primes.h"
#include"int64.h"
#include"longgmp.h"

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

template<class longint>
class Sievelng: public Btable {
public:
  longint A;
  longint B;

  Sievelng() : A() , B() {}
  Sievelng(int64 ws) {setup(ws);}
  void setup(int64 SIZE);

  void showindow() {
    cout << "Fenetre : [" << setw(20) << A << ", " << B << "]\n";
  }
  void sieve_by(int64 p);
  void sieve_by_long(int64 p);

  void eratosthene();
  longint& first_prime();
  longint& last_prime();
  longint& previous_prime();
  longint& max_prime_upto(longint&);
  longint& min_prime_greater(longint&);
  longint& next_prime();

  void set_upon(longint x);
  void set_at_right(longint x);
  void set_at_left(longint x);
  void forward();
  void backward() {A-=SIZE; B-= SIZE; fill();}
  // index u, defini pour u >= B est le rang dans la table de crible
  // du premier entier <= u qui est premier avec PK

  void display();
  void insert(longint u) {set_bit(index(u));}
  void suppress(longint u) {unset_bit(index(u));}
  inline int index(longint u) {return preKindex((int64)(u-A));}
  longint& image(int indx); 

private:
  int cursor;
  int64 SIZE;
  int max_bit_index; // l'offset dans la Btable du plus grand premier avec
  // PK appartenant a la fenetre courante [A,B]
  longint resimage;
};

#include"sievelng.cpp"
#endif

