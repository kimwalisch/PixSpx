#include<iostream>
using namespace std;
#include"globals.h"
#include"sieve_dynamic.h"
#include"p2xy.h"

longint res;



void read_data_compute_data_aux(int argc, char *argv[]) {
  mpz_init(tmp0);
  x1 = atolong(argv[1]);
  x2 = atolong(atgv[2]);
}

longint& sfx() {
  compute_p2xy<longint>();
  compute_fixy();
  res += fixy;
  res += Sy;
  res -= 1;
  res -= p2xy;
  cout << "Sf(x) = fixy(x,y) + Sy - 1 - p2(x,y) = " << res << "\n";
  un_trait();
  return res;
}

int main(int argc, char* argv[]) {
  read_data_compute_data_aux(argc,argv);
  print_data();
  cout << "Sf(x) = " <<  sfx() << "\n";
}
