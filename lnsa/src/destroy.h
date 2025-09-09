#ifndef DESTROY_H
#define DESTROY_H

#include <vector>
#include "solution.h"

int   max_gap     (Solution&);
float prob_weight (Bin&, int);

std::vector <int>* destroy_solution (Solution&, float);

#endif