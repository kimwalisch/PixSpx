#include"arith_tools.h"

char buff[20];

void itoa(int n, int Base, char* str) {
  if (n==0) {
    str[0] = '0';
    str[1] = char(0);
  }
  else {
    int i=20,j=0;
    int m = abs(n);
    buff[--i]=char(0);
    while (m > 0) {
      int r= m % Base;
      m/= Base;
      buff[--i] = '0'+ r;
    }
    if (n < 0)
      buff[--i] = '-';
    for(; i< 20; i++)
      str[j++] = buff[i];
  }
}


