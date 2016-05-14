#ifndef _vector_h
#define _vector_h
#include<iostream>
#include<limits.h>
using namespace std;
#define DEBUG_VC               0
#define DEBUG_OUT_OF_RANGE     0

template<class T> class Vector
{
protected:
  T* elts;
  int dim;
  inline int best_index(int,int);
public:
  Vector() {dim = 0; }
  Vector(int n) {dim = n; elts = new T[dim]; }
  Vector(const Vector &v) { 
    dim  = v.dim;
    elts = new T[dim];
    for (int j = 0; j < dim; j++) elts[j] = v.elts[j]; }
  Vector<T> operator + (Vector<T> &v);
  Vector<T> operator - (Vector<T> &v);
  Vector<T>& operator = (const Vector<T> &v) {
    if (dim != v.dim)
      {
	cerr << "Vectors of different sizes in (Vector) = (Vector)\n";
	exit(0);	
      }
    for (int j = 0; j < dim; j++) elts[j] = v[j];
    return *this; }
  void set_dim(int n) { dim = n; elts = new T[dim]; }

  void insertion_sort0(int, int);

  void free();
  ~Vector() { 
#if DEBUG_VC
    cerr << "~Vector(): destruction of Vector.elts\n";
#endif
    if (dim)
      delete[] elts; 
  }
  int get_dim() const { return dim; }
  T& operator[] (int n)  const { 
#if DEBUG_OUT_OF_RANGE
    if ((n < 0) || (n > dim-1))
      {
	cerr << "Vector: index n = " << n << " is invalid \n";
	exit(0);
      }
#endif
    return elts[n]; 
  }
  void set_elts_to(T);
  void display(int upto, int w) const;
  void display_with_sum(int w = 2) const;
  inline void swap(int, int);
  void insertion_sort();
  int partition_wrt(int,int,int);
  void quicksort();
  int index_of_first_bigger_than(T v);
  void add_to(T x) {elts[dim++] = x;} 
};

template<class T> void Vector<T>::display(int upto, int w) const
{
  cerr << "Dimension du Vector " << dim << "\n";
  if (upto < 0) {
    return;
  }
  if (!upto)
    upto = dim;
  for (int i = 0; i < min(upto,dim); i++ )
  {
    if (elts[i] != INT_MAX) {
      cerr.width(w);
      cerr << elts[i];
    }
    else {
      cerr.width(w);
      cerr << "INFTY";
    }
  }
  cerr << "\n";
  cerr.flush();
}

template<class T> void Vector<T>::display_with_sum(int w) const
{
  for (int i = 0; i < dim; i++ )
  {
    cerr << elts[i];
    for (int j = 0; j < w; j++) cerr << " ";  // FIXME!
  }
  T sum = (T)0;
  for (int j = 0; j < dim; j++) sum += elts[j];
  cerr << "[sum = " << sum << "]"; 
  cerr << "\n";
  cerr.flush();
}

template<class T> void Vector<T>::swap(int i, int j)
{
  T v;

  v = elts[i];
  elts[i] = elts[j];
  elts[j] = v;
}

template<class T> void Vector<T>::insertion_sort0(int start, int end)
{
  int j;
  T v;

  for (int i = start; i < end; i++)
    {
      j = i;
      v = elts[j+1];
      while ((j >= start) && ( v < elts[j]))
	{
	  elts[j+1] = elts[j];
	  j--;
	}
      elts[j+1] = v;
    }
}

template<class T> void Vector<T>::insertion_sort()
{
  insertion_sort0(0, dim-1);
}

template<class T> int Vector<T>::partition_wrt(int k,int i,int j)
{
  T v = elts[k];

  while (i <= j)
    {
      if (elts[i] <= v) 
	{
	  i++; 
	  continue;
	} 
      if (elts[j] >= v)
	{ 
	  j--;
	  continue;
	}

      swap(i,j);
      i++; j--;
    }

  if (k < i) 
    {
      swap(k, j);
      return j;
    }
  
  swap(k, i);	
  return i;
}

// return the best index choice between start, end and (start+end)/2
template<class T> int Vector<T>::best_index(int start, int end)
{
  int middle = (start + end)/2;

  if (elts[start] > elts[middle])
    swap(start, middle);

  if (elts[start] > elts[end])
    swap(start, end);

  if (elts[middle]> elts[end])
    swap(middle, end);

  return middle;
}

// non-recursive quicksort using insertion sort when lenght <= 8
template<class T> void Vector<T>::quicksort()
{
  int start = 0;
  int end = dim - 1;
  int k = 0;
  int stack[60];
  int top = 2;
  
  do
    {
      if (end-start <= 8)
	{
	  insertion_sort0(start, end);
	  end = stack[--top];
	  start = stack[--top];
	}
      else
	{
	  k = best_index(start, end);
	  // k = start;
	  //	  cerr << "Before partition start , end = " 
	  //     <<  start << "  " << end << endl;
	  k = partition_wrt(k, start, end);
	  //cerr << "partition renvoie k = " << k << endl; 
	  //cerr << "top = " << top << endl;
	  if ((k-start) > (end-k))
	    {
	      stack[top++] = start;
	      stack[top++] = k-1;
	      start = k+1; 
	    }
	  else
	    {
	      stack[top++] = k+1;
	      stack[top++] = end;
	      end = k-1;
	    }
	}
    }
  while (top);
}

template<class T> void Vector<T>::set_elts_to(T v)
{
  for (int j = 0; j < dim; j++)
    elts[j] = v;
}

// Renvoie le premier j tel que elts[j] > v 
template<class T> int 
Vector<T>::index_of_first_bigger_than(T v)
{
  int first = 0;
  int last  = dim;

  if (v < elts[first])
    return first; 

  while (first+1 < last)
    {
      int middle = first + (last-first)/2;  
      if (elts[middle] > v)
        last = middle;
      else first = middle;     
    }

  return last;
}

template<class T> 
Vector<T>
Vector<T>::operator + (Vector<T> &v)
{
  if (dim != v.dim)
    {
      cerr << "Vectors of different sizes in (Vector) += (Vector)\n";
      exit(0);
    }
  Vector<T> result;
  result.create(dim);
  for (int j = 0; j < dim; j++) result[j] = elts[j] + v[j];
  
  return result;
}

template<class T> 
Vector<T>
Vector<T>::operator - (Vector<T> &v)
{
  if (dim != v.dim)
    {
      cerr << "Vectors of different sizes in (Vector) += (Vector)\n";
      exit(0);
    }
  Vector<T> result;
  result.create(dim);
  for (int j = 0; j < dim; j++) result[j] = elts[j] - v[j];
  
  return result;
}

template<class T>
void
Vector<T>::free()
{
  if (dim) {
    cerr << "Vector::free() liberation de " << dim << " elements" << endl;
    delete[] elts;
    dim=0;
  }
}
#endif
