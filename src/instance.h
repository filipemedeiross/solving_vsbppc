#ifndef INSTANCE_H
#define INSTANCE_H

class Instance {
    public:
        int   n;  // number of items
        int*  v;  // size of items
        int** G;  // conflict graph

        Instance (char* filename);

        int  operator [] (int);
        void describe ();
};

#endif