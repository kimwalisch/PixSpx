#include"globals.h"

static longval Somme_V;
static longval Somme_V2;

longval& sommeV1();
longval& sommeV2();
longval& somme_W1_W2();
longval& somme_W3();
longval& somme_W4();
longval& somme_W5();

longval& compute_V() {
  Somme_V += sommeV2();
  Somme_V -= sommeV1();
  cerr << "Somme_V = sommeV2 - sommeV1 = " << Somme_V << endl;
  return Somme_V;
}


longval& sommeV2() {
  chronometre();
  Somme_V2 += somme_W1_W2();
  chronometre();
  un_trait();
  Somme_V2 += somme_W3();
  chronometre();
  un_trait();
  Somme_V2 += somme_W4();
  chronometre();
  un_trait();
  Somme_V2 += somme_W5();
  chronometre();
  un_trait();
  cerr << "SommeV2 = somW1 + somW2 + somW3 + somW4 + somW5 = " 
       << Somme_V2 << endl;
  return Somme_V2;
}

