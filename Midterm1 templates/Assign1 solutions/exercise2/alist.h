/*
*
*
*   The new functions are declared at the bottom of the class declaration.
*   The corresponding definitions are organized at the bottom of this file.
*
*/

#ifndef alist_h
#define alist_h

#include <cstdlib>
#include <stdio.h>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

template<class T> class AList
{
public:
// the original declarations
    AList(int size = 20);       // constructor
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
    int numitems;
    T *reprarray;
    void allocate(void);
    void deallocate(void);

/*
*
*/
// ex.1 delete_last method declaration
public:
    void delete_last(int k);
    void listDisplay();         // a helper function to display the list visually
private:
    void deallocate_ex1();      // a helper function used in delete_last(k) and only in delete_last(k), 
                                // similar to deallocate

/*
*
*/
// ex.2 structual recursion declaration
public:
    // I used symbol U to replace symbol T' in ex.2
    // src has return type U and three parameters. 
    // parameter e is of type U, f and g are two function pointers. 
    // f has return type U, and a single parameter of type T. note T is from AList<T>.
    // g has return type U, and two parameters of type U.
    template<class U> U src(U e ,U f(T value), U g(U l1, U l2));
};





// end of class declaration
/*
*
*
*
*
*/
// start of function definitions 





// the original function definitions
template<class T> AList<T>::AList(int size)
{
    maxsize = size;
    if (size < 20)
        minsize = size;
    else
        minsize = 20;
    numitems = 0;
    reprarray = new T[maxsize];
}

template<class T> T &AList<T>::operator[](int index)
{
    return reprarray[index - 1];
}

template<class T> int AList<T>::getlength(void)
{
    return numitems;
}

template<class T> void AList<T>::setitem(int index, T value)
{
    if ((index > 0) && (index <= numitems))
    {
        reprarray[index - 1] = value;
        return;
    }
    else
        cout << "Index error: index out or range\n";
}

template<class T> T AList<T>::getitem(int index)
{
    if ((index > 0) && (index <= numitems))
    {
        return reprarray[index - 1];
    }
    else
    {
        cout << "Index error: index out or range\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> void AList<T>::append(T value)
{
    if (numitems == maxsize)
        allocate();
    reprarray[numitems] = value;
    ++numitems;
    return;
}

template<class T> void AList<T>::insert(int index, T value)
{
    if (numitems == maxsize)
        allocate();
    if (index < numitems)
    {
        for (int j = numitems - 1; j >= index; --j)
        {
            reprarray[j+1] = reprarray[j];
        }
        reprarray[index] = value;
        ++numitems;
        return;
    }
    else
    {
        append(value);
        return;
    }
}

template<class T> void AList<T>::allocate(void)
{
    int newsize = 2 * maxsize;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        newarray[i] = reprarray[i];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

template<class T> void AList<T>::remove(int index)
{
    if ((numitems == maxsize / 4) && (maxsize > minsize))
        deallocate();
    if (index <= numitems)
    {
        for (int j = index; j < numitems; ++j)
        {
            reprarray[j-1] = reprarray[j];
        }
        --numitems;
        return;
    }
    else
        cout << "Index error: list index out of range\n";
}

template<class T> void AList<T>::deallocate(void)
{
    int newsize = maxsize / 2;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        newarray[i] = reprarray[i];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

template<class T> void AList<T>::concat(AList<T> &list)
{
    int length = list.getlength();
    for (int i = 1; i <= length; ++i)
    {
        append(list[i]);
    }
    return;
}

template<class T> bool AList<T>::member(T value)
{
    bool result = false;
    for (int i = 0; i < numitems; ++i)
    {
        if (reprarray[i] == value)
        {
            result = true;
            break;
        }
    }
    return result;
}

template<class T> bool AList<T>::equal(AList<T> &list)
{
    bool result = true;
    if (numitems == list.getlength())
    {
        for (int i = 0; i < numitems; ++i)
        {
            if (reprarray[i] == list[i + 1])
                continue;
            else
            {
                result = false;
                break;
            }
        }
    }
    else
        result = false;
    return result;
}

template<class T> bool AList<T>::sublist(AList<T> &list)
{
    int length = list.getlength();
    bool result = true;
    for (int i = 1, j = 0; (i <= length) && (j < numitems); ++i, ++j)
    {
        if (list[i] == reprarray[j])
        {
            if ((j == numitems - 1) && (i < length))
            {
                result = false;
                break;
            }
        }
        else
            if (j == numitems - 1)
            {
                result = false;
                break;
            }
            else
                --i;
    }
    return result;
}





/*
*
*/
// ex.1 delete_last definition

template<class T> void AList<T>:: delete_last(int k)
{
    if (k < numitems){
        cout << "The last " << k << " elements are deleted." << endl;
        numitems -= k;
    }
    else{
        cout << "The last " << numitems << " elements are deleted. The list is now empty." << endl; 
        numitems = 0;
    }

    deallocate_ex1();   // call the helper function, which will resize the array if needed,
                        // or do nothing if the size is suitable.
}

template<class T> void AList<T>:: deallocate_ex1(){
    if ((maxsize <= minsize) || (numitems > maxsize / 4))         // no need for reallocation
        return;

    int newsize = maxsize / 2;
    while ((numitems <= newsize / 4) && (newsize > minsize)){     // a loop to find out the newsize
        newsize /= 2;
    }

    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i){
        newarray[i] = reprarray[i];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

template<class T> void AList<T>:: listDisplay(){
    cout << "numItems: " << numitems << ";  list size: " << maxsize << endl;
    cout << "List";
    for (int i = 0; i < numitems; ++i){
        cout << " -> " << reprarray[i];
    }
    cout << endl;
}

/*
*
*/
// ex.2 structual recursion definition
template <class T> template<class U> U AList<T>::src(U e ,U f(T), U g(U, U))
{
    if (numitems == 0)
        return e;
    if (numitems == 1)
        return f(getitem(1));
    int mid = numitems / 2;     // cut the list in half
    // create two new lists to store each half
    AList<T>* list1 = new AList<T>(mid);
    AList<T>* list2 = new AList<T>(numitems - mid);
    for (int i = 0; i < mid; ++i){
        list1->append(reprarray[i]);
    }
    for (int i = mid; i < numitems; ++i){
        list2->append(reprarray[i]);
    }
    U l1 = list1->src<U>(e, f, g);
    U l2 = list2->src<U>(e, f, g);
    delete list1;
    delete list2;
    return g(l1, l2);
}

#endif