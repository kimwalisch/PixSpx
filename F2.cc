#include<iostream>
#include"globals.h"
// La fonction F = sum(n | n <= u, (n,PK)=1)


static longint q;
static longval res;
static longval tmp; 
int r;

void div(longint&, int, longint&, int&);

longval& F(longint& u)  {
  div(u,PK,q,r);
  res = q;
  res -= 1;
  res *= PK*(FK/2) ;
  res += SK;
  res *= q;
  if (r) {
    tmp  = q;
    tmp *= PK;
    for (int k=0; (k < 8) && (CLASS[k] <= r) ; k++)
      { 
	res += tmp;
	res += CLASS[k];
      }
  }
  return res;
}




