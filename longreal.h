#ifndef longdouble_h
#define longdouble_h
#include<iostream>
//#include<string>
#include<gmp.h>
#include <mpfr.h>
#include <mpf2mpfr.h>
#include"longgmp.h"
#include"int64.h"
using namespace std;

class LongReal{
 public:
  mpf_t mp;

  LongReal() {mpf_init2(mp,96);}
  ~LongReal() {mpf_clear(mp);}
  LongReal(int u) {mpf_init_set_si(mp,u);}
  LongReal(char* str) {mpf_set_str(mp, str, 10);}

  inline LongReal& operator= (const LongReal& x); //operateur de recopie
  inline LongReal(const LongReal& x);//constructeur par recopie 

  inline void operator/=(int d) {
    mpf_div_ui(mp,mp,d);
  }

  inline void operator*=(int a) {
    mpf_mul_ui(mp,mp,a);
  }


  inline void operator=(char *str) {
    mpf_set_str(mp,str,10);
    mpf_out_str(stdout,10,40,mp);
    cout << "OUT EGAL STR" << endl;
  }

  inline void operator=(int u) {
    mpf_set_si(mp,u);
  }

  inline int operator==(LongReal& u) {
    return mpf_cmp(mp,u.mp) == 0;
  }

  inline int operator!=(LongReal& u) {
    return mpf_cmp(mp,u.mp) != 0;
  }

  inline int operator!=(int u) {
    return mpf_cmp_si(mp,u) != 0;
  }

  inline int operator>(LongReal& u) {
    return mpf_cmp(mp,u.mp) > 0;
  }

  inline int operator<(int u) {
    return (mpf_cmp_si(mp,u)<0);
  }

  const  char* str(int sz=40);
  //  operator int64() const;
  //  operator long() const;
  // operator int() const;

  void operator+= (LongReal u) {mpf_add(mp,mp,u.mp);}
  LongReal& operator=(const LongGmp& x);
  void operator-= (LongReal u) {mpf_sub(mp,mp,u.mp);}
  void operator*= (LongReal u) {mpf_mul(mp,mp,u.mp);}
  //  friend int min(LongReal& x, int u);
  /*
  inline friend int min(LongReal& x, int u) {
    if (mpf_cmp_si(x.mp, u) < 0) {
      return x;
    }
    return u;
  } 
  */

  void addmul_int(LongReal& res, LongReal& u, int a);
  void submul_int(LongReal& res, LongReal& u, int a);

  friend void submul_int(LongReal& res, LongReal& u, LongReal& a);
  friend void addmul_int(LongReal& res, LongReal& u, LongReal& a);

  // ATTENTION LES OPERATEURS QUI RETOURNENT L'ADRESS UNE VALEUR
  // DE TYPE LONGINT, RENVOIENT LEUR RESULTAT DANS tmp1
  // ET C'EST tmp1 QUI EST RENVOYE PAR ADRESSE
  // CELA PERMET, QUEL QUE SOIT LE TYPE DE LA VARIABLE u
  // POURVU QU'IL EXISTE UNE CONVERSION EXPLICITE DU
  // TYPE LONGINT VERS LE TYPE de u d'ecrire
  // u = f(x) chaque fois que f est un operateur
  // ou une fonction qui renvoie une valeur de type LongReal
  // par adresse

  // ON N'UTILSE DONC PAS DE FONCTION ou D'OPERATEUR pour
  // construire des valeurs de type LongReal
  
  friend const LongReal& operator-(LongReal&, LongReal&);
  friend const LongReal& operator/(LongReal&, int64);
  friend const LongReal& operator/(LongReal& x, int y);
  friend const LongReal& operator/(LongReal& x, long y);
  friend const LongReal& pow_3_8(LongReal& x);
  friend ostream& operator<<(ostream &os,const LongReal x);

  friend LongReal& F(LongReal& u);



};

void atolong(LongReal& x, char* str);

//////////////////////////////////////////////////////////////////////



inline LongReal& LongReal::operator=(const LongReal& x) {
  mpf_set(mp,x.mp);
  return *this;
}

inline LongReal& LongReal::operator=(const LongGmp& x) {
  mpf_set_z(mp,x.mp);
  return *this;
}


inline  void log(LongReal& res, LongReal& u) {
  mpfr_log(res.mp,u.mp,GMP_RNDN);
}


inline LongReal::LongReal(const LongReal& x){
  mpf_init_set(mp,x.mp);
}

inline void inverse(LongReal& x, LongReal u) {
  mpf_ui_div(x.mp,1,u.mp);
}

void init_gamma30();
#endif
