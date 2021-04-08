#ifndef CENTRAL_HASH_H
#define CENTRAL_HASH_H
// #include "central_hash.cpp"
#include "../fibheap.h"
#include "../fibheap_f.h"
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

class Hash_Chaining
{
public:
    Hash_Chaining(int length);
    int calculate_hashvalue(int id, int size);
    void insertion(FibNode<int>* node);
    void deletion(int id);
    // Return the pointer of the patient instance in the hash table:
    FibNode<int>* retrieval(int id);
    int get_numitems();
private:
    std::vector<vector<FibNode<int>*>*>* hashtable;      // The hashtable
    int hash_numitems;                  // length of hashtable
    int hash_maxsize;                   // defines the size of the hashtable
};

#endif /* Local_hash_h */
