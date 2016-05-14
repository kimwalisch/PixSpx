#include"longint.h"
#include"globals.h"

static longval SommeV2;

longval& compute_V2() {
  SommeV2 += compute_sommeW1W2();
  SommeV2 += compute_sommeW3();
  SommeV2 += compute_sommeW4();
  SommeV2 += compute_sommeW5();
  return SommeV2;
}


static longval sommeW3;
static longval sommeW4;
static longval sommeW5;

longval& compute_sommeW1W2() {
  return SommeW1W2;
}

longval& compute_sommeW3() {
  return SommeW3;
}

longval& compute_sommeW4() {
  return SommeW4;
}

longval& compute_sommeW1W2() {
  return SommeW5;
}
