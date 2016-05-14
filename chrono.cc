#include<iostream>
#include<time.h>
#define VERBOSE
#include"int64.h"
using namespace std;

static int lastime = 0 ;
static int lastcompte = 0;

void un_trait(void)
{int i;
 for (i = 0 ; i < 80 ; i++) 
   cerr << "_";
 cerr << endl;
}


void chronometre(void )
{clock_t duree,newtime;
 newtime = clock()/CLOCKS_PER_SEC;
 duree   = newtime - lastime;
 lastime = newtime;
#ifdef VERBOSE
 cerr << "Duree de cette phase " << duree << " secondes" << endl;
 // un_trait();
 fflush(stdout);
#endif
}


void etoile(int64 FIN, int64 FINCRIBLE)
{
 int newcompte = 80*FIN/FINCRIBLE;
 if (newcompte == lastcompte )
   return;
 for ( int i = lastcompte+1; i <= newcompte; i++) 
   cerr << "*";
 cerr.flush();
 // fflush(stdout);
 lastcompte = newcompte;
}
