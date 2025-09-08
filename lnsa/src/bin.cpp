#include <iostream>
#include <algorithm>
#include "bin.h"

using namespace std;

Bin::Bin (int type) :
    k (type),
    s (0)   ,
    n (0)
{}

Bin::Bin (const Bin& other) :
    k (other.k),
    s (other.s),
    n (other.n),
    items (other.items)
{}

Bin& Bin::operator= (const Bin& other) {
    if (this != &other) {
        k = other.k;
        s = other.s;
        n = other.n;
        items = other.items;
    }

    return *this;
}

int Bin::is_feasible(int* conflicts) {
    for (int item : items) 
        if (conflicts[item])
            return 0;

    return 1;
}

int Bin::is_feasible(int* conflicts, int rm) {
    for (int item : items)
        if (conflicts[item] && item != rm)
            return 0;

    return 1;
}

int Bin::is_feasible(int v, int max, int* conflicts) {
    return s + v <= max && is_feasible(conflicts);
}

int Bin::is_feasible(int v1, int v2, int max, int* conflicts, int rm) {
    return s - v1 + v2 <= max && is_feasible(conflicts, rm);
}

void Bin::add (int item, int size, int type) {
    n++;
    s += size;

    items.push_back(item);

    k = type;
}

void Bin::remove (int item, int size, int type) {
    auto pos = find(
        items.begin(),
        items.end()  ,
        item
    );

    n--;
    s -= size;

    items.erase(pos);

    k = type;
}

int Bin::has_item(int item) {
    return find(items.begin(), items.end(), item) != items.end();
}

const std::list <int>& Bin::get_items() {
    return items;
}

void Bin::describe (int idx) {
    cout << "Bin " << idx << \
            " ( "  << k   << \
            " - "  << s   << \
            " ) [ ";

    for (int item : items)
        cout << item << " ";

    cout << "]" << endl;
}
