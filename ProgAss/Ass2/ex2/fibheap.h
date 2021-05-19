#ifndef FIBHEAP_H
#define FIBHEAP_H
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>

#include "../ex1/relation.h"

using namespace std;

registration* Reg_Relation_Delete(int64_t ID);
void Reg_Relation_Insert(registration Reg);
registration* Reg_Relation_Retrieve(int64_t ID);
vector<registration*>& Reg_Relation_Retrieve_2(int8_t withdraw);
void Per_Relation_Insert(person Per);
person* Per_Relation_Delete(int64_t ID);
person* Per_Relation_Retrieve(int64_t ID);
void Tre_Relation_Insert(treatment Tre);
treatment* Tre_Relation_Delete(int64_t ID);
treatment* Tre_Relation_Retrieve(int64_t ID);
vector<treatment*>& Tre_Relation_Retrieve_2(int64_t week);

class FibNode;
class Hash_Chaining;

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

        void removeReg(registration* Reg);
        
        void hash_table_insert(FibNode* node);
        FibNode* hash_table_remove(int id);
        FibNode* hash_table_find(int id);
        FibNode* hash_table_swap(FibNode* node);   // helper function for updating nodes (only for priority
        bool hash_intable_check(int id);
    private:
        void _PrintTree(FibNode* node);
        // void debug_PrintTree(FibNode* node);
        FibNode* min_ptr;
        // vector<FibNode*> fiblist;
        int numitems;
        Hash_Chaining* processin_table;
};

class FibNode{
    friend class FibHeap;
    public:
        FibNode(registration* n_registration);
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

class Hash_Chaining
{
public:
    Hash_Chaining(int length = 20);
    int calculate_hashvalue(int id, int size);
    void insertion(FibNode* node);
    void deletion(int id);
    // Return the pointer of the patient instance in the hash table:
    FibNode* retrieval(int id);
    // Return a list containing all the patients' pointer:
    vector<FibNode*>& list_patient();
    int get_numitems();
private:
    std::vector<std::vector<FibNode*>*>* hashtable;      // The hashtable
    int hash_numitems;                  // length of hashtable
    int hash_maxsize;                   // defines the size of the hashtable
};

#endif /* fibheap_h */
