//
//  hashset.h
//  
//
//  Created by KD on 6.03.21.
//

#ifndef hashset_h
#define hashset_h

template<class T> class hashset
{
public:
    hashset(int size = 20);
//    virtual ~hashset();
    T &operator[](int index);
// The operation add inserts an element into the hashtable, remove deletes an
// element and member checks, if the element is in the hashtable
    void add(T item);
    void remove(T item);
    bool member(T item);
// The function display is only used for testing purposes. It shows the size of
// the hashtable, the number of elements, and displays all entries
    void display(void);
private:
    int numitems;           // contains the number of elements in the hashtable
    T **reprarray;
/* reprarray defines a pointer to (an array of) pointers to values of type T. We will use a null pointer, if an entry is undefined, and a fixed pointer as placeholder for free entries (after remove) */
    T *pt_nil;              // used as placeholder
    int maxsize;            // defines the size of the hashtable
    void rehash(int newsize);
// rehash is an internal function to enlarge or shrink the hashtable,
// if the fill factors 0.75 or 0.25 are exceeded or undershot, resp.
};

#endif /* hashset_h */
