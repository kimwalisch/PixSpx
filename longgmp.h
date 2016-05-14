#ifndef longgmp_h
#define longgmp_h
#include<iostream>
#include<gmp.h>
#include"int64.h"


using namespace std;

class LongGmp{
 public:
  LongGmp() {mpz_init2(mp,64);}
  ~LongGmp() {mpz_clear(mp);}
  LongGmp(int u) {mpz_init_set_si(mp,u);}

  inline LongGmp& operator= (const LongGmp& x); //operateur de recopie
  inline LongGmp(const LongGmp& x);//constructeur par recopie 

  inline void operator=(char *str);

  inline void operator=(int u) {mpz_import(mp,1,-1,4,0,0,(&u));}
  //  inline void operator=(long u) {mpz_import(mp,1,-1,4,0,0,(&u));}
  inline void operator=(long u) {mpz_set_si(mp,u);}
  inline void operator=(double u){mpz_set_d(mp,u);}

#if __WORDSIZE == 32
  LongGmp(int64 u)  {
    mpz_init2(mp,64);
    mpz_import(mp,1,-1,8,0,0,(&u));
}
  inline void operator=(int64 u) {mpz_import(mp,1,-1,8,0,0,(&u));}
#endif

  void init(char* str) {
    mpz_set_str(mp,str,10);
  }

  inline int operator<=(long u) {
    return (mpz_cmp_si(mp,u)<=0);
  }

  inline int operator<=(int u) {
    return (mpz_cmp_si(mp,u)<=0);
  }

  inline int operator<(long u) {
    return (mpz_cmp_si(mp,u)<0);
  }

  inline int operator<(int u) {
    return (mpz_cmp_si(mp,u)<0);
  }

  inline int operator<=(LongGmp& u) {
    return mpz_cmp(mp,u.mp) <= 0;
  }

  inline int operator<(LongGmp& u) {
    return (mpz_cmp(mp,u.mp) <0);
  }

  inline int operator>=(long u) {
    return (mpz_cmp_si(mp,u)>=0);
  }

  inline int operator>(long u) {
    return (mpz_cmp_si(mp,u)>0);
  }

  inline int operator>(int u) {
    return (mpz_cmp_si(mp,u)>0);
  }

  inline int operator>=(int u) {
    return (mpz_cmp_si(mp,u)>=0);
  }

  inline int operator>=(LongGmp& u) {
    return mpz_cmp(mp,u.mp) >= 0;
  }

#if __WORDSIZE == 32
mpz_t tmp0;

  inline int operator>(int64 u) {
    mpz_import(tmp0,1,-1,8,0,0,&u);
    return (mpz_cmp(mp,tmp0)>0);
  }

  inline int operator>=(int64 u) {
    mpz_import(tmp0,1,-1,8,0,0,&u);
    return (mpz_cmp(mp,tmp0)>=0);
  }

  inline int operator<=(int64 u) {
    mpz_import(tmp0,1,-1,8,0,0,&u);
    return (mpz_cmp(mp,tmp0)<=0);
  }

  inline int operator<(int64 u) {
    mpz_import(tmp0,1,-1,8,0,0,&u);
    return (mpz_cmp(mp,tmp0)<0);
  }

  void operator/= (int64 y);
  friend const LongGmp& operator/(LongGmp&, int64);

  void operator+= (int64 u);
  void operator*= (int64 u);
  void operator-= (int64 u);

  friend void remdivlong64(int64&, LongGmp&, int64);
  friend int64 root(LongGmp& x);
  operator int64()  const;
#endif



  const char* str();
  operator long() const;
  operator int() const;
  operator double() const;

  void operator+= (LongGmp u) {mpz_add(mp,mp,u.mp);}
  void operator-= (LongGmp u) {mpz_sub(mp,mp,u.mp);}
  void operator*= (LongGmp u) {mpz_mul(mp,mp,u.mp);}
  void operator+= (long y) {mpz_add_ui(mp,mp,y);}
  void operator-= (long y) {mpz_sub_ui(mp,mp,y);}
  void operator*= (long y) {mpz_mul_si(mp,mp,y);}
  void operator/= (long y) {mpz_tdiv_q_ui(mp,mp,y);}
  void operator+= (int y) {mpz_add_ui(mp,mp,y);}
  void operator-= (int y) {mpz_sub_ui(mp,mp,y);}
  void operator*= (int y) {mpz_mul_si(mp,mp,y);}
  void operator/= (int y) {mpz_tdiv_q_ui(mp,mp,y);}

  int  operator%(int d);
  
  inline friend int min(LongGmp& x, int u) {
    if (mpz_cmp_si(x.mp, u) < 0) {
      return x;
    }
    return u;
  } 

  friend void submul_int(LongGmp& res, LongGmp& u, int a);
  friend void addmul_int(LongGmp& res, LongGmp& u, int a);

  // ATTENTION LES OPERATEURS QUI RETOURNENT L'ADRESS UNE VALEUR
  // DE TYPE LONGINT, RENVOIENT LEUR RESULTAT DANS tmp1
  // ET C'EST tmp1 QUI EST RENVOYE PAR ADRESSE
  // CELA PERMET, QUEL QUE SOIT LE TYPE DE LA VARIABLE u
  // POURVU QU'IL EXISTE UNE CONVERSION EXPLICITE DU
  // TYPE LONGINT VERS LE TYPE de u d'ecrire
  // u = f(x) chaque fois que f est un operateur
  // ou une fonction qui renvoie une valeur de type LongGmp
  // par adresse

  // ON N'UTILSE DONC PAS DE FONCTION ou D'OPERATEUR pour
  // construire des valeurs de type LongGmp
  
  friend const LongGmp& operator-(LongGmp&, LongGmp&);
  friend const LongGmp& operator/(LongGmp& x, int y);
  friend const LongGmp& operator/(LongGmp& x, long y);
  friend const LongGmp& pow_3_8(LongGmp& x);
  friend ostream& operator <<(ostream &os,const LongGmp x);

  friend int pow25(LongGmp& x);

  long root(LongGmp& x);

  friend void div(LongGmp&, long, LongGmp&, long&);
#if __WORDSIZE == 64
  friend void remdivlong64(long&, LongGmp&, long);
#endif
  friend LongGmp& root_n(LongGmp& x, int n);
  mpz_t mp;
};

void atolong(LongGmp& x, char* str);

//////////////////////////////////////////////////////////////////////


inline  LongGmp::operator long()  const {
  return mpz_get_si(mp);
}


inline  LongGmp::operator int()  const {
  return mpz_get_si(mp);
}

#if __WORDSIZE == 32
inline LongGmp::operator int64()  const {
    int64 res;
    mpz_export(&res,NULL,-1,8,0,0,mp);
    return res;
}
#endif


inline  LongGmp::operator double()  const {
  return mpz_get_d(mp);
}


inline void LongGmp::operator=(char *str) {
  mpz_set_str(mp,str,10);
}

inline LongGmp& LongGmp::operator=(const LongGmp& x) {
  mpz_set(mp,x.mp);
  return *this;
}

inline LongGmp::LongGmp(const LongGmp& x){
  mpz_init_set(mp,x.mp);
}

inline int LongGmp::operator%(int d) {
  return mpz_tdiv_ui(mp,d);
}

void div(LongGmp& u, long d, LongGmp& q, int& r);
#endif


#if __WORDSIZE==64
long root(LongGmp& x);
#endif
