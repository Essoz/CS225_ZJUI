#ifndef CENTRAL_HASH_H
#define CENTRAL_HASH_H
// #include "FibNode<int>.h"
#include <iostream>	
#include <math.h>
#include <cstdlib>
#include <map>
#include <vector>

// #include "../../FibNode<int>.h"
#include "../fibheap.h"
using namespace std;

/*
 *  File: hash.h
 *
 *  Writter: Yuxuan Jiang
 *
 *  Description:
 *  This header file contains the class of "hash", which is the hash table defined
 *  in the Local_Queue.h. It is modified from the HW5, ex2.
 *  We apply hashing with chaining here.
 */

class Hash_Chaining
{
    friend class Queue;
public:
    Hash_Chaining(int length);
    int calculate_hashvalue(int id, int size);
    void insertion(FibNode<int>* item);
    void deletion(FibNode<int>* item);
    // Return the pointer of the FibNode<int> instance in the hash table:
    FibNode<int>* retrieval(int id);

private:
    std::vector<FibNode<int>*>** hashtable;  // The hashtable
    int hash_numitems;                  // length of hashtable
    int hash_maxsize;                   // defines the size of the hashtable
};

#endif /* Local_hash_h */
