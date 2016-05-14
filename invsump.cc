#include<stdlib.h>
#include<iomanip>
#include<gmp.h>
#include<math.h>

#include"primes.h"
#include"typedefs.h"
#include"longgmp.h"
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

double LI2INV(double);
longval& sfx();
extern longval res;

using namespace std;
extern longint x;
longval u;
extern longval yx;
extern longval Delta;
extern int64  estimate_number_primes;
longval ux;
longval Delta;
longint p;

Sievelng<longint> last_sieve;

int main(int argc, char *argv[]) {
  u=argv[1];
  if (u < 100) {
    int i;
    make_primes(50);
    longval s=0;
    for(i=0; s <= u; s+= prime(++i));
    s -= prime(i);
    u -= s;
    Delta = prime(i) -int(s);
    cerr << "p = " << prime(i-1) << "     nextp = " << prime(i)
	 << "   Delta = " << u << endl;
    return 0;
  }
  mpz_init(tmp0);
  double udouble = u;
  double xdouble = LI2INV(udouble);
  cerr << "u       = " << u << endl;
  cerr << "udouble = " << udouble << endl;
  cerr << "xdouble = " << xdouble << endl;
  x = xdouble;
  cerr << "x = " << x << endl;
  compute_aux_data();
  print_data();
  cerr << "  x= " << x << "  sfx= " << sfx() << endl;
  ux = res;
  //ux = (char *) "999999999658280586244840501038306614";
  //x = (char *)" 9291904454837350400";
  //cerr << "ux = " << ux << endl;
  Delta = u-ux;
  cerr << "Delta = u-sf(x) = " << Delta << endl;
  double AbsDelta_x =  fabs(double(Delta))/double(x);
  cerr << "AbsDelta/x = " <<  AbsDelta_x << endl;
  double logx = log(xdouble);
  cerr << "logx = " << logx << endl;
  int64 size_approx = int(logx) * AbsDelta_x;
  int64 size_aux = (int64)(1.2 * size_approx);
  cerr << "Crible terminal :taille approx 1.2*logx*Delta = " 
       << size_aux << endl;
  last_sieve.setup(next_multiple(PK,size_aux));

  if (ux < u) {
    last_sieve.set_at_left(x);
    cerr << " A x B = " << last_sieve.A << "  " << x << "  " 
	 << last_sieve.B << endl;
    p = last_sieve.first_prime();
    cerr << "Le premier premier de la fenetre " << p << endl;
    while (p <= x)
      p=last_sieve.next_prime();
    cerr << "Le premier premier plus grand que x " 
	 << "p = " << p << endl;
    while(Delta >= p ) {
      Delta -= p;
      p=last_sieve.next_prime();
      // cout << "last_sieve.nextprime() = " << p << endl;
    }
    longint nextp = p;
    p = last_sieve.previous_prime();
    cout << "p = " << p << "   nextp = " << nextp  << 
      "    Delta = " << Delta << endl;
  }
  else {
    last_sieve.set_at_right(x);
    cerr << " A x B = " << last_sieve.A << "  " << x << "  " 
	 << last_sieve.B << endl;
    p = last_sieve.last_prime();
    //cerr << "Last prime = " << p << endl;
    while (Delta < 0)  {
      Delta += p;
      p = last_sieve.previous_prime();
    }
    longint nextp = last_sieve.next_prime();
    cout << "p = " << p << "   nextp = " << nextp  << 
      "    Delta = " << Delta << endl;
  }
}
