#ifndef hash_h
#define hash_h
#include "Patient.h"
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
    Hash_Chaining(Patient** input_set, int length);
    int calculate_hashvalue(int id, int size);
    void insertion(Patient* item);
    void deletion(Patient* item);
    bool check(Patient* item);

private:
    std::vector<Patient*>** hashtable;  // The hashtable
    int hash_numitems;                  // length of hashtable
    int hash_maxsize;                   // defines the size of the hashtable
};

#endif /* hash_h */
