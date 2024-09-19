#ifndef INSTANCE_H
#define INSTANCE_H

class Instance {
    public:
        int   n;  // number of items
        int*  v;  // size of items
        int** G;  // conflict graph
        int   s;  // minimum item size
        float d;  // conflict graph density

        Instance (char* filename);
        ~Instance ();

        int  operator [] (int);
        void describe ();
};

#endif