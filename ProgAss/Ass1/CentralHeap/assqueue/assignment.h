#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H
#include "../alist.h"
#include "../alist.cpp"
#include "../fibheap.h"
#include "../fibheap_f.h"
#include "assignment_f.h"
#include <vector>

template<class T> class Assignment{
    public:
        bool Assign(FibNode<T>* reg);

    private:
        vector<FibNode<T>*> ass_queue;
        maxnum; // number of locations 
        currentnum; // current number of available locations //TODO do I really need this?
    

};

/* Locations for medical treatment */
class Location{
    public:
    
    private:

};

/* Local registries */
class Registry{
    public:
    
    private:
};


#endif