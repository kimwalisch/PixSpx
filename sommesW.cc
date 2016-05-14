// ATTENTION VERIFIER LES TAILLES 
#include<iomanip>
#include"globals.h"
#include"arith_tools.h"
#include"sieve.h"
#include"int64.h"
#include"typedefs.h"
#include"primes.h"
#define DEBUGS3aux 0
#define DEBUGS3auxp 0
#define DEBUGS3auxq 0
#define DEBUGQV 0
#define DEBUGOMIS 1
#define DEBGS3INT 1
#define DEBGS4INT 1
#define DEBGS5INT 1
using namespace std;

static longval W3_res;
static longval W4_res;
static longval W5_res;
static longval pres;
static longval qres;

longval S3aux_res = 0;
static longval SommeW1W2;
static longval SommeS3aux;
static longval W1_res = 0;
static longval W2_res = 0;
static longval tmp;

static longint xa;
static longint xap;
static int64 xb; // PEUT ETRE int64
static int64 xp; // car p >= x4
static int64 sqrt_xa;

extern longval* Sx;

void S3aux_contrib();
void W1_contrib();
void W2_contrib();
int cnt_S3aux=0;


Sieve<int64> sieve;

longval& somme_W1_W2() {
  cerr << "In somme_W1_W2\n";
  int sieve_size = next_multiple(PK,y/4);
  sieve.setup(sieve_size, x2);
  sieve.set_fcounters();
  while (!sieve.done())
    {
      #if DEBUGS3aux
      sieve.showindow();
      #endif

      xa = x/sieve.A;
      sqrt_xa = root_n(xa,2);
      xb = x/(sieve.B+1);  // Verifier si operation existe;
      sieve.eratosthene();
      W1_contrib();

      W2_contrib();

      S3aux_contrib();

      sieve.forward();
    }
  cerr << "Calcul au passage de S3aux() (les feuilles binaires simples): "
       << endl;
  cerr << cnt_S3aux << "    feuilles b_simples  "   
       << "  -->  S3aux = " << S3aux_res << endl;
  un_trait();
  cerr << setw(20) << "sommeW1 = " << W1_res << endl;
  cerr << setw(20) << "sommeW2 = " << W2_res << endl;
  SommeW1W2 += W1_res;
  SommeW1W2 += W2_res;
  SommeS3aux += S3aux_res;
  return SommeW1W2;
}

//-------------------------------------------------------------------------
// Notons [u] la partie entiere de u
// L'encadrement             A        <= [x/(pq)] <= B
// est equivalent a     [x/(B+1)]/p   <     q     <= [[x/A]/p]
//
//-------------------------------------------------------------------------


void  W1_contrib() {
  for (int ip = max(pi_x4 +1,K+1); ip <= pi_xyy; ip++) {
    int p = prime(ip);
    xp=x/p;
    int64 xpa = xa/p;
    int64 q2  = min(y,xpa);
    int64 q1  = xb/p;
    if (q1 > y)
      continue;
    //    int iq1 = 1+max(pi((int)q1),ip); 
    int iq2  = pi((int)q2);
    int iq1 = (q1 > p)? 1+pi(q1) : 1+ip;
    //int iq2  = (y <= xpa) ? pi_y : pi(xpa);
    for (int iq = iq1; iq <=iq2; iq++) {
      int64 x_p_q = xp/prime(iq);
      sieve.count_f(tmp, x_p_q);
      tmp *= fint(p);  // ZZ
      tmp *= fint(prime(iq)); // ZZ
      W1_res += tmp;
    }
  }
}


void W2_contrib() {
  int pmin = max(xyy,x4);
  //  cerr << "In W2_contrib\n";
  pmin = max(pmin,xb/(sieve.B+1));
  if(pmin>y)
    return;
  int ip1 = 1+pi(pmin);
  //  int ip1 = 1+max(pi_xyy,pi_x4);
  int ip2 = pi(min(sqrt_x_y, sqrt_xa)); 
  //  cerr << "Somme 2 intervalle ip [" << ip1 << ", " << ip2 << "]\n";
  for (int ip = ip1; ip <= ip2; ip++) {
    int p = prime(ip);
    xp=x/p;
    xap = xa/p;
    int maxq  = min(xap,y);
    int64 minq  = xb/p;
    if (minq > y)
      continue;
    int iq1 = 1+max(pi((int)minq),ip); 
    //int iq1 = (minq > p)? 1+pi(minq) : 1+ip;
    int xp2 = root(xp);
    int iq2 = pi(min(xp2,maxq));
    for (int iq = iq1; iq <= iq2; iq++) {
      int64 x_p_q = xp/prime(iq);
      sieve.count_f(tmp, x_p_q);
      tmp *= fint(p); // ZZZZZZZZZZ
      tmp *= fint(prime(iq)); // ZZZZZZZZZZ
      W2_res += tmp;
    }
  }
}


void S3aux_contrib() {
  int xby = xb/y;
  if (xby > y)
    return;
  int ip1 = 1+pi(max(cbrt_xy,xby));
  if(ip1 <= K)
    return;
  int ip2 = pi(min(x4,sqrt_xa));
  #if DEBUGS3auxp
  cerr << "[ip1,i2]  = [" << ip1 << "," << ip2 << "]\n";
  #endif
  for (int ip=ip1;ip<=ip2;ip++)
      {
	#if DEBUGS3auxp
	cerr << "ip = " << ip << endl;
	#endif
	int iq,iq1,iq2;
	int p   = prime(ip);
	xp  = x/p;
	int64 xp2 = xp/p;
	int64 xap = xa/p;
	#if DEBUGS3auxp
	cerr << "xp2 = " << xp2 << endl;
	cerr << "xap = " << xap << endl;
	cerr << "min(y,xap) " << min(y,xap) << endl;
	cerr << "xp2/p = " << xp2/p << endl;
	cerr << "B = " << sieve.B << endl;
	cerr << "xb/p = " << xb/p << endl;
	cerr << "max(xp2/p,xb/p)  " << max(xp2/p,xb/p) << endl; 
	#endif
	int qmin=max(xp2/p,xb/p);
	if (qmin > y)
	  return;
	iq1 = 1+pi(max(xp2/p,xb/p));
	iq2 = pi(min(y,xap));  //OK
        #if DEBUGS3auxq
	cerr << setw(8) << ip << "   xap = " << xap;
	cerr << "[iq1,iq2]  = [" << iq1 << "," << iq2 << "]\n";
        #endif
	for (iq=iq1;iq<=iq2;iq++)
	  {
	    int64 x_p_q = xp/prime(iq);
	    #if DEBUGOMIS
	    cnt_S3aux++;
	    #endif
	    sieve.count_f(tmp,x_p_q);
	    /*
	    S3aux_res += tmp;
	    S3aux_res -= Sx[ip-1];
	    S3aux_res += 1;
	    */
	    tmp -= Sx[ip-1];
	    tmp+=1;
	    tmp*=fint(p);
	    tmp*=fint(prime(iq));
	    S3aux_res += tmp;
	    #if DEBUGQV
	    cerr << "p = " << p << endl;
	    cerr << "         " << prime(iq) << " -> " << x_p_q 
		 <<  "pi(xpq) = " << tmp
		 <<   "Sx[ip-1] = " << Sx[ip-1] << endl;
            #endif
	  }
	#if DEBUGS3auxq 
	cerr << "S3aux_contrib out S3aux_res = " << S3aux_res << endl;
	#endif
      }
}


longval& somme_W3() {
  int ip1 = 1+max(pi_xyy,pi_x4);
  int ip2 = pi_sqrt_x_y;
#if DEBGS3INT
 cerr << "Somme_W3 intervalle ip [" << ip1 << ", " << ip2 << "]\n";
#endif

  for (int ip = ip1;  ip <=  ip2; ip++) {
    pres = 0;
    int p = prime(ip);
    xp=x/p;
    int xp2 = root(xp);
    int iq = 1+pi(xp2);
    int q=prime(iq);
    while (q <= y) {
      int xpq = xp/q;
      int s = pi(xpq);
      int xps = xp/prime(s);
      int t = pi(min(xps,y));
      qres  = Sx[t];
      qres -= Sx[iq-1];
      qres *= Sx[pi(xpq)];
      pres += qres;
      //pres += (t-iq+1)*Sx[pi(xpq)];
      iq = t+1;
      q = prime(iq);
    }
    addmul_int(W3_res,pres,fint(p));
    // cerr << "W3 p " << p << " -> " << pres << endl;
  }
  cerr << setw(20) << "sommeW3 = " << W3_res << endl;
  return W3_res;
}

longval& somme_W5() {
  int ip1 = 1+pi_sqrt_x_y;
  int ip2 = pi_x3;
#if DEBGS5INT
 cerr << "Somme_W5 intervalle ip [" << ip1 << ", " << ip2 << "]\n";
#endif

  for (int ip = ip1; ip <= ip2; ip++) {
    pres = 0;
    int p = prime(ip);
    xp = x/p;
    int xp2 = root(xp);
    int iq = 1+pi(xp2);
    int x_p2 = xp/p;
    int q=prime(iq);
    while (q <= x_p2) {
      int xpq = xp/q;
      int s = pi(xpq);
      int xps=xp/prime(s);
      int t = pi(min(xps,y));
      qres = Sx[t];
      qres -= Sx[iq-1];
      qres *= Sx[pi(xpq)];
      pres += qres;
      iq = t+1;
      q = prime(iq);
    }
    addmul_int(W5_res,pres,fint(p));
  }
  cerr << setw(20) << "sommeW5 = " << W5_res << endl;
  return W5_res;
}

longval&  somme_W4() {
  int ip1 =  1+pi_sqrt_x_y;
  int ip2 =  pi_x3;
#if DEBGS4INT
 cerr << "Somme_W4 intervalle ip [" << ip1 << ", " << ip2 << "]\n";
#endif

  for (int ip =ip1; ip <= ip2; ip++) {
    int p = prime(ip);
    xp=x/p;
    int xp2 = root(xp);
    pres = 0;
    int q;
    for (int iq=1+ip; (q=prime(iq)) <= xp2; iq++) { 
      int xpq = xp/q;
      addmul_int(pres,Sx[pi(xpq)],fint(q));
    }
    addmul_int(W4_res,pres,fint(p));
  }
  cerr << setw(20) << "sommeW4 = " << W4_res << endl;
  return W4_res;
}

