#include"globals.h"
#define FXY_VERBOSE 1

longval ordinary_sum_pos;
longval ordinary_sum_neg;

longval ordinary_sum;
longval special_sum;

longval& special_leaves();

longval& compute_fixy() {
  cerr << endl << "CALCUL DE Fi(x,y,z) " << endl << endl;
  make_squarefree();
  fixy = ordinary_leaves();
  //  un_trait();
  fixy += special_leaves();
  cerr << "S() =  S1() + S2() + S3() = "<<special_sum << endl;
  cerr << "fixy = S0() + S() = " << fixy << "\n";
  un_trait();
  return fixy;
}
