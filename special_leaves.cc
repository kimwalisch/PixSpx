#include"globals.h"

extern longval special_sum;
longval& S1();
longval& S2();
longval& S3();

longval& special_leaves() {
  special_sum += S1();
  special_sum += S2();
  special_sum += S3();
  return special_sum;
} 

