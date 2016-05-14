#include<iomanip>
#ifndef sieve_dynamic
#define sieve_dynamic
#include"globals.h"
#include"sieve.h"
#define DYNAMIC_VERBOSE 1

using namespace std;
/*
1) Dans un crible ordinaire la fonction de crible compte
le nombre des entiers <= x non supprimes par le crible.

Ici on introduit un parametre supplementaire f qui est
une fonction N -> C. La fonction de crible rend la somme 
des valeurs f(n) pour les entiers n <= x non rayes par 
le crible.

2) On fera le crible, nombre premier par nombre premier, 
en s'interessant aux fonctions de crible partielles 
comptant les f(n) pour n <= x non raye apres le crible
par les premiers prime(1), prime(2),...,prime(k).

Il deviendrait trop couteux de mettre a jour les
compteurs apres chaque crible partiel, car cette
operation coute autant que la longueur de la fenetre
de crible.

On se debrouille pour mettre a jour apres chaque suppression
d'un entier la table de compte en un temps logarithmique
en sa taille.

L'idee est representee par ce dessin
ici BASE = 16
et la ligne superieure local_sum[16] = 4, local_sum[17] = 5 
contient les valeurs associees au entier L+1, L+5, L+7,.......

4   5   1  7   4  6  8  3  3  5  0  0  0  0  0  0
9   8  10  11  8  0  0  0
17 21   8  0
38 8
46

La ligne du haut est la fenetre de crible (completee
d'autant de 0 qu'il faut pour que sa longueur soit
une puissance de 2

Si on numerote les cases de gauche a droite,
et de bas en haut, la numerotation partant de 1,
la case numero 1 contient 46, la case numero 2
contient 38, la numero 3 contient 8 etc...

Le contenu de la case de rank k est la somme des contenus
des cases de rang 2k et 2k+1

Previous_total[indp] est la somme des f(n) pour les n non
subsistant apres le crible par prime(indp) dans les intervalles
précédents la fenetre courante.

Attention currentp est le nombre premiers par lequel
on VA cribler.
*/

template <class LONGVAL, class MEDVAL>
class Sieve_dynamic
{
public :
  Sieve_dynamic() {};
  void setup(int size, int64 END, int max_prime);

  void sieve_by(int p);
  inline int done() {return (A > END);}
  int window_sieved() {return (currentp > max_prime);}

  void showindow();
  void display();
  void forward();

  void fill();
  void count(LONGVAL& accu,int64 u); // La fonction de crible
  int curp; // Le nombre premier courant par le quel on va cribler  
  void sieve_by_currentp(); // crible par curp et incrementattion de curp
  int64 A; // Element minimum de la fenetre courante
  int64 B; // Element minimum de la fenetre courante
  int64 END;
  
  void remember();
  int is_set(int64 u);
  int is_set_bit(int offset) {return local_sum[BASE+offset]!=0;}
  inline int index(int64 u) {return preKindex(u-A);}
  inline int64 image(int indx) {return A+preKimage(indx);} 
  int currentp;
  int curp_index;
private:
  int SIZE;
  int BASE;
  int BSIZE; //Nombre d'entiers premier avec PK dans la fenetre courante
  int max_prime;
  int nb_primes;
  MEDVAL* local_sum;
  LONGVAL* previous_total;
  MEDVAL local_count(int offset);
  void unset_bit(int i);
  void set_bit(int i);

  longint tmp1;
};

#include "sieve_dyn_methodes.h"

#endif
