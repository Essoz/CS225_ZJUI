#include "hashset_f.h"
template<class T> void hashset<T>::rehash(int newsize)
{
    /*
        You should modify this function
        hint: you can use rand() to generate a random number between 0 and RAND_MAX
    */
    // std::cout<<newsize<<std::endl;
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
        if (reprarray[i] != 0 && reprarray[i] != pt_nil)
        {
            T item = *reprarray[i];
            int index = hash(item) % newsize;
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

template<class T> void hashset<T>::update(int a, int b, int m)
{
    /*
    Input:
        a,b,m: the new parameter, you should update the corresponding parameters
        in the hashset class.
    Output:
        None
    */
    
}

template<class T> int hashset<T>::hash(T value)
{
    /*
    Input: 
        value: the original value
    Output:
        A hash value 
    */
    return 0;
}


