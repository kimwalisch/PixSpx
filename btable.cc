#include<iostream>
#include"btable.h"
#define DEBUG_SVB 0
using namespace std;
#include"presieve30.h"

void Btable::display(unsigned n) const
{
  cerr << "Bit_size: " << bit_size << "\n";
  if ((n > bit_size) || (!n)) 
    n = bit_size;
 
  for (unsigned i = 0 ; i < n ; i++)
    {
      cerr.width(4);
      if (is_set_bit(i)) cerr << 1 ;
      else cerr << 0 ;
    }
  cerr << "\n";
}

void  Btable::show_bits() {
  for (unsigned i = 0; i < bsize(); i++) {
    int c;
    if (is_set_bit(i)) 
      c=1;
    else c=0;
    cerr << c;
  }
  cerr << "\n";
}


void Btable::fill()
{
  for (unsigned i = 0 ; i < word_size ; i++)	
    words[i] = ~0;
}

void Btable::delete_words()
{
  if (words != NULL)
    {
#if (DEBUG_SVB > 0)
      cerr << "~Btable: suppression of " << word_size <<" words\n";
#endif
      delete [] words;
      words = NULL;
    } 
}

Btable::~Btable()
{
#if (DEBUG_SVB > 0)
  cerr << "Suppression d'une Btable de taille " << bit_size << "\n";
#endif
  if (words != NULL)
    delete_words();
}

Ctable_compact::~Ctable_compact() {
#if (DEBUG_SVB > 0)
  cerr << "~Ctable_compact: suppression of count_array \n";
  delete [] count_array;
#endif
}

Ctable_fast::~Ctable_fast() {
#if (DEBUG_SVB > 0)
  cerr << "~Ctable_fast: suppression of count_array \n";
  delete [] count_array;
#endif
}

void Btable::setup(unsigned n)
{
#if (DEBUG_SVB > 0)
  cerr << "Btable::Btable(unsigned n) with  n = " << n << "\n";
#endif
  bit_size = n;
  word_size  = 
    (n & WORDSIZEMOINS1)?   (n >> WORDSIZE2)  + 1 : n >> WORDSIZE2;
  words = new unsigned[word_size];
  if ( words == NULL)
    {
      cerr << "Not enough memory to initialize words\n";
      exit(0);
    }
  for (unsigned i = 0; i < word_size; i++)
    words[i] = ~0;
}

void Ctable_compact::setup(unsigned n) {
  Btable::setup(n);
  count_array = new unsigned[wsize()];
  cerr << "Ctable_compact cree" << endl;
}


void Ctable_compact::init_counters() {
  count_array[0] = number_bit(get_nth_word(0));
  for (unsigned i = 1 ; i < wsize(); i++)
    {
      count_array[i] = count_array[i-1] + number_bit(get_nth_word(i));
    }
}

void Ctable_fast::setup(unsigned n) {
  Btable::setup(n);
  count_array = new unsigned[bsize()];
  //  cerr << "Ctable_fast cree" << endl;
}

void Ctable_fast::init_counters() {
  count_array[0] = (is_set_bit(0))? 1 : 0;    
  for (unsigned i = 1 ; i < bsize() ; i++)
    {
      count_array[i] = (is_set_bit(i))? 
	count_array[i-1] + 1 : count_array[i-1];
    }
}

