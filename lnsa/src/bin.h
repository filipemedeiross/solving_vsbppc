#ifndef BIN_H
#define BIN_H

#include <list>

class Bin {
    std::list <int> items;

    public:
        int k;  // bin type
        int s;  // capacity used
        int n;  // number of items in the bin

        Bin (int);
        Bin (const Bin&);

        Bin& operator= (const Bin&);

        int is_feasible (int*);
        int is_feasible (int*, int);
        int is_feasible (int , int, int*);
        int is_feasible (int , int, int , int*, int);

        void add    (int, int, int);
        void remove (int, int, int);

        int has_item(int);
        const std::list <int>& get_items();

        void describe (int);
};

#endif