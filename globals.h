#ifndef globals_h
#define globals_h
#include"typedefs.h"
#include"data.h"
#include"f.h"
#include"arith_tools.h"
#include"sieve.h"
#include"primes.h"
#include"chrono.h"
#include"sqf.h"
#include"p2xy.h"

#define LONGINT 64
#define LONGVAL gmp

// Les donnes
extern longint x;
extern int y,z;

// Variables globales de type int
extern int x3;
extern int x4;

extern int y,z;
extern int z2;
extern int pi_x3;
extern int pi_x4;
extern int pi_y;
extern int xyy;
extern int pi_xyy;
extern int sqrt_x_y;
extern int pi_sqrt_x_y;
extern int pi_z2;
extern int sqf_list_last_range;
extern int cbrt_xy;

// Variables globales de type int64
extern int64 x_y;
extern int64 x_z;
extern int64 x2;
extern int64 FINCRIBLE1;
extern int64 FINCRIBLE2;

// Variables globales de type longval
extern longval Sy;
extern longval p2xy;
extern longval fixy;
extern longval binary_sum;
extern longval nbinary_sum;
extern longval sdyntmp1;

//Fonctions
void init_Finv();
void make_squarefree();
void un_trait();
longval& compute_fixy();
longval& ordinary_leaves();
void read_data_compute_data_aux(int, char*[]);
void print_data();
#endif

