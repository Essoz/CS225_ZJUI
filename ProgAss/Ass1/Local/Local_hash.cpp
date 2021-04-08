#include "Local_hash.h"
#include <iostream>	
#include <math.h>
#include <cstdlib>
#include <map>
#include <vector>
using namespace std;
using std::cout;
using std::cin;
using std::hash;

/*
 *  File: hash.cpp
 *
 *  Writter: Tianyu Zhang
 *
 *  Description: The function definition for hash.h
 */

// Constructor:
Hash_Chaining::Hash_Chaining(int length)
{
    // Initialize the attributes of the hashtable
    hash_maxsize = length;
    if (length < 20) {
        hash_maxsize = 20;  // Default size for hashtable
    }
    hash_numitems = 0;   // The current number of pairs in hashtable
    hashtable = new vector<vector<Patient*>*>(hash_maxsize);
    for (int i = 0; i < hash_maxsize; i++) {
        hashtable->at(i) = NULL;
    }
}

// Calculate the hashvalue:
int Hash_Chaining::calculate_hashvalue(int id, int size)
{
    hash<int> hashfunction; // use the predefined hashfunction to get "key" values
    return hashfunction(id) % size;
}

// Insert a value:
void Hash_Chaining::insertion(Patient* item)
{
    int index = calculate_hashvalue(item->getid(), hash_maxsize); // Calculate the hashvalue
    // If the corresponding entry is not defined, define it:
    if (hashtable->at(index) == NULL) {
        vector<Patient*>* entry = new vector<Patient*>;
        hashtable->at(index) = entry;
        hash_numitems++;
        hashtable->at(index)->push_back(item);   // Add that item into the entry
        return;
    }
    // Go through that entry to check if the item is already there:
    for (int i = 0; i < int(hashtable->at(index)->size()); i++)
    {
        if (hashtable->at(index)->at(i) == item) {
            return;
        }
    }
    hashtable->at(index)->push_back(item);   // Add that item into the entry
    return;
}
/*
// Delete a value:
void Hash_Chaining::deletion(Patient* item)
{
    int index = calculate_hashvalue(item->getid(), hash_maxsize); // Calculate the hashvalue
    // If the corresponding entry is not defined, just return:
    if (hashtable->at(index) == NULL) {
        cout << item << " is not in the hashtable." << endl;
        return;
    }
    else {
        // Loop through that vector entry:
        for (int i = 0; i < int(hashtable->at(index)->size()); i++)
        {
            if (item == hashtable->at(index)->at(i)) {
                // item found
                hashtable->at(index)->erase(hashtable->at(index)->begin() + i);
                // If now the entry is empty, undefine that entry:
                if (0 >= int(hashtable->at(index)->size())) {
                    hashtable->at(index) = NULL;
                    hash_numitems--;
                }
                return;
            }
        }
        // item not found
        cout << item << " is not in the hashtable." << endl;
        return;
    }
}
*/
// Return the pointer of the patient instance in the hash table:
Patient* Hash_Chaining::retrieval(int id)
{
    int index = calculate_hashvalue(id, hash_maxsize); // Calculate the hashvalue
    // If the corresponding entry is not defined, just return:
    if (hashtable->at(index) == NULL) {
        //cout << "The patient of id " << id << " is not in the hashtable." << endl;
        return NULL;
    }
    else {
        // Loop through that vector entry:
        for (int i = 0; i < int(hashtable->at(index)->size()); i++) {
            if (id == hashtable->at(index)->at(i)->getid()) {
                // item found
                return hashtable->at(index)->at(i);
            }
        }
        //cout << "The patient of id " << id << " is not in the hashtable." << endl;
        return NULL;
    }
}
