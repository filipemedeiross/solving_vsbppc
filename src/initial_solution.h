#ifndef INITIAL_SOLUTION_H
#define INITIAL_SOLUTION_H

#include <vector>
#include "instance.h"
#include "solution.h"

using namespace std;

/***********************************************************************************
 * The logic of this greedy algorithm consists of:                                 *
 * add a item to each iteration until all the items in V are packed into the bins; *
 * choose the unpacked item with the minimum per unit cost increase;               *
 * pack the item into the corresponding bin;                                       *
 * satisfying maximum capacity constraints and incompatibility between items.      *
 ***********************************************************************************/
class Greedy {
    public:
        Instance* instance;
        int* new_bins_type;
        float* new_bins_cost;

        Greedy (Instance*);

        Solution* initial_solution ();

        void update_best (int&, int&, int&, float&, int, int, int, float);
        void find_best (Solution&, vector <int>&, int&, int&, int&, float);
        void greedy_solution (Solution&, vector <int>&, int);
};

#endif