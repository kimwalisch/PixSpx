#include<stdlib.h>
#include<iomanip>
#include<gmp.h>
#include"primes.h"
#include"globals.h"
#include"chrono.h"
#include"data.h"
//extern Ctable_fast ptable;

using namespace std;
//longint& atolong(char* s);
void compute_aux_data();

//mpz_t tmp0;
//static longint x_y;
//static longint x_z;

void read_data_compute_data_aux(int argc, char *argv[]) {
  atolong(x,argv[1]);
  if (x < 125) {
    return;
  }
  mpf_set_default_prec(128);
  mpz_init(tmp0);

  if (argc==4) {
    y = atoi(argv[2]);
    z = atoi(argv[3]);
  }
  else {
    y = z = 0;
  }
  compute_aux_data();
  print_data();
}


void compute_aux_data() {
  cerr << "In compute_aux_data\n";
#ifdef longdouble_h
  init_Finv();
#endif
  x2 = root_n(x,2);
  x3 = root_n(x,3);
  x4 = root_n(x,4);

  //  cerr << " y = " << y << endl;
  if (y < x3) {
    y = max(pow25(x)/5*4,x3);
    z = 5*y;
  }
  x_y = x/y;
  if (z > x2)
    z = x2;
  if (z < y)
    z=y;
  make_primes(y+200,1);

  pi_y = pi(y);

  sqrt_x_y = root(x_y);
  
  xyy = x_y/y;
  pi_xyy = pi(xyy);
  pi_x3 = pi(x3);
  pi_x4 = pi(x4);
  pi_sqrt_x_y = pi(sqrt_x_y);
  z2 = sqrt(z);
  pi_z2 = pi(z2);
  cbrt_xy = root_n(x_y,3);

  sqf_list_last_range = min(pi_y-1, pi_z2);
  FINCRIBLE1 = x_y;
  FINCRIBLE2 = x/z;

  for (int i=1; i <= max(pi_y,K); i++)  {
    Sy += fint(prime(i));
  }
}

void print_data() {
  cerr << "x           =" << setw(22) << x << "\n";
  cerr << "y           =" << setw(22) << y << "\n";
  cerr << "z           =" << setw(22) << z << "\n";

  cerr <<  "x^(1/2)     =" << setw(22) << x2 << "\n";
  cerr <<  "x^(1/4)     =" << setw(22) << x4 << "\n";
  cerr <<  "x^(1/3)     =" << setw(22) << x3 << "\n";
  cerr <<  "x/y^2       =" << setw(22) << xyy     << "\n";

  cerr << "x_y         =" << setw(22) << x_y       << "\n";
  cerr << "(x/y)^(1/2) =" << setw(22) << sqrt_x_y  << "\n";
  cerr << "cbrt_xy     =" << setw(22) << cbrt_xy << endl;
  cerr << "pi_y        =" << setw(22) << pi_y      << "\n";
  cerr << "pi_x3       =" << setw(22) << pi_x3  << "\n";
  cerr << "pi_x4       =" << setw(22) << pi_x4  << "\n";
  cerr << "pi(x/y^2)   =" << setw(22) << pi_xyy    << "\n";
  cerr << "pi(z^(1/2)) =" << setw(22) << pi_z2<< "\n";
  cerr << "sqf_lst_rng =" << setw(22) << sqf_list_last_range<< "\n";
  cerr << "FINCRIBLE1  =" << setw(22) << FINCRIBLE1 << "\n";
  cerr << "FINCRIBLE2  =" << setw(22) << FINCRIBLE2 << "\n";
  cerr << "Sy          =" << setw(22) << Sy << "\n";
  un_trait();
  cerr << endl;
  cerr.flush();
}
