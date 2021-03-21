#include "multiset.h"
#include <iostream>	
#include <math.h>
#include <cstdlib>
#include <map>
#include <vector>
using namespace std;
using std::cout;
using std::cin;
using std::hash;

/* Put your implementation here */
// Q2.1
//
// Tianyu Zhang
//
// Constructor:
template<class T> MultiSet<T>::MultiSet(T* input_set, int length)
{
    // Initalize the attributes of the multiset
    set_size = length;
    ori_set = input_set; // ????????

    // Initalize the attributes of the hashtable
    hash_maxsize = length;
    if (length < 20){
        hash_maxsize = 20;  // Default size for hashtable
    }
    hash_numitems = 0;   // The current number of pairs in hashtable
    hashtable = new pair<T, int>*[hash_maxsize];
    for (int i = 0; i < hash_maxsize; i++){
        hashtable[i] = NULL;
    }

    // Initialize the placeholder
    pair<T, int>* pt = new pair<T, int>;    // This defines the fixed placeholder pointer
    pt->first = 0;
    pt->second = 0;
    placeholder = pt;
}

// Create the needed hashtable:
template<class T> void MultiSet<T>::create_hashtable()
{
    // Loop through all the items in the multiset:
    for (int i = 0; i < set_size; i++)
    {
        T cur_number = ori_set[i];  // Get the current number
        insertion(cur_number);   // Now we can add the items into the hashtable:
    }
    return;
}

// Calculate the hashvalue:
template<class T> int MultiSet<T>::calculate_hashvalue(T item, int size)
{
    hash<T> hashfunction; // use the predefined hashfunction to get "key" values
    return hashfunction(item) % size;
}

// Insert a value:
template<class T> void MultiSet<T>::insertion(T item)
{
    int index = calculate_hashvalue(item, hash_maxsize); // Calculate the hashvalue
    int location = -1;  // used to distinguish between undefined entries (null pointer) and placeholders
    while (hashtable[index] != NULL) // We first check, if the item is already in the hashtable
    {
        if (hashtable[index] != placeholder && hashtable[index]->first == item){
            hashtable[index]->second++; // item found; increase the multiplicity by 1
            return;
        }

        if (location < 0 && hashtable[index] == placeholder){ // a placeholder object is found; i.e. if the item is not in the hashtable, this will be the place for the insertion
            location = index;
        }
        index = (index + 1) % hash_maxsize;
    }
    // after leaving the while loop we either have location < 1, i.e. we store the item at the last examined index (which contains a null pointer),
    // otherwise, if location >= 0 holds, we found a placeholder, so the item will be stored at the location of this placeholder
    if (location < 0){
        location = index;   // NULL pointer found, store there
    }
    // Create a new pair for that element
    pair<T, int>* pt = new pair<T, int>;
    pt->first = item;
    pt->second = 1;
    hashtable[location] = pt;   // store pair in the hashtable
    hash_numitems++;

    int load = 100 * hash_numitems / hash_maxsize;
    if (load >= 75)             // max load factor is exceeded; double the size
    {
        int hash_newsize = 2 * hash_numitems;
        rehash(hash_newsize);
    }
    return;
}

// Delete a value:
template<class T> void MultiSet<T>::deletion(T item)
{
    int index = calculate_hashvalue(item, hash_maxsize); // Calculate the hashvalue
    while (hashtable[index] != 0)  // same as for add we search for item in the hashtable; the search starts at the designated hash value, and stops when we find a null pointer
    {
        if (hashtable[index] != placeholder && hashtable[index]->first == item)
            // item found
        {
            hashtable[index]->second--; // Decrease the multiplicity by 1
            if (hashtable[index]->second <= 0)
            {
                // We need to delete that pair since the multiplicity is 0 or less
                int nextindex = (index + 1) % hash_maxsize;
                /* check the next entry, if it is a null pointer; if yes, we can overwrite item by a null pointer; otherwise we use a placeholder, i.e. the pointer pt_nil */
                if (hashtable[nextindex] == NULL){
                    hashtable[index] = NULL;
                }
                else{
                    hashtable[index] = placeholder;
                }
                hash_numitems--;

                int load = 100 * hash_numitems / hash_maxsize;
                if (load <= 25)
                    // if the min load factor is undershot, we shrink the hashtable, but the size shall always be >= 20
                {
                    int newsize = hash_numitems;
                    if (newsize < 20)
                        newsize = 20;
                    rehash(newsize);
                }
            }
            return;
        }
        index = (index + 1) % hash_maxsize;
    }
    cout << item << " is not in the hashtable.\n";
    return;
}

// Retrieve a value pair:
template<class T> std::pair<T, int>* MultiSet<T>::retrieval(T item)
{
    int index = calculate_hashvalue(item, hash_maxsize); // Calculate the hashvalue
    while (hashtable[index] != NULL) // again we search for item starting from the index position until we find a null pointer
    {
        if (hashtable[index] != placeholder && hashtable[index]->first == item){
            return hashtable[index];  // item was found
        }
        index = (index + 1) % hash_maxsize;
    }

    cout << item << " is not in the hashtable.\n";
    return NULL;  // a null pointer was found, so item is not in the hashtable
}

// Combine two multisets:
template<class T> std::pair<T, int>** MultiSet<T>::setunion(T* set1, T* set2, int length1, int length2)
{
    // Create a new array with the total length:
    T* newarray = new T[length1 + length2];
    // Add all the values into that array:
    for (int i = 0; i < length1; i++)
    {
        newarray[i] = set1[i];
    }

    for (int i = 0; i < length2; i++)
    {
        newarray[length1 + i] = set2[i];
    }

    // Create a new hashtable:
    MultiSet<T>* Union = new MultiSet<T>(newarray, length1 + length2); // ????????
    Union->create_hashtable();
    Union->display();
    return Union->hashtable;
}

// Intersect two multisets:
template<class T> std::pair<T, int>** MultiSet<T>::intersection(T* set1, T* set2, int length1, int length2)
{
    // Convert the two sets into hashtables:
    MultiSet<T>* multiset1 = new MultiSet<T>(set1, length1);
    MultiSet<T>* multiset2 = new MultiSet<T>(set2, length2);
    multiset1->create_hashtable();
    multiset2->create_hashtable();

    // loop through the first hashtable:
    for (int i = 0; i < multiset1->hash_maxsize; i++)
    {
        if (multiset1->hashtable[i] != NULL && multiset1->hashtable[i] != multiset1->placeholder)
            // there is a valid pair, then search for the second hashtable
        {
            int check = 0;
            for (int j = 0; j < multiset2->hash_maxsize; j++)
            {
                // std::cout << "check" << std::endl;
                if (multiset2->hashtable[j] != NULL && multiset2->hashtable[j] != multiset2->placeholder 
                    && multiset1->hashtable[i]->first == multiset2->hashtable[j]->first)
                    // Match pair found, update the first hashtable
                {
                    if (multiset1->hashtable[i]->second > multiset2->hashtable[j]->second)
                    {
                        multiset1->hashtable[i]->second = multiset2->hashtable[j]->second;
                    }
                    check = 1;
                    break;
                }
                // std::cout << "???" << std::endl;
            }
            // No match pair found, clear that pair:
            if (0 == check)
            {
                int nextindex = (i + 1) % multiset1->hash_maxsize;
                /* check the next entry, if it is a null pointer; if yes, we can overwrite item by a null pointer; otherwise we use a placeholder, i.e. the pointer pt_nil */
                if (multiset1->hashtable[nextindex] == NULL){
                    multiset1->hashtable[i] = NULL;
                }
                else{
                    multiset1->hashtable[i] = multiset1->placeholder;
                }
                multiset1->hash_numitems--;
            }
        }
        // std::cout << "zz" << std::endl;
    }
    multiset1->display();
    return multiset1->hashtable;
}

// Difference two multisets:
template<class T> std::pair<T, int>** MultiSet<T>::difference(T* set1, T* set2, int length1, int length2)
{
    // Convert the two sets into hashtables:
    MultiSet<T>* multiset1 = new MultiSet<T>(set1, length1);
    MultiSet<T>* multiset2 = new MultiSet<T>(set2, length2);
    multiset1->create_hashtable();
    multiset2->create_hashtable();

    // loop through the first hashtable:
    for (int i = 0; i < multiset1->hash_maxsize; i++)
    {
        if (multiset1->hashtable[i] != NULL && multiset1->hashtable[i] != multiset1->placeholder)
            // there is a valid pair, then search for the second hashtable
        {
            for (int j = 0; j < multiset2->hash_maxsize; j++)
            {
                if (multiset2->hashtable[j] != NULL && multiset2->hashtable[j] != multiset2->placeholder 
                    && multiset1->hashtable[i]->first == multiset2->hashtable[j]->first)
                    // Match pair found, update the first hashtable
                {
                    multiset1->hashtable[i]->second = multiset1->hashtable[i]->second - multiset2->hashtable[j]->second;
                    break;
                }
            }
            // If the multiplicity is not positive after updating, clear that pair:
            if (0 >= multiset1->hashtable[i]->second)
            {
                int nextindex = (i + 1) % multiset1->hash_maxsize;
                /* check the next entry, if it is a null pointer; if yes, we can overwrite item by a null pointer; otherwise we use a placeholder, i.e. the pointer pt_nil */
                if (multiset1->hashtable[nextindex] == NULL){
                    multiset1->hashtable[i] = NULL;
                }
                else{
                    multiset1->hashtable[i] = multiset1->placeholder;
                }
                multiset1->hash_numitems--;
            }
        }
    }
    multiset1->display();
    return multiset1->hashtable;
}

// Rehash:
template<class T> void MultiSet<T>::rehash(int newsize)
{
    if (newsize < 20){
        newsize = 20;
    }
    int newnum = 0;
    pair<T, int>** newarray = new pair<T, int>*[newsize];   // allocate space for a new hashtable of the given new size
    for (int i = 0; i < newsize; i++){
        newarray[i] = NULL;   // initialise the new hashtable with only null pointers
    }

    for (int i = 0; i < hash_maxsize; i++)  // we need to copy all existing entries to the new hash table
    {
        if (hashtable[i] != NULL && hashtable[i] != placeholder)
        {
            T item = hashtable[i]->first;
            int index = calculate_hashvalue(item, newsize); // recompute the hashvalue
            while (newarray[index] != NULL){  // find the first free place, where the entry can be stored in the new hashtable
                index = (index + 1) % newsize;
            }
            newarray[index] = hashtable[i];  // do the actual copying
            ++ newnum;
        }
    }
    hash_numitems = newnum;   // change the number of stored elements
    hashtable = newarray;   // make the new hashtable the one of the hashset object
    hash_maxsize = newsize;   // update the size
    return;
}

// Only for test purposes
template<class T> void MultiSet<T>::display(void)
{
    // cout << "The size of the hashtable is: " << hash_maxsize << "\n";
    cout << "The number of elements in the hashtable is: " << hash_numitems << endl;
    for (int i = 0; i < hash_maxsize; i++)
    {
        if (hashtable[i] != NULL && hashtable[i] != placeholder){
            cout << "The entry " << i + 1 << " contains the element " << hashtable[i]->first << "." << endl;
            cout << "The multiplicity of this element is " << hashtable[i]->second << endl;
        }
    }
    return;
}

// Q2.2
//
// Tianyu Zhang
//
// Constructor:
