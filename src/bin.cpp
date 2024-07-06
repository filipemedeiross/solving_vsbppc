#include <iostream>
#include <algorithm>
#include "bin.h"

using namespace std;

Bin::Bin (int type) : k(type), s(0), n(0) {}

int Bin::is_feasible(int* conflicts) {
    for (int item : items) 
        if (conflicts[item])
            return 0;

    return 1;
}

void Bin::add (int item, int size, int type) {
    s += size;
    n++;
    items.push_back(item);

    k = type;
}

void Bin::remove (int item, int size, int type) {
    auto pos = find(items.begin(),
                    items.end()  ,
                    item);

    s -= size;
    n--;
    items.erase(pos);

    k = type;
}

void Bin::describe () {
    cout << "(" << k << " - " << s << ") [ ";

    for (int item : items)
        cout << item << " ";

    cout << "]" << endl;
}