//
//  hashset.cpp
//  
//
//  Created by KD on 6.03.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "hashset.h"
using std::cout;
using std::cin;
using std::hash;

#define UNDEFINED -999999
#define PLACEHOLDER 999999

/* This defines a constructor */
template<class T> hashset<T>::hashset(int size)
{
    maxsize = size;
    if (size < 20){
        maxsize = 20; // default size is 20; no smaller hashtables are considered
    }
    numitems = 0; // initially, the hashtable is empty
    reprarray = new T*[maxsize];  // allocate space for the array of pointers
    // the for loop initialises all table entries to be undefined
    for (int i = 0; i < maxsize; i++)
    {
        reprarray[i] = 0;   // We use 0 (NULL) as the undefined pointer (the value of pointer is 0)
    }
    T *pt0 = new T;  // This defines the fixed placeholder pointer
    *pt0 = 0;
    pt_nil = pt0;   // The placeholder pointer is the fixed pointer to a declared "zero"
}

// template<class T> hashset<T>::~hashset(void)
// {
//     delete[] reprarray;
// }

// What you need to know for this reload is that kd changes the index again and it return the dereference value
// 这类运算符重构的调用条件是对实例直接用该符号[]
// hashset<T> instance;
// instance[i];
template<class T> T & hashset<T>::operator[](int index)
{
    if (index <= 0 || index > maxsize)
    {
        cout << "Index error: index out of range\n";
        exit(EXIT_FAILURE);
    }
    if (reprarray[index - 1] != 0 && reprarray[index - 1] != pt_nil)
        return *reprarray[index - 1];
    else
    {
        cout << "Index not used in hashtable";
        return 0;
    }
}

template<class T> void hashset<T>::add(T item)
{
    // Here, kd calls the standard library in C++
    hash<T> hashfunction; // use the predefined hashfunction to get "key" values
    int index;
    index = hashfunction(item) % maxsize; // First determine the position index in the hash table, where the new value is stored, if free.
    int location = -1;  // used to distinguish between undefined entries (null pointer) and placeholders
    while (reprarray[index] != 0) // We first check, if the item is already in the hashtable
    {
        if (reprarray[index] != pt_nil && *reprarray[index] == item)
            return;   // item found; no insertion
        // The "location" is used to find the index of first placeholder, since we do not know if the item exists after that placeholder,
        // we need to store this index first. If no item found, we use this place.
        if (location < 0 && reprarray[index] == pt_nil) // a placeholder object is found; i.e. if the item is not in the hashtable, this will be the place for the insertion
            location = index;
        index = (index + 1) % maxsize;  // Increase the index
    }
    // after leaving the while loop we either have location < 1, i.e. we store the item at the last examined index (which contains a null pointer),
    // otherwise, if location >= 0 holds, we found a placeholder, so the item will be stored at the location of this placeholder
    // No placeholder found, we store the index of the NULL pointer
    if (location < 0){
        location = index;
    }
    T *pt = new T;
    *pt = item;
    reprarray[location] = pt;   // store item in the hashtable, we store the pointer of the item
    ++ numitems;
    int load = 100 * numitems / maxsize;
    if (load >= 75)             // max load factor is exceeded; double the size
    {
        int newsize = 2 * numitems;
        rehash(newsize);
    }
    return;
}

template<class T> void hashset<T>::add_new(T item)
{
    // Here, kd calls the standard library in C++
    hash<T> hashfunction; // use the predefined hashfunction to get "key" values
    int index;
    index = hashfunction(item) % maxsize; // First determine the position index in the hash table, where the new value is stored, if free.
    int location1 = -1;  // used to distinguish between undefined entries (null pointer) and placeholders
    int location2 = -1;

    while (reprarray[index] != 0) // loop through the hash table
    {
        // array found, loop through it:
        for (int i = 0; i < 4; i++)
        {
            if (reprarray[index][i] != PLACEHOLDER && reprarray[index][i] == item){
                return;   // item found; no insertion
            }
            
            // The "location" is used to find the index of first placeholder, since we do not know if the item exists after that placeholder,
            // we need to store this index first. If no item found, we use this place.
            if (location1 < 0 && location2 < 0 && reprarray[index][i] == PLACEHOLDER){ // a placeholder object is found; i.e. if the item is not in the hashtable, this will be the place for the insertion
                location1 = index;
                location2 = i;
            }

            // Empty place found
            if (UNDEFINED == reprarray[index][i])
            {
                // No placeholder before
                if (location1 < 0 && location2 < 0)
                {
                    reprarray[index][i] = item;
                    ++ numitems;
                }
                else
                {
                    reprarray[location1][location2] = item;
                    ++ numitems;
                }
                return;
            }
        }

        // Place not found:
        index = (index + 1) % maxsize;  // Increase the index
    }

    // NULL pointer found, no array in that place:
    T* arr = new T[4];
    arr[0] = item;
    for (int i = 1; i < 4; i++)
    {
        arr[i] = UNDEFINED;
    }
    reprarray[index] = arr;
    ++ numitems;
    return;

/* Check for rehash:
    int load = 100 * numitems / maxsize;
    if (load >= 75)             // max load factor is exceeded; double the size
    {
        int newsize = 2 * numitems;
        rehash(newsize);
    }
*/
}

template<class T> void hashset<T>::remove(T item)
{
    hash<T> hashfunction;  // use again the predefined hashfunction
    int index;
    index = hashfunction(item) % maxsize;
    while (reprarray[index] != 0)  // same as for add we search for item in the hashtable; the search starts at the designated hash value, and stops when we find a null pointer
    {
        if (reprarray[index] != pt_nil && *reprarray[index] == item)
                    // item found
        {
            int nextindex = (index + 1) % maxsize;
            /* check the next entry, if it is a null pointer; if yes, we can overwrite item by a null pointer; otherwise we use a placeholder, i.e. the pointer pt_nil */
            if (reprarray[nextindex] == 0)
                reprarray[index] = 0;
            else
                reprarray[index] = pt_nil;
            --numitems;
            int load = 100 * numitems / maxsize;
            if (load <= 25)
                // if the min load factor is undershot, we shrink the hashtable, but the size shall always be >= 20
            {
                int newsize = numitems;
                if (newsize < 20)
                    newsize = 20;
                rehash(newsize);
            }
            return;
        }
        // item not found
        index = (index + 1) % maxsize;
    }
    cout << item << " is not in the hashtable.\n";
    return;
}

template<class T> bool hashset<T>::member(T item)
{
    hash<T> hashfunction;  // use the "key" function for the type T (if defined)
    int index;
    index = hashfunction(item) % maxsize;
    while (reprarray[index] != 0) // again we search for item starting from the index position until we find a null pointer
    {
        if (reprarray[index] != pt_nil && *reprarray[index] == item)
            return true;  // item was found
        index = (index + 1) % maxsize;
    }
    return false;  // a null pointer was found, so item is not in the hashtable
}

template<class T> void hashset<T>::rehash(int newsize)
{
    if (newsize < 20)
        newsize = 20;
    int newnum = 0;
    T **newarray = new T*[newsize];   // allocate space for a new hashtable of the given new size
    for (int i = 0; i < newsize; i++)
    {
        newarray[i] = 0;   // initialise the new hashtable with only null pointers
    }
    for (int i = 0; i < maxsize; i++)  // we need to copy all existing entries to the new hash table
    {
        // The current position in the old hash table is not a NULL pointer nor a placeholder
        if (reprarray[i] != 0 && reprarray[i] != pt_nil)
        {
            // get that current item
            T item = *reprarray[i];
            hash<T> hashfunction;
            int index = hashfunction(item) % newsize;
                // recompute the new hash value
            while (newarray[index] != 0)  // find the first free place, where the entry can be stored in the new hashtable
            {
                index = (index + 1) % newsize;
            }
            newarray[index] = reprarray[i];  // do the actual copying
            ++ newnum;
        }
    }
    numitems = newnum;   // change the number of stored elements
    reprarray = newarray;   // make the new hashtable the one of the hashset object
    maxsize = newsize;   // update the size
}

template<class T> void hashset<T>::display(void) // only for test purposes
{
    cout << "The size of the hashtable is: " << maxsize << "\n";
    cout << "The number of elements in the hashtable is: " << numitems << "\n";
    for (int i = 0; i < maxsize; ++i)
    {
        if (reprarray[i] == 0)
            cout << "The entry " << i + 1 << " is undefined.\n";
        else if (reprarray[i] == pt_nil)
            cout << "The entry " << i + 1 << " is free.\n";
        else
            cout << "The entry " << i + 1 << " is " << *reprarray[i] << " .\n";
    }
    return;
}
