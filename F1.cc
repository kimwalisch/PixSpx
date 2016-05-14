#include<iostream>
#include"globals.h"
#include"typedefs.h"
#include"int64.h"
#include"longint.h"
#include"longval.h"
// La fonction F = sum(n | n <= u, (n,PK)=2)
// lorsque f est la fonction a valeur
// entiere  f= n-> 1 (cas FUNCTION==1)
// ou       f= n->n  (cas FUNCTION==2)

static longint q;
static longval res;
int r;


void div(longint&, int, longint&, int&);


longval& F(longint& u) {
  div(u,PK,q,r);	
  res = q;
  res *= FK;
  if (r)
    res += 1+PRED[r-1];
  return res;
}




