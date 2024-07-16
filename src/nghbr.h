#ifndef NGHBR_H
#define NGHBR_H

#include "solution.h"

int best_k (int);

int is_feasible (Bin*, int, int*);

int is_feasible (Bin*, Bin*, int, int, int, int, int**);

int is_better (Bin*, Bin*, int, int, int);

int is_better (Bin*, Bin*, int, int, int, int);

int reinsertion (Solution&, int, int*, int**);

int swap (Solution&, int, int*, int**);

#endif