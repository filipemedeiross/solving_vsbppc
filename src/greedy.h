#ifndef GREEDY_H
#define GREEDY_H

#include <vector>
#include <random>
#include "instance.h"
#include "solution.h"

using namespace std;

/***********************************************************************************
 * The logic of this greedy algorithm consists of:                                 *
 * Add a item to each iteration until all the items in V are packed into the bins; *
 * Choose the unpacked item with the minimum per unit cost increase;               *
 * Pack the item into the corresponding bin;                                       *
 * Satisfying maximum capacity constraints and incompatibility between items.      *
 ***********************************************************************************/
class Greedy {
    private:
        int hc;

        void  set_news();
        void  set_hc  ();

    public:
        int*   new_type;
        float* new_cost;
        Instance* instance;

        Greedy (Instance*);
        ~Greedy ();

        Solution* initial_solution ();

        float greedy1 (int, int, Bin&);
        float greedy2 (int, int, Bin&);

        void greedy_solution (Solution&, vector <int>&, int);
        void update_best (int&, int&, int&, float&, int, int, int, float);
        void find_best   (Solution&, vector <int>&, int&, int&, int&,
                          float, float (Greedy::*)(int, int, Bin&));
};

#endif