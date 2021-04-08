#ifndef _FIBHEAP_H
#define _FIBHEAP_H
/* Put your declaration here */
#include "../Patient.h"
#include "hashing/central_hash.h"
#include <string>
#include <vector>

template<class T> class FibNode;

template<class T> class FibHeap{
    public:
        friend class CentralIO;
        FibHeap();  // this operation builds the heap
        /* You should add other functions to make the structure as Fibonacci heap  */
        /* It is part of computing assignment, so we would not provide the basic implementation for you */
        void Insert(FibNode<T>* fib_node);
        FibNode<T>* Minimum();
        FibNode<T>* ExtractMin();
        void DecreaseKey(FibNode<T>* handle, T new_key);
        void Delete(FibNode<T>* handle);
        void Consolidate();
        void FindMin();
        void PrintTree();
        FibNode<T>* HeapLink(FibNode<T>* heap1, FibNode<T>* heap2);
        /* The following is required for this assignment */
        /* It is not complete, you should design the API by yourself */
        // void Change_Key(x, k);
        // void Prune(r);
        void Cut(FibNode<T>* handle);
        static FibHeap<T>* Union(FibHeap<T>* heap1, FibHeap<T>* heap2);
        int GetNum();
        void PatientCreate(vector<string>&infolist);
        //
        /* <=== Helper Functions for DDL management ===> */
        /* to be done list
         * DDL check
         * DDL assign (executed before normal assignments)
         */

        /* <=== Helper Function for HashTable Management ===> */
        void hash_table_insert(FibNode<T>* node);
        FibNode<T>* hash_table_remove(int id);
        FibNode<T>* hash_table_find(int id);
        FibNode<T>* hash_table_swap(FibNode<T>* node);   // helper function for updating nodes (only for priority
        bool hash_intable_check(int id);
        
        void withdraw_table_insert(FibNode<T>* node);
        FibNode<T>* withdraw_table_remove(int id);
        
        void highrisk_table_insert(FibNode<T>* node);
        FibNode<T>* highrisk_table_remove(int id);
        FibNode<T>* highrisk_table_find(int id);
        bool highrisk_intable_check(int id);
        FibHeap<T> highrisk_queue;

        void assigned_table_insert(FibNode<T>* node);
        FibNode<T>* assigned_table_remove(int id);
        FibNode<T>* assigned_table_find(int id);
        bool assigned_intable_check(int id);

        void ddl_insert(FibNode<T>* node);
        bool ddl_incheck(FibNode<T>* node);
        FibNode<T>* ddl_delete(FibNode<T>* node);
        
    private:
        void _PrintTree(FibNode<T>* node);
        FibNode<T>* min_ptr;
        int numitems;
        Hash_Chaining withdraw_table;
        Hash_Chaining processin_table;
        Hash_Chaining highrisk_table;
        Hash_Chaining assigned_table;
        vector<FibNode<T>*> ddl_queue;


        
};


// build an empty heap
template<class T> FibHeap<T>::FibHeap(){
    min_ptr = NULL;
    numitems = 0;
};

template<class T> class FibNode: public Patient{
    public:
        friend class FibHeap<T>;
        FibNode(vector<string>&infolist);
        void PatientCreate(vector<string>&infolist);
        FibNode<T>* parent;
        FibNode<T>* child;
        FibNode<T>* left;
        FibNode<T>* right;
        bool mark;
        T key;
        int degree;
};

template<class T> FibNode<T>::FibNode(vector<string>&infolist){
    parent = NULL;
    child = NULL;
    left = NULL;
    right = NULL;
    degree = 0;
    mark = false;       // default marking == false
    // key = priority;
    PatientCreate(infolist);

};
#endif
