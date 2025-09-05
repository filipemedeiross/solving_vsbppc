/***********************************************************************************
 * The logic of this greedy algorithm consists of:                                 *
 * Add a item to each iteration until all the items in V are packed into the bins; *
 * Choose the unpacked item with the greedy heuristic;                             *
 * Pack the item into the corresponding bin;                                       *
 * Satisfying maximum capacity constraints and incompatibility between items.      *
 ***********************************************************************************/

#ifndef GREEDY_H
#define GREEDY_H

#include <vector>
#include "instance.h"
#include "solution.h"


typedef float   (*GreedyF      ) (int, int, Bin&, Instance&, const int*);
typedef GreedyF (*GreedyChooser) (Instance&);


extern GreedyF chooser_legacy (Instance&);


struct BestAlloc {
    int i;
    int t;
    int k;
    float cost;

    BestAlloc (                               ) : i(0), t(0), k(0), cost(0.0f) {}
    BestAlloc (int i, int t, int k, float cost) : i(i), t(t), k(k), cost(cost) {}

    void operator () (int i, int t, int k, float cost) {
        this->i = i;
        this->t = t;
        this->k = k;
        this->cost = cost;
    }
};


class Greedy {
    private:
        const int  bin_types;
        const int  max_cost ;
        const int* bin_costs;

        int*   new_type;
        float* new_cost;
        Instance&    instance;
        GreedyChooser chooser;

        void      set_news  ();
        bool      can_alloc (int, int, Bin&);
        BestAlloc find_best (Solution&, vector <int>&);

    public:
        Greedy  (Instance&, int, const int*, GreedyChooser);
        ~Greedy ();

        Solution initial_solution ();
        void     greedy_solution  (Solution&, vector <int>&);
};

#endif