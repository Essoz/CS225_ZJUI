//
//  alist.h
//  
//
//  Created by KD on 14.01.21.
//  Annotated by HB on 18.01.21.
//

#ifndef alist_h
// if this file is not yet defined
#define alist_h
// define this file, and load all things below into the compiler

// for those we don't want to change or let others change, we define these contents
//  into the header file. In this example we define AList in the header file.

template<class T> 
class AList
{
public:
    AList(int size = 20);
    // ctor for AList. If no parameter is delivered, simply deliver 20 for size.
    //  Thus, no default ctor for AList is required any more.
    // notice. this function is a function with ONLY signature, so you WILL
    //  see its detailed decalarations in the following code (in an OUTLINE form).

//    virtual ~AList(); // I'm not sure what this line is for. Just ignore it.

    // all codes below are concerning concrete operations & functions for the class.
    //  notice (again). this function is a function with ONLY signature, so you WILL
    //  see its detailed decalarations in the following code (in an OUTLINE form).
    T &operator[](int index);
    int getlength(void);
    void setitem(int index, T value);
    T getitem(int index);
    void append(T value);
    void insert(int index, T value);
    void remove(int index);
    void concat(AList<T> &list);
    bool member(T value);
    bool equal(AList<T> &list);
    bool sublist(AList<T> &list);
    
private:
    int maxsize, minsize;
    int numitems; // number of items
    T *reprarray; // ptr of type T*

    // the two functions below are concerning memory space allocations.
    void allocate(void);
    void deallocate(void);
};

template<class T> 
AList<T>::AList(int size)
// this is the CONCRETE definition of the data type AList.
//  notice. if you've already set the default value above (in the non-concrete signature),
//  then you DON'T NEED TO set the default value in the concrete signature again.
{
    // the maximum size is always equal to the value of the given size.
    maxsize = size;

    // the minimum size MUST satisfy that minsize >= 20. i.e. if it's smaller than 20,
    //  then we set it to 20 automatically.
    if (size < 20)
        minsize = size;
    else
        minsize = 20;
    
    // notice. size != numitems. size is the CAPACITY of your list, numitems is the EXACT number of 
    //  THINGS in your list.
    numitems = 0;

    // notice the declaration of reprarray.
    //      T *reprarray;
    //  this is consistent with the assignment here. HERE IT MEANS:

    // 1. make an array of capacity equal to maxsize.
    // 2. each element inside this array is of type T.
    // 3. return the ptr of this array to the ptr reprarray.
    reprarray = new T[maxsize];
}

//template<class T> AList<T>::~AList()
//{
//    delete[] reprarray;
//}

#endif /* alist_h */
// if this file is already defined once previously, then the header file
//  will get here IMMEDIATELY.