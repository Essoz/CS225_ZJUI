#ifndef FIBHEAP_H
#define FIBHEAP_H
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>

#include "../ex1/relation.h"
#include "hashing/central_hash.h"
using namespace std;

class FibNode;

class FibHeap
{
    friend class CentralIO;
    public:
        FibHeap();  // this operation builds the heap
        /* You should add other functions to make the structure as Fibonacci heap  */
        /* It is part of computing assignment, so we would not provide the basic implementation for you */
        void Insert(FibNode* fib_node);
        FibNode* Minimum();
        FibNode* ExtractMin();
        void DecreaseKey(FibNode* handle, int new_key);
        void Delete(FibNode* handle);
        void Consolidate();
        void FindMin();
        void PrintTree();
        FibNode* HeapLink(FibNode* heap1, FibNode* heap2);
        /* The following is required for this assignment */
        /* It is not complete, you should design the API by yourself */
        // void Change_Key(x, k);
        // void Prune(r);
        void Cut(FibNode* handle);
        static FibHeap* Union(FibHeap* heap1, FibHeap* heap2);
        int GetNum();
    private:
        void _PrintTree(FibNode* node);
        // void debug_PrintTree(FibNode* node);
        FibNode* min_ptr;
        // vector<FibNode*> fiblist;
        int numitems;
};

class FibNode{
    friend class FibHeap;
    public:
        FibNode(registration n_registration);
        FibNode* parent;
        FibNode* child;
        FibNode* left;
        FibNode* right;
        bool mark;
        int key;
        int degree;
        
        int64_t getRegID()      { return reg_id;}
    private:
        int64_t reg_id;
};

#endif /* fibheap_h */
