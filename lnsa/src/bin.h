#ifndef BIN_H
#define BIN_H

#include <list>

class Bin {
    public:
        int k;  // bin type
        int s;  // capacity used
        int n;  // number of items in the bin
        std::list <int> items;

        Bin (int);
        ~Bin ();

        int  is_feasible (int*);
        int  is_feasible (int*, int);

        void add    (int, int, int);
        void remove (int, int, int);

        void describe (int);
};

#endif