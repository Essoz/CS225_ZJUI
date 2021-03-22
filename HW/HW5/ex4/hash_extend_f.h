#include <stdio.h>
#include <iostream>
#include <cstdlib>

#include "hash_extend.h"
using std::cout;
using std::cin;
using std::hash;
/* Put your implementation here */


/* inthis defines a constructor */
HashSet_LCFS::HashSet_LCFS(int size)
{
    maxsize = size;
    if (size < 20)
        maxsize = 20; // default size is 20; no smaller hashtables are considered
    numitems = 0; // initially, the hashtable is empty
    reprarray = new int*[maxsize];  // allocate space for the array of pointers
    disarray = new int[maxsize];
    // the for loop initialises all table entries to be undefined
    for (int i = 0; i < maxsize; i++)
    {
        reprarray[i] = 0;
        disarray[i] = -1;
    }
    int *pt0 = new int;  // inthis defines the fixed placeholder pointer
    *pt0 = 0;
    pt_nil = pt0;
}
HashSet_RH::HashSet_RH(int size)
{
    maxsize = size;
    if (size < 20)
        maxsize = 20; // default size is 20; no smaller hashtables are considered
    numitems = 0; // initially, the hashtable is empty
    reprarray = new int*[maxsize];  // allocate space for the array of pointers
    disarray = new int[maxsize];
    // the for loop initialises all table entries to be undefined
    for (int i = 0; i < maxsize; i++)
    {
        reprarray[i] = 0;
        disarray[i] = -1;
    }
    int *pt0 = new int;  // inthis defines the fixed placeholder pointer
    *pt0 = 0;
    pt_nil = pt0;
}
// template<class int> hashset<int>::~hashset(void)
// {
//     delete[] reprarray;
// }
void HashSet_LCFS::add(int item)
{
    hash<int> hashfunction; // use the predefined hashfunction to get "key" values
    int index;
    index = hashfunction(item) % maxsize; // First determine the position index in the hash table, where the new value is stored, if free.
    int location = -1;  // used to distinguish between undefined entries (null pointer) and placeholders
    if(reprarray[index] != 0) // We first check, if the item is already in the hashtable
    {
        if(reprarray[index] != pt_nil && *reprarray[index] == item)
            return;   // item found; no insertion
        if(location < 0 && reprarray[index] == pt_nil) // a placeholder object is found; i.e. if the item is not in the hashtable, this will be the place for the insertion
            location = index;
        else
        {
           location = index;    //these location has a redident, but it must move out to the new location, the newly input element will occupy this location
           int new_index=index;
           while (reprarray[new_index]!=0)
           {
               if(reprarray[new_index] == pt_nil)
                {
                    reprarray[new_index]=reprarray[index];
                    break;
                }
               new_index+=(new_index+1)% maxsize;
           }
           reprarray[new_index]=reprarray[index];   //now we find the reprarray with 0 entry, so add the previous "resident" element to it 
        }
    }
    // after leaving the while loop we either have location < 1, i.e. we store the item at the last examined index (which contains a null pointer),
    // otherwise, if location >= 0 holds, we found a placeholder, so the item will be stored at the location of this placeholder
    if (location < 0)
        location = index;
    int *pt = new int;
    *pt = item;
    reprarray[location] = pt;   // store item in the hashtable
    ++ numitems;
    int load = 100 * numitems / maxsize;
    if (load >= 75)             // max load factor is exceeded; double the size
    {
        int newsize = 2 * numitems;
        rehash(newsize);
    }
    return;
}
void HashSet_RH::add(int item)
{
    hash<int> hashfunction; // use the predefined hashfunction to get "key" values
    int index;
    int distance=0;
    index = hashfunction(item) % maxsize; // First determine the position index in the hash table, where the new value is stored, if free.
    int location = -1;  // used to distinguish between undefined entries (null pointer) and placeholders
    if(reprarray[index] != 0) // We first check, if the item is already in the hashtable
    {
        if(reprarray[index] != this->pt_nil && *(reprarray[index]) == item)
            return;   // item found; no insertion
        if(location < 0 && reprarray[index] == this->pt_nil) // a placeholder object is found; i.e. if the item is not in the hashtable, this will be the place for the insertion
            location = index;
        else
        {
           this->add(index, item, distance, reprarray,disarray);
        }
    }
    // after leaving the while loop we either have location < 1, i.e. we store the item at the last examined index (which contains a null pointer),
    // otherwise, if location >= 0 holds, we found a placeholder, so the item will be stored at the location of this placeholder
    if (location < 0)
        location = index;
    int *pt = new int;
    *pt = item;
    reprarray[location] = pt;   // store item in the hashtable
    disarray[location] = distance;
    ++ this->numitems;
    int load = 100 * this->numitems / maxsize;
    if (load >= 75)             // max load factor is exceeded; double the size
    {
        int newsize = 2 * numitems;
        rehash(newsize);
    }
    return;
}
void HashSet_RH::add(int index, int item, int distance,int **HashArray, int* DistArray)
    {

        if (HashArray[index]==0 || HashArray[index] == pt_nil)   //empty entry here, so just insert into it
        {
            int *newpt = new int;
            *newpt = item;
            HashArray[index] = newpt; 
            DistArray[index]=distance;
            return;
        }
        else if (distance<=DistArray[index])
            this->add((index+1)%maxsize,item,distance+1,HashArray, DistArray);
        else    //now we need to swap the elements, and keep the recursion going
        {
            int new_distance=DistArray[index];
            int new_item=*HashArray[index]; //take out the resident element
            int *pt = new int;
            *pt = item;
            HashArray[index] = pt; 
            DistArray[index]=distance;   //enter the new element
            this->add((index+1)%maxsize,new_item,new_distance+1,HashArray, DistArray);
        }
        return;
}
void HashSet_LCFS::remove(int item)
{
    hash<int> hashfunction;  // use again the predefined hashfunction
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
        index = (index + 1) % maxsize;
    }
    cout << item << " is not in the hashtable.\n";
    return;
}
void HashSet_RH::remove(int item)
{
    hash<int> hashfunction;  // use again the predefined hashfunction
    int index;
    index = hashfunction(item) % maxsize;
    while (reprarray[index] != 0)  // same as for add we search for item in the hashtable; the search starts at the designated hash value, and stops when we find a null pointer
    {
        if (reprarray[index] != this->pt_nil && *(reprarray[index]) == item)
                    // item found
        {
            int nextindex = (index + 1) % maxsize;
            /* check the next entry, if it is a null pointer; if yes, we can overwrite item by a null pointer; otherwise we use a placeholder, i.e. the pointer pt_nil */
            if (reprarray[nextindex] == 0){
                reprarray[index] = 0;
                disarray[index] =-1;
            }
            else{
                reprarray[index] = pt_nil;
                disarray[index] =-1;
            }
            --numitems;
            int load = 100 * this->numitems / maxsize;
            if (load <= 25)
                // if the min load factor is undershot, we shrink the hashtable, but the size shall always be >= 20
            {
                int newsize = this->numitems;
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
void HashSet_LCFS::rehash(int newsize)
{
    if (newsize < 20)
        newsize = 20;
    int newnum = 0;
    int new_index;
    int **newarray = new int*[newsize];   // allocate space for a new hashtable of the given new size
    for (int i = 0; i < newsize; i++)
    {
        newarray[i] = 0;   // initialise the new hashtable with only null pointers
    }
    for (int i = 0; i < maxsize; i++)  // we need to copy all existing entries to the new hash table
    {
        if (reprarray[i] != 0 && reprarray[i] != pt_nil)
        {
            int item = *reprarray[i];
            hash<int> hashfunction;
            int index = hashfunction(item) % newsize;
                // recompute the new hash value

            if (newarray[index]!=0)
            {
                new_index=index;
                while (newarray[new_index]!=0)
                {
                    new_index+=(new_index+1)% maxsize;
                }
                reprarray[new_index]=reprarray[index];  //find the new location and insert into it
            }
            newarray[index] = reprarray[i];  // do the actual copying
            ++ newnum;
        }
    }
    numitems = newnum;   // change the number of stored elements
    reprarray = newarray;   // make the new hashtable the one of the hashset object
    maxsize = newsize;   // update the size
}
void HashSet_RH::rehash(int newsize)
{
    if (newsize < 20)
        newsize = 20;
    int newnum = 0;
    int **newarray = new int*[newsize];   // allocate space for a new hashtable of the given new size
    int* newdisarray = new int[newsize];

    for (int i = 0; i < newsize; i++)
    {
        newarray[i] = 0;   // initialise the new hashtable with only null pointers
        newdisarray[i]=-1;
    }
    for (int i = 0; i < maxsize; i++)  // we need to copy all existing entries to the new hash table
    {
        if (this->reprarray[i] != 0 && this->reprarray[i] != this->pt_nil)    //need to take the copy
        {
            int item = *reprarray[i];
            int distance= disarray[i];
            hash<int> hashfunction;
            int index = hashfunction(item) % newsize;
                // recompute the new hash value

            if (newarray[index]!=0)
            {
                this->add(index, item, distance, newarray, newdisarray);
            }
            newarray[index] = reprarray[i];  // do the actual copying
            newdisarray[index]=0;
            ++ newnum;
        }
    }
    numitems = newnum;   // change the number of stored elements
    reprarray = newarray;   // make the new hashtable the one of the hashset object
    disarray = newdisarray;
    maxsize = newsize;   // update the size
}
void HashSet_LCFS::display(void) // only for test purposes
{
    cout << "in the size of the hashtable is: " << maxsize << "\n";
    cout << "in the number of elements in the hashtable is: " << numitems << "\n";
    for (int i = 0; i < maxsize; ++i)
    {
        if (reprarray[i] == 0)
            cout << "in the entry " << i + 1 << " is undefined.\n";
        else if (reprarray[i] == pt_nil)
            cout << "in the entry " << i + 1 << " is free.\n";
        else
            cout << "in the entry " << i + 1 << " is " << *reprarray[i] << " .\n";
    }
    return;
}
void HashSet_RH::display(void) // only for test purposes
{
    cout << "inthe size of the hashtable is: " << maxsize << "\n";
    cout << "inthe number of elements in the hashtable is: " << numitems << "\n";
    for (int i = 0; i < maxsize; ++i)
    {
        if (reprarray[i] == 0)
            cout << "inthe entry " << i + 1 << " is undefined.\n";
        else if (reprarray[i] == pt_nil)
            cout << "inthe entry " << i + 1 << " is free.\n";
        else
            cout << "inthe entry " << i + 1 << " is " << *reprarray[i] << " .\n";
    }
    return;
}
