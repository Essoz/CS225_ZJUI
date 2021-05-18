#ifndef Local_hash_h
#define Local_hash_h
#include "Local_Queue.h"
#include <iostream>	
#include <math.h>
#include <cstdlib>
#include <map>
#include <vector>
using namespace std;

/*
 *  File: hash.h
 *
 *  Writter: Tianyu Zhang
 *
 *  Description:
 *  This header file contains the class of "hash", which is the hash table defined
 *  in the Local_Queue.h. It is modified from the HW5, ex2.
 *  We apply hashing with chaining here.
 */
class FibNode;
class FibHeap;

class Hash_Chaining
{
    friend class Queue;
public:
    Hash_Chaining(int length);
    int calculate_hashvalue(int id, int size);
    void insertion(FibNode* item);
    //void deletion(FibNode* item);
    // Return the pointer of the FibNode instance in the hash table:
    FibNode* retrieval(int id);

private:
    std::vector<vector<FibNode*>*>* hashtable;      // The hashtable
    int hash_numitems;                  // length of hashtable
    int hash_maxsize;                   // defines the size of the hashtable
};

#endif /* Local_hash_h */
