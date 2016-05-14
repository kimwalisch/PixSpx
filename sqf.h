// -*- C++ -*-
#ifndef sqf_h 
#define sqf_h



void make_squarefree();
int index_of_first_prime_bigger_than(int x);

extern Vector<Vector<int> > sqf_list_pos;
extern Vector<Vector<int> > sqf_list_neg;

int* first_pos_index_of_bigger_than(int k, int m_0);
int* first_neg_index_of_bigger_than(int k, int m_0);

int next_free_for_prime(int numprime);
#endif
