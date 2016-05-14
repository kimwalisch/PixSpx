//-------------------------------------------------------------------------
//
//                  LES METHODES
//
//-------------------------------------------------------------------------

template<class LONGVAL, class MEDVAL>
void
Sieve_dynamic<LONGVAL, MEDVAL>::setup(int size ,int64 end, int pmax)
{
  if (size % PK) {
    cout << "Erreur: creation d'un Sieve_dynamic = " << size\
	 << " doit etre un multiple de " << PK << endl;
    exit(0);
  }
  A=1; 
  B=size;
  END = end;
  SIZE=size;
  BSIZE = (SIZE/PK)*FK;
  curp_index = K+1;
  currentp = prime(K+1);
  max_prime = pmax;
  nb_primes = pi(pmax);
  BASE=1;
  while (BASE < BSIZE)
    BASE *=2;
  local_sum = new MEDVAL[BASE+BSIZE];
  if ( local_sum == NULL)
    {
      cout << "Not enough memory for local_sum\n";
      exit(0);
    }
  previous_total = new LONGVAL[nb_primes+1];
  for (int k=0; k <= nb_primes; k++)
      previous_total[k] = 0;
  if (previous_total == NULL)
    {
      cout << "Not enough memory for previous_total\n";
      exit(0);
    }
  fill();
}

template <class LONGVAL, class MEDVAL>
void 
Sieve_dynamic<LONGVAL, MEDVAL>::fill()
{
  int i,j;
  // Remplissage de la ligne superieure
  for (i = BASE ; i < BASE+BSIZE ; i++) { // m+m ou m+BASE
    local_sum[i] = f64(image(i-BASE)); 
  }
  // La deuxieme ligne
  for (i=BASE, j=BASE/2; i< BASE+BSIZE; i+=2,j++)
    {
      local_sum[j] = local_sum[i];
    }
  for (i=BASE+1, j=BASE/2; i< BASE+BSIZE; i+=2,j++)
    {
      local_sum[j] += local_sum[i];
    }
  for (j=(BASE+BSIZE)/2; j< BASE; j++)
    local_sum[j] = 0;

  // Les suivantes

  int m = BASE>>2;
  while (m) {
    for (i = m; i  < m+m; i++) {
      local_sum[i]  = local_sum[2*i];
      local_sum[i] += local_sum[2*i+1];
    }
    m = m>>1;
  }
}

template <class LONGVAL, class MEDVAL>
void
Sieve_dynamic<LONGVAL, MEDVAL>::showindow(void) {
  cout << "Fenetre [" << A << ", " << B << "]" << endl;
}


template <class LONGVAL, class MEDVAL>
void
Sieve_dynamic<LONGVAL, MEDVAL>::display(void)
{
  cout << "Sieve_dynamic::display :  fenetre : [" 
       << A  << ", "
       << B << "  currentp = " << currentp << "]\n";
  
#if DYNAMIC_VERBOSE > 0
  if (nb_primes) {
    cout << "Sieve_dynamic<LONGVAL>::display :  Les comptes: \n";
    for (int k=1; k <= nb_primes; k++) {
      cout << setw(2) << k << " -> " << setw(8) << previous_total[k]
	   << "\n";
    }}

  cout << "Sieve_dynamic<LONGVAL>::display :  Les valeurs de f \n";
  for (int i = 0 ; i <= index(B) ; i++)
    { 
      if(is_set_bit(i))
      {
	cout.width(8);
	//	cout << f64(image(i));
	cout << image(i);
      }
      else
      {
	cout.width(8);
	cout << "__";
      }
    }
  cout << "\nSieve_dynamic<LONGVAL>::display : compteurs\n";
  for (int i=0 ; i <= index(B) ; i++)
    {
      count(sdyntmp1,image(i));
      cout << setw(8) << sdyntmp1;
    }
  cout << "\n";

  cout << "\nSieve_dynamic<LONGVAL>::display : compteurs locaux\n";
  for (int i=0 ; i <= index(B) ; i++)
    {
      cout << setw(8) << local_count(i);
    }
  cout << "\n";
#endif
}

/*
template <class LONGVAL, class MEDVAL>
void 
Sieve_dynamic<LONGVAL, MEDVAL>::suppress(int64 u)
{
  if is_set(u)
    {
      MEDVAL v = f64(u);
      int i= index(u-A);
      do {
	local_sum[i]-= v;
      }
      while (i >>= 1);
    }
}
*/


// Fonction de crible de la fenetre courante
template <class LONGVAL, class MEDVAL>
MEDVAL 
Sieve_dynamic<LONGVAL, MEDVAL>::local_count(int offset)
{
  MEDVAL som=local_sum[1];
  int i = offset+BASE;
  while (i > 0) {
    if (!(i % 2))
      som -= local_sum[i+1];
    i /= 2;
  }
  return som;
}


template<class LONGVAL, class MEDVAL>
void
Sieve_dynamic<LONGVAL, MEDVAL>::sieve_by_currentp() {
  int q = inversePK(currentp);
  int increment = FK*currentp;
  int64 debut=(A-1) % currentp; // ZZZZZZZZZZZZZZZ (au lieu de int debut...

  for (int k=0; k < FK; k++) {
    int i0 = q*(debut+CLASS[k]) % currentp;
    if (i0) 
      i0 = currentp-i0;
    int ibase = k + FK*i0;
    for (int  i = ibase ; i <= index(B) ; i += increment ) unset_bit(i);
  }
  currentp = prime(++curp_index);
}

template<class LONGVAL, class MEDVAL>
void 
Sieve_dynamic<LONGVAL, MEDVAL>::forward() {
  A += SIZE;
  B += SIZE;
  fill(); 
  curp_index = K+1;
  currentp = prime(curp_index);
}

template<class LONGVAL, class MEDVAL>
void 
Sieve_dynamic<LONGVAL, MEDVAL>::unset_bit(int offset)
{
  if (is_set_bit(offset))
    {
      int i= BASE+offset;
      MEDVAL v = local_sum[i];
      do {
	local_sum[i]-= v;
      }
      while (i >>= 1);
    }
}


template <class LONGVAL, class MEDVAL>
void 
Sieve_dynamic<LONGVAL, MEDVAL>::count(LONGVAL& res,int64 u) {
  res = local_count(index(u));
  res += previous_total[curp_index];  
}

static longval tmp2;

template<class LONGVAL, class MEDVAL>
void 
Sieve_dynamic<LONGVAL, MEDVAL>::remember() {
  count(tmp2,B);
  // sdyntmp1 = local_count(BSIZE-1);
  // previous_total[curp_index] += sdyntmp1;
  // cout << "rememer curp_index = " << curp_index 
  //     << " -> " << tmp2 << endl;
  previous_total[curp_index] = tmp2;
  //  count(previous_total[curp_index],B);
}

