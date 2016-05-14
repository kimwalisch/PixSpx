#ifndef longfixed_h
#define longfixed_h
#include<gmp.h>
#include<string>
#include<iostream>
#include"int64.h"
#include"longaux.h"

using namespace std;

template<int N> class Longfixed{
  mp_limb_t mp[N];

public:

  Longfixed();// {set_zero<N>(mp);}
  Longfixed(int y);
  Longfixed(string str);

  Longfixed& operator=(Longfixed& u) {copy<N>(mp, u.mp);}
  Longfixed(Longfixed& u) {copy<N>(mp, u.mp);}

  int is_zero();
  void set_to_zero();

  void operator=(int y);

  void operator+= (int y);
  void operator-= (int y);
  void operator*= (int y);
  int  divint(int y);

  void operator+= (int64 y);
  void operator-= (int64 y);
  void operator*= (int64 y);

  void operator+= (Longfixed& y);
  void operator-= (Longfixed& y);
  void operator*= (Longfixed<N> u);

  void display();


  Longfixed operator-();

  int operator>=(Longfixed& u);
};

template<int N>
void 
Longfixed<N>::set_to_zero() {
  set_zero<N>(mp);
}

template<int N>
Longfixed<N>::Longfixed() {
  set_to_zero();
}

template<int N>
Longfixed<N>::Longfixed(int y) {
  mp[0]=y;
  if (y >= 0)
      set_to<N-1>(mp+1,0);
  else
      set_to<N-1>(mp+1,-1);
}

template<int N>
void Longfixed<N>::operator=(int y) {
  mp[0]=y;
  if (y >= 0)
      set_to<N-1>(mp+1,0);
  else
      set_to<N-1>(mp+1,-1);
}


template<int N>
inline void 
Longfixed<N>::operator+= (int y) {
    mpn_add_1(mp, mp, N,  (mp_limb_t)y);
}

template<int N>
inline void 
Longfixed<N>::operator-= (int y) {
    mpn_sub_1(mp, mp, N,  (mp_limb_t)y);
}

template<int N>
inline void 
Longfixed<N>::operator+= (int64 y) {
    mpn_add(mp, mp, N,  (mp_limb_t*)&y, 2);
}

template<int N>
inline void 
Longfixed<N>::operator-= (int64 y) {
    mpn_sub(mp, mp, N,  (mp_limb_t*)&y, 2);
}

template<int N>
inline int 
Longfixed<N>::is_zero() {
  return is_null<N>(mp);
}

template<int N>  
inline void 
Longfixed<N>::operator*= (int y) {
  mpn_mul_1 (mp, mp,N , y);
}

template<int N>  
inline void 
Longfixed<N>::operator*= (int64 y) {
  mpn_mul_1 (mp, mp,N ,(mp_limb_t*) &y,2);
}

template<int N>
inline int
Longfixed<N>::divint(int y) {
  return
    mpn_divrem_1 (mp,0, mp,N, y);
}



template<int N>
inline void 
Longfixed<N>::operator+= (Longfixed& y) {
    mpn_add_n(mp, mp, y.mp, N);
}

template<int N>
inline void 
Longfixed<N>::operator-= (Longfixed& y) {
    mpn_sub_n(mp, mp, y.mp, N);
}

extern mp_limb_t limb_buff[];

template<int N>
inline void 
Longfixed<N>::operator*=(Longfixed<N> u) {
  mpn_mul((mpr)limb_buff, mp, N, mp, N);
  copy<N>(mp,(mpr)limb_buff);
}

template<int N>
inline int
Longfixed<N>::operator>=(Longfixed& u) {
  return bigger<N>(mp,u.mp);
}

template<int N>
Longfixed<N>
Longfixed<N>::operator-() {
  Longfixed res=*this;
  negat<N>((mpr)res.mp);
  return res;
}

#endif

