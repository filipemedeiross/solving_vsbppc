#ifndef BIN_H
#define BIN_H

#include <list>

class Bin {
    public:
        int k;  // bin type
        int s;  // capacity used
        int n;  // number of items in the bin
        std::list <int> items;

        Bin (int bin_type);

        void add (int item, int size, int bin_type);
        void remove (int item, int size, int bin_type);
        int is_feasible(int* conflicts);

        void describe ();
};

#endif