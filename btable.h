#ifndef btable_h
#define btable_h
#include<iostream>

#define WORDSIZEMOINS1 31
#define WORDSIZE  32
#define WORDSIZE2  5

/* Counts the number of 1 in a 32 bits unsigned */

inline int number_bit(unsigned  a)
{
  const unsigned mask1 = (unsigned(0x55555555));
  const unsigned mask2 = (unsigned(0x33333333));

  a = (a&mask1) + ((a>>1)&mask1);
  a = (a&mask2) + ((a>>2)&mask2);

  unsigned b = (a&0xFFFF)+(a>>16);
  b = (b&0x0F0F)+((b>>4)&0x0F0F);
  b = (b&0xFF)+(b>>8);
  return int(b);
}

/* Definitions and inline methods for bit-tables */

//-------------------------------------------------------------------------
//
//  La classe Btable
//
//-------------------------------------------------------------------------

class Btable {
public:
  Btable() {};
  Btable(unsigned n) {setup(n);}
  unsigned bsize() const {return bit_size;}
  inline unsigned wsize() const {return word_size;}
  void setup(unsigned n);
  void display(unsigned n = 0) const;
  void show_bits();
  inline void unset_bit(unsigned);
  inline void set_bit(unsigned);
  inline int is_set_bit(unsigned) const;
  ~Btable();
  void delete_words();

private:
  unsigned* words;

  unsigned word_size;
  unsigned bit_size; 
  inline int get_bit_mask(long n) const { 
    return ((int)1) << (n & WORDSIZEMOINS1); }

protected:
  unsigned get_word_of(long x) const { 
    return words[x >> WORDSIZE2];} 
  inline int get_bit_mask2(long n) const { 
    return ((int)2) << (n & WORDSIZEMOINS1); }
  inline long get_word_index(long x) const { 
    return x >> WORDSIZE2;}
  inline long number_bit_at_right(unsigned x) const {
    return number_bit(get_word_of(x) & ~(get_bit_mask2(x)-1));}

  inline unsigned get_nth_word(long n)const { 
    return words[n];}
  void fill();
};



class Ctable_fast : public Btable
{
public:
  Ctable_fast() {};
  void setup(unsigned sz);
  void set_counters();
  void init_counters();
  inline unsigned count(unsigned x) const { 
    return count_array[x];}
  ~Ctable_fast();

private:
  unsigned* count_array;
};


class Ctable_compact: public Btable
{
public:
  Ctable_compact() {};
  void setup(unsigned);
  void set_counters();
  void init_counters();

  inline unsigned count(unsigned x) const { 
    return count_array[get_word_index(x)]
      - number_bit_at_right(x);
    }
  inline unsigned total_count() {
    return count(bsize()-1);
  }
~Ctable_compact();
private:
  unsigned* count_array;
};



//-------------------------------------------------------------------------
//
// Les inline
//
//-------------------------------------------------------------------------

inline void Btable::unset_bit(unsigned x)
{
#ifdef DEBUG_SVB
  if ((x < 0) || (x >= bit_size))
    {
      cout << "unset_bit: overflow x = " << x << "\n";
      cout << "Taille de la table  = " << bit_size << "\n";
      exit(0);
    }
#endif
  words[get_word_index(x)] &= ~get_bit_mask(x);
}

inline void Btable::set_bit(unsigned x)
{
#ifdef DEBUG_SVB
  if ((x < 0) || (x >= bit_size))
    {
      cout << "set_bit: overflow x = " << x << "\n";
      cout << "Taille de la table  = " << bit_size << "\n";
      exit(0);
    }
#endif
  words[get_word_index(x)] |= get_bit_mask(x);
}

inline int Btable::is_set_bit(unsigned x) const
{
#ifdef DEBUG_SVB
  if (x >= bit_size)
    {
      cout << "bit: overflox x = " << x << "\n";
      cout << "Taille de la table  = " << bit_size << "\n";
      exit(0);
    }
#endif
  return words[get_word_index(x)] & get_bit_mask(x);
}

#endif
