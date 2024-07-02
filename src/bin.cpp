#include <iostream>
#include "bin.h"

using namespace std;

Bin::Bin (int bin_type) {
    k = bin_type;
    s = 0;
    n = 0;
}

void Bin::add (int item, int size, int bin_type) {
    s += size;
    n++;
    items.push_back(item);

    if (k != bin_type)
        k = bin_type;
}

void Bin::remove (int item, int size, int bin_type) {
    std::list<int>::iterator pos;
    
    pos = items.begin();
    while (*pos != item)
        pos++;
    
    s -= size;
    n--;
    items.erase(pos);

    if (k != bin_type)
        k = bin_type;
}

int Bin::is_feasible(int* conflicts) {
    for (int item : items) 
        if (conflicts[item])
            return 0;

    return 1;
}

void Bin::describe () {
    cout << "(" << k << " - " << s << ") [ ";
    
    for (int item : items)
        cout << item << " ";
        
    cout << "]" << endl;
}