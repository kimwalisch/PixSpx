#include"globals.h"
#define DEBUG_SQF 0
#include"chrono.h"
#include"arith_tools.h"

/*
  Construction de tous les entiers squarefree <= z, non premiers dont
  les diviseurs premiers sont inferieurs à y et donf le plus petit
  facteur premier est majore par z^(1/2) Ils sont partitionnes selon
  la valeur de leur plus petit diviseur premier. Pour chaque valeur de
  k la liste sqf_list_posp[k] contient les sqfree de plus petit diviseur
  prime(k) et admettant un nombre pair de facteurs premiers. La liste
  sqf_list_neg[k] contient les sqfree de plus petit diviseur prime(k) et
  admettant un nombre impair de facteurs premiers.
*/

static int dim;
static int cnt_pos = 0;
static int cnt_neg = 0;
static int cnt_tous = 0;

static Vector<int>  buff_pos;
static Vector<int>  buff_neg;
Vector<Vector<int> > sqf_list_pos;
Vector<Vector<int> > sqf_list_neg;

void squarefree_table_recursive_step_pos(int u, int i);

void 
squarefree_table_recursive_step_neg(int u, int i)
{
  int j = i;
  int zu = min(z/u,y);
  while (prime(j) <= zu)
    {
      int v = prime(j++)*u;
      cnt_tous++;
      buff_pos[cnt_pos++] = v;
      squarefree_table_recursive_step_pos(v, j);
    }
} 

void 
squarefree_table_recursive_step_pos(int u, int i)
{
  int j = i;
  int zu = min(z/u,y);
  while (prime(j) <= zu)
    {
      int v = prime(j++)*u;
      cnt_tous++;
      buff_neg[cnt_neg++] = v;
      squarefree_table_recursive_step_neg(v, j);
    }
} 


void 
squarefree_table_p_init(int i)
{
  buff_neg[0]  = prime(i);
  cnt_pos  = 0;
  cnt_neg  = 1;

  squarefree_table_recursive_step_neg(prime(i), i+1);

  sqf_list_pos[i].set_dim(cnt_pos+1);
  for (int j = 0; j < cnt_pos; j++)
    sqf_list_pos[i][j] = buff_pos[j];
  sqf_list_pos[i][cnt_pos] = INT_MAX;
  sqf_list_pos[i].quicksort();

  sqf_list_neg[i].set_dim(cnt_neg+1);
  for (int j = 0; j < cnt_neg; j++)
    sqf_list_neg[i][j] = buff_neg[j];
  sqf_list_neg[i][cnt_neg] = INT_MAX;
  sqf_list_neg[i].quicksort();
}

void 
make_squarefree()
{
  cerr << "Construction de la table des squarefree jusqu'a z = " 
       << z << endl;
  // sqf_list_last_range =  sqf_list_last_range;
  if (K > sqf_list_last_range) {
    cerr << "\nPas de squarefree\n";
    return;
  }

  dim = z/4;
  buff_pos.set_dim(dim); //ZZZZZ est il libere apres la construction
  buff_neg.set_dim(dim); //ZZZZZ est il libere apres la construction

  sqf_list_pos.set_dim(sqf_list_last_range+1);
  sqf_list_neg.set_dim(sqf_list_last_range+1);
  for (int i = K+1; i <= sqf_list_last_range; i++)
    {
      squarefree_table_p_init(i);
#if DEBUG_SQF > 0
      cerr << "Square-free lists for smallest prime factor = " 
	   << prime(i) << "\n";
      cerr << "Positive_list :" << endl;
      sqf_list_pos[i].display();
      cerr << "Negative_list :" << endl;
      sqf_list_neg[i].display();
#endif
    }
  cerr << "Suppression des buffers " << endl;
  buff_pos.free();
  buff_neg.free();
  cerr << "Nombre total de squarefree : " << cnt_tous << endl;
  chronometre();
  un_trait();
}

int* first_pos_index_of_bigger_than(int k, int m_0) {
  int m_index = sqf_list_pos[k].index_of_first_bigger_than(m_0);
  return &sqf_list_pos[k][m_index];
}

int* first_neg_index_of_bigger_than(int k, int m_0) {
  int m_index = sqf_list_neg[k].index_of_first_bigger_than(m_0);
  return &sqf_list_neg[k][m_index];
}

