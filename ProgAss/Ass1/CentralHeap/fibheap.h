#ifndef FIBHEAP_H
#define FIBHEAP_H
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>

#include "central_patient_f.h"
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
        void PatientCreate(vector<string>&infolist);
        //
        /* <=== Helper Functions for DDL management ===> */
        /* to be done list
         * DDL check
         * DDL assign (executed before normal assignments)
         */

        /* <=== Helper Function for HashTable Management ===> */
        void hash_table_insert(FibNode* node);
        FibNode* hash_table_remove(int id);
        FibNode* hash_table_find(int id);
        FibNode* hash_table_swap(FibNode* node);   // helper function for updating nodes (only for priority
        bool hash_intable_check(int id);
        
        void withdraw_table_insert(FibNode* node);
        FibNode* withdraw_table_remove(int id);
        
        void highrisk_table_insert(FibNode* node);
        FibNode* highrisk_table_remove(int id);
        FibNode* highrisk_table_find(int id);
        bool highrisk_intable_check(int id);
        FibHeap* highrisk_queue;    // table generated within highrisk_queue is not used

        void assigned_table_insert(FibNode* node);
        FibNode* assigned_table_remove(int id);
        FibNode* assigned_table_find(int id);
        bool assigned_intable_check(int id);

        void ddl_insert(FibNode* node);
        bool ddl_incheck(FibNode* node);
        FibNode* ddl_delete(FibNode* node);
        
    private:
        void _PrintTree(FibNode* node);
        FibNode* min_ptr;
        vector<FibNode*> fiblist;
        int numitems;
        Hash_Chaining* withdraw_table;
        Hash_Chaining* processin_table;
        Hash_Chaining* highrisk_table;
        Hash_Chaining* assigned_table;
        vector<FibNode*> ddl_queue;
};

class FibNode: public Patient{
    friend class FibHeap;
    public:
        FibNode(vector<string>&infolist);
        void PatientCreate(vector<string>&infolist);
        FibNode* parent;
        FibNode* child;
        FibNode* left;
        FibNode* right;
        bool mark;
        int key;
        int degree;
};

#endif /* fibheap_h */
