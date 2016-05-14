#ifndef long64_h
#define long64_h 
#include<iostream>
#include<gmp.h>
#include"int64.h"
using namespace std;

inline int non_zero(int64 u) {return u != 0;}
//int root_n(int64,int);
int pow25(int64 x);
int64 root(int64);
void submul_int(int64&, int64&, int);
void addmul_int(int64&, int64&, int);
typedef int64 longint;
int64& F(int64&);
#endif
