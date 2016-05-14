#include<stdlib.h>
#include<iomanip>
#include<gmp.h>
#include<math.h>

#include"primes.h"
#include"typedefs.h"
#include"sieve.h"
#include"sievelng.h"
#include"f.h"
#include"arith_tools.h"
#include"chrono.h"

extern int64 x2;
extern int x3;
extern mpz_t tmp0;

void compute_aux_data();
void print_data();

double RINV(double);
longval& sfx();
extern longval res;

using namespace std;
extern longint x;
longval u;
extern longval yx;
extern longval Delta;
longval ux;
longval Delta;
longint p;
extern int y;

Sievelng<longint> last_sieve;
double Ei(double);

int main(int argc, char *argv[]) {
  atolong(u,argv[1]);
  if (u < 100)
    {
      make_primes(1000);
      cout << prime(u) << endl;
      return(0);
    }

  mpz_init(tmp0);
  cerr << "argc = " << argc << endl;
  if (argc==3)
    y = atoi(argv[2]);
  double udouble = u;
  double xdouble = RINV(udouble);
  cerr << "u       = " << u << endl;
  cerr << "udouble = " << udouble << endl;
  cerr << "xdouble = " << xdouble << endl;
  x = xdouble;
  cerr << "x = " << x << endl;
  compute_aux_data();
  print_data();
  ux = sfx();
  cerr << "x = " << x << endl;
  //  cerr << "sfx = " << sfx() << endl;
  ux = res; // ZZZ????
  Delta = u-ux;
  cerr << "Delta = u-sf(x) = " << Delta << endl;
  double logx = log(xdouble);
  int64 size_approx = int(logx) * int64(1+fabs(double(Delta)));
  cerr << "logx = " << logx << endl;
  int64 size_aux = (int64)(1.2 * size_approx);
  cerr << "Crible auxiliaire :taille approx 1.2*logx*Delta = " 
       << size_aux << endl;
  last_sieve.setup(next_multiple((int)PK,size_aux));

  if (Delta > 0) {
    last_sieve.set_at_left(x);
    cerr << "[A, B] = " << last_sieve.A << ", " << last_sieve.B << endl;
    un_trait();
    p = last_sieve.first_prime();
    while (p <= x)
      p=last_sieve.next_prime();
    cerr << "Le premier premier plus grand que x " 
	 << "p = " << p << endl;
    for (int i=1; Delta > i; i++) {
      p=last_sieve.next_prime();
      //      cerr << "p = " << p << endl;
    }
  }
  else {
    last_sieve.set_at_right(x);
    cerr << "[A, B] = " << last_sieve.A << ", " << last_sieve.B << endl;
    p = last_sieve.last_prime();
    while (x < p)
      p=last_sieve.previous_prime();
    cerr << "Le premier premier <= x : " << p << endl;
    while (Delta < 0)  {
      Delta += 1;
      p = last_sieve.previous_prime();
    }
  }
  chronometre();
  un_trait();
  cout << "p = " << p << endl; 
}
