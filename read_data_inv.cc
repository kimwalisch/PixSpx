#include<stdlib.h>
#include<iomanip>
#include<gmp.h>
#include"primes.h"
#include"typedefs.h"

using namespace std;
extern longint x;
longval but;
longval resx;
extern longval Delta;
extern int64  estimate_number_primes;

extern mpz_t tmp0;

void read_data_inv(int argc, char *argv[]) {
  mpz_init(tmp0);
  but=argv[1];
  atolong(x,argv[2]);
  resx=argv[3];
  Delta=but;
  Delta-=resx;
}


void print_data_inv() {
  cout << "but          =" << setw(35) << but << "\n";
  cout << "x (source)   =" << setw(35) << x << "\n";
  cout << "resx           =" << setw(35) << resx << "\n";
  cout << "Delta = ecart=" << setw(35) << Delta << "\n";
  cout.flush();
}
