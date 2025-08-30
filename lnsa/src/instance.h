#ifndef INSTANCE_H
#define INSTANCE_H

class Instance {
    int   n;  // number of items
    int*  v;  // size of items
    int** G;  // conflict graph

    public:
        int   s;  // minimum item size
        float d;  // conflict graph density

        Instance  (const char* filename);
        ~Instance ();

        int size ();
        int  operator [] (int);
        int* operator () (int);
        int  operator () (int, int);

        void describe ();
};

#endif