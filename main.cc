#include<iostream>
using namespace std;
#include"globals.h"

longval& sfx();

int main(int argc, char* argv[]) {
  read_data_compute_data_aux(argc,argv);
  //  cout << "Sf(x)       =" << setw(22) << sfx() << "\n";
  cout << x << " " << sfx() << "\n";
}
