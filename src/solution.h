#ifndef SOLUTION_H
#define SOLUTION_H

#include "bin.h"

class Solution {
    public:
        int n;    // number of bins
        int obj;  // objective value of the solution
        Bin** S;
        
        Solution (int bins);

        Bin* operator [] (int bin);
        void copy (Solution& sol);

        void new_bin (int type);
        void erase_bin (int bin);

        void alloc (int bin, int type, int item, int size);
        void dealloc (int bin, int type, int item, int size);
        void reinsert (int bin1, int bin2, int type1, int type2, int item, int size);
        void swap (int bin1, int bin2, int type1, int type2, int item1, int item2, int size1, int size2);

        void describe ();
};

#endif