#include"longfixed.h"
#include"longgmp.h"
mp_limb_t limb_buff[20];

template<int N> 
Longfixed<N>::Longfixed(string str) {
  char c;
  int i = 0;
  set_to_zero();
  while ((c=str[i++])) {
    //    cerr << "c = " << c  << endl;
    *this *= 10;
    *this += (c-char('0'));
  }
}

template<int N>
inline void 
Longfixed<N>::display() {
  int r;
  char buff[500];
  Longfixed<N>u(*this);
  int i=0;

  while (!u.is_zero()) {
    r= u.divint(10);
    buff[i++] = char('0') + r;
  }
  for (--i; i >= 0; i--)
    cerr << buff[i];
  cerr << endl;
}


int main(void) {
  //  Longfixed<5> x("10000000000000000");
  //  Longfixed<5> y("10000000000000001");
  //x.display();

  Longfixed<6> x;
  //  LongGmp x;
  /*
  for (int i=0; i < 10000000; i++) {
      int y=rand();
      //cerr << "y = " << y << endl;
      x = y;
      x*=x;
      x*=x;
      //x.display();
    }
  */

  for (int i=0; i < 10000000; i++) {
      int y=rand();
      //cerr << "y = " << y << endl;
      x = y;
      x*=x;
      x*=x;
      //x.display();
    }

  exit(0);
  // cerr << (x >= y) << endl;
  //  (-x).display();
  //  cerr << -x << endl;
}
