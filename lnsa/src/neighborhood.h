#ifndef NEIGHBORHOOD
#define NEIGHBORHOOD

#include "instance.h"
#include "solution.h"

int best_k (int);

int is_feasible (Bin*,       int, int,           Instance&);
int is_feasible (Bin*, Bin*, int, int, int, int, Instance&);

int is_better (Bin*, Bin*, int, int, int);
int is_better (Bin*, Bin*, int, int, int, int);

int reinsertion (Solution&, Instance&);
int swap        (Solution&, Instance&);
int search      (Solution&, Instance&);

#endif