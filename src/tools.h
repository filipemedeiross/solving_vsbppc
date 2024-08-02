#ifndef TOOLS_H
#define TOOLS_H

#include <vector>
#include "solution.h"

using namespace std;

int   max_gap (Solution&);
float prob_weight (Bin&, int);

vector <int>* destroy_solution (Solution&, float);

#endif