#include<iostream>
using namespace std;
#include"globals.h"

longval res;

longval& petit_sfx() {
  cerr << "petit_sfx avec x = " << x << "\n";
  if (x < 1) {
    return res;
  }
  make_primes(x);
  for (int i = 1; i <= number_of_primes(); i++) {
    int p = prime(i);
    if (x >= p) {
      res += fint(prime(i));
    }
  }
  return res;
}

longval& sfx() {
  if (x < 125) {
    cerr << "x < 125\n";
    return petit_sfx();
  }
  compute_p2xy();
  compute_fixy();
  res += fixy;
  res += Sy;
  res -= 1;
  res -= p2xy;
  cerr << "Sf(x) = fixy(x,y) + Sy - 1 - p2(x,y) = " << res << "\n";
  return res;
}
