#include"globals.h"
#include"arith_tools.h"
//#include"longint.h"
#include"sieve_dynamic.h"

#define DEBUGINTERVALLESF 0

static longval tmp;
static longint xp;
static longint xa;
static int64 xb;
static longint xap;
static longint xpm;

static int64 xbp;
static int p;
static int ip;
static int m_max;
static int mminm1;

static longval p_sum;

static longval cnt;
extern int cnt_S3aux;
extern longval S3aux_res;
extern int lastcompte;

static Sieve_dynamic<longval,medval>  sieve;
int cntnb=0;
int cntb=0;
int cnte_ecartees = 0;
int* cnte_omise;


void binary_leaves(); // definie plus bas
void n_binary_leaves();// definie plus bas

longval& S3() {
  cerr << "Calcul de S3() : crible jusqu a " << FINCRIBLE2 << endl;
  int y5 = y/5;
  int r = y5%PK;
  int sieve_size = (r) ? y5 + PK -r : y5;
  if (sieve_size < PK) sieve_size = PK;
  cerr << "sieve_size = " << sieve_size << "   FINCRIBLE2 = "<< FINCRIBLE2
       << " x4   " << x4 << endl;
  sieve.setup(sieve_size, FINCRIBLE2, x4);
  // Deplaisant on va cribler inutilement par x^(1/4) qd x est une
  // puissance 4eme
  while (!sieve.done()) {
#if DEBUGINTERVALLESF
    sieve.showindow();
#endif
    xa = x/sieve.A;
    xb = x/(sieve.B+1);
    while (!sieve.window_sieved())
      {
	p=sieve.currentp;
	ip=sieve.curp_index;
	xp = x/p;
	xap = xa/p;
	m_max = min(xap,z);
	xbp = xb/p; // xp/(sieve.B+1);
	if (xbp < m_max) {
	  mminm1 = max(xbp,z/sieve.currentp);  
#if DEBUGFAUX
	  cerr << "currentp = " << setw(6) << sieve.currentp;
	  cerr << "     Intervalle aux [" 
	       << setw(6) << mminm1 << "," << setw(6) << m_max << "]" << endl;
#endif 
	if (sieve.currentp <= z2)
	  n_binary_leaves();
	binary_leaves();
	}
	sieve.remember();
	sieve.sieve_by_currentp();
      }
    etoile(sieve.A, FINCRIBLE2);
    sieve.forward();
  }
  tmp  = binary_sum;
  tmp += nbinary_sum_pos;
  tmp -= nbinary_sum_neg;
  tmp += S3aux_res;
  cerr << endl;
  cerr << setw(10) << cntb   <<    "  feuilles binaires     -->  "
       << setw(20) << binary_sum << endl;
  cerr << setw(10) << cntnb  <<    "  feuilles n_naires pos -->  "
       << setw(20) << nbinary_sum_pos << endl;
  cerr << setw(10) << cntnb  <<    "  feuilles n_naires neg -->  "
       << setw(20) << nbinary_sum_neg << endl;
  cerr << setw(10) << cnt_S3aux << "  feuilles b_simples    -->  " 
       << setw(20) << S3aux_res << endl;
  cerr << setw(10) << cntb + cnt_S3aux << "  feuilles binaires "
       << "(binaires + b_simples)\n";
  cerr << "feuilles simples " << cnte_ecartees << endl;
  cnte_ecartees = 0;
  cerr << "S3() = feuil. binaires + feuil. naires + feuil. simples" <<endl;
  cerr << "S3 = " << tmp << endl << endl; 
  chronometre();
  cerr << endl;
  return tmp;
}

// Les feuilles ternaires de la forme sieve.currentp*m, ou m est un squarefree
// dont le plus petit facteur premier q est un premier >= prime(k+1)


void n_binary_leaves() {
  for (int q_index = ip+1 ; q_index <= pi_z2; q_index++)
    { 
      int* mindex =first_pos_index_of_bigger_than(q_index, mminm1);
      int m = *mindex++;
      while (m <= m_max)
	{
	  cntnb++;
	  xpm = xp/m;
	  p_sum = 0;
	  sieve.count(p_sum,xpm);
	  p_sum *= fint(p);  // PEUT ETRE PAS ZZZZ longint ou int64
	  p_sum *= fint(m);
	  nbinary_sum_neg += p_sum;
	  m=*mindex++;
	}
      mindex =first_neg_index_of_bigger_than(q_index, mminm1);
      m=*mindex++;
      while (m  <= m_max)
	{
	  cntnb++;
	  xpm = xp/m;
	  p_sum = 0;
	  sieve.count(p_sum,xpm);
	  p_sum *= fint(p);  // PEUT ETRE PAS ZZZZ longint ou int64
	  p_sum *= fint(m);
	  nbinary_sum_pos += p_sum;
	  m = *mindex++;
	}
    }
}

void binary_leaves()
{
  int maxm  = min(m_max,y);
  longint xp2 = xp/p; //ZZZZZ
  int64 xp3 = xp2/p; //ZZZZ
  maxm = min(maxm, xp3); //ZZZZ
  int q_index = index_of_first_prime_bigger_than(mminm1);
  q_index = max(q_index, ip+1);
  int q = prime(q_index);
  while (q <= maxm)
    {
      cntb++;
      xpm = xp/q;
      sieve.count(cnt,xpm);
      cnt *= fint(p);
      cnt *= fint(q);
      binary_sum += cnt;
      q = prime(++q_index);
    }
}

