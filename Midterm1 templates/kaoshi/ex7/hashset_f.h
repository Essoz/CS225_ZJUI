#include "hashset.h"
using std::cout;
using std::cin;
using std::hash;
/* This defines a constructor */
template<class T> hashset<T>::hashset(int size)
{
    maxsize = size;
    if (size < 20)
        maxsize = 20; // default size is 20; no smaller hashtables are considered
    numitems = 0; // initially, the hashtable is empty
    reprarray = new T*[maxsize];  // allocate space for the array of pointers
    // the for loop initialises all table entries to be undefined
    for (int i = 0; i < maxsize; i++)
    {
        reprarray[i] = 0;
    }
    T *pt0 = new T;  // This defines the fixed placeholder pointer
    *pt0 = 0;
    pt_nil = pt0;
    
    p=499;
    int a =111;
    int b =222;
    int m =maxsize;
}

// template<class T> hashset<T>::~hashset(void)
// {
//     delete[] reprarray;
// }

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
    // hash<T> hashfunction; // use the predefined hashfunction to get "key" values
    int index;
    index = hash(item) % maxsize; // First determine the position index in the hash table, where the new value is stored, if free.
    int location = -1;  // used to distinguish between undefined entries (null pointer) and placeholders
    while (reprarray[index] != 0) // We first check, if the item is already in the hashtable
    {
        if (reprarray[index] != pt_nil && *reprarray[index] == item)
            return;   // item found; no insertion
        if (location < 0 && reprarray[index] == pt_nil) // a placeholder object is found; i.e. if the item is not in the hashtable, this will be the place for the insertion
            location = index;
        index = (index + 1) % maxsize;
    }
    // after leaving the while loop we either have location < 1, i.e. we store the item at the last examined index (which contains a null pointer),
    // otherwise, if location >= 0 holds, we found a placeholder, so the item will be stored at the location of this placeholder
    if (location < 0)
        location = index;
    T *pt = new T;
    *pt = item;
    reprarray[location] = pt;   // store item in the hashtable
    ++ numitems;
    int load = 100 * numitems / maxsize;
    if (load >= 75)             // max load factor is exceeded; double the size
    {
        // std::cout<<numitems << ' ' << maxsize<<std::endl;
        int newsize = 2 * numitems;
        rehash(newsize);
    }
    return;
}

template<class T> void hashset<T>::remove(T item)
{
    // hash<T> hashfunction;  // use again the predefined hashfunction
    int index;
    index = hash(item) % maxsize;
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
        index = (index + 1) % maxsize;
    }
    cout << item << " is not in the hashtable.\n";
    return;
}

template<class T> bool hashset<T>::member(T item)
{
    int index;
    index = hash(item) % maxsize;
    while (reprarray[index] != 0) // again we search for item starting from the index position until we find a null pointer
    {
        if (reprarray[index] != pt_nil && *reprarray[index] == item)
            return true;  // item was found
        index = (index + 1) % maxsize;
    }
    return false;  // a null pointer was found, so item is not in the hashtable
}


template<class T> void hashset<T>::display(void) // only for test purposes
{
    // cout << "The size of the hashtable is: " << maxsize << "\n";
    // cout << "The number of elements in the hashtable is: " << numitems << "\n";
    for (int i = 0; i < maxsize; ++i)
    {
        if (reprarray[i] == 0)
            cout << "None ";
        else if (reprarray[i] == pt_nil)
            cout << "free ";
        else
            cout << *reprarray[i]<< ' ';
    }
    cout<<' '<<std::endl;
    return;
}

template<class T> int hashset<T>::get_num(void)
{
    return maxsize;
}
