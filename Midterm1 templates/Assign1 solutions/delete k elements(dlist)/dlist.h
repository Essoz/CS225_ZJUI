/*
*
*
*   The new functions are declared at the bottom of the class declaration.
*   The corresponding definitions are organized at the bottom of this file.
*
*/

#ifndef dlist_h
#define dlist_h

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "dlist.h"
using std::cout;
using std::cin;
using std::endl;

template<class T> class DList;

template<class T> class node
{
    friend class DList<T>;
public:
    node(T item = 0, node<T> *pt_n = 0, node<T> *pt_p = 0);
//    virtual ~node(void);
    T getdata(void);
    node<T> *getnext(void);
    node<T> *getprevious(void);
    void setdata(T item);
    void setnext(node<T> *pt);
    void setprevious(node<T> *pt);
private:
    T dataitem;
    node<T> *pt_next;
    node<T> *pt_previous;
};

template<class T> class DList
{
public:
    DList(void);
//    virtual ~DList();
    T operator[](int index);
    int getlength(void);
    void setitem(int index, T value);
    T getitem(int index);
    void append(T value);
    void insert(int index, T value);
    void remove(int index);
    void concat(DList<T> *dlist);
    bool member(T value);
    bool equal(DList<T> *dlist);
    bool sublist(DList<T> *dlist);
private:
    node<T> *dummy;
    int numitems;
    node<T> *locate(int index);
    node<T> *first(void);
    node<T> *last(void);

/*
*
*/
// ex.1 delete_last method declaration
public:
    void delete_last(int k);
    void listDisplay();         // a helper function to display the list visually
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
template<class T> node<T>::node(T item, node<T> *pt_n, node<T> *pt_p)
{
    dataitem = item;
    pt_next = pt_n;
    pt_previous = pt_p;
}

template<class T> T node<T>::getdata(void)
{
    return dataitem;
}

template<class T> node<T> *node<T>::getnext(void)
{
    return pt_next;
}

template<class T> node<T> *node<T>::getprevious(void)
{
    return pt_previous;
}

template<class T> void node<T>::setdata(T item)
{
    dataitem = item;
    return;
}

template<class T> void node<T>::setnext(node<T> *pt)
{
    pt_next = pt;
    return;
}

template<class T> void node<T>::setprevious(node<T> *pt)
{
    pt_previous = pt;
    return;
}

template<class T> DList<T>::DList(void)
{
    dummy = new node<T>;
    (*dummy).setnext(dummy);
    (*dummy).setprevious(dummy);
    numitems = 0;
}

//template<class T> DList<T>::~DList()
//{
//    delete[] reprarray;
//}

template<class T> T DList<T>::operator[](int index)
{
    T val = getitem(index);
    return val;
}

template<class T> int DList<T>::getlength(void)
{
    return numitems;
}

template<class T> node<T> *DList<T>::last(void)
{
    return (*dummy).getprevious();
}

template<class T> node<T> *DList<T>::first(void)
{
    return (*dummy).getnext();
}

template<class T> void DList<T>::append(T value)
{
    node<T> *lpt;
    lpt = last();
    node<T> *pt = new node<T>;
    (*pt).setdata(value);
    (*pt).setnext(dummy);
    (*pt).setprevious(lpt);
    (*dummy).setprevious(pt);
    (*lpt).setnext(pt);
    ++numitems;
    return;
}

template<class T> node<T> *DList<T>::locate(int index)
{
    if ((index <= 0) || (index > numitems))
    {
        cout << "Error: index out of range.\n";
        exit(EXIT_FAILURE);
    }
    else
    {
        node<T> *pt;
        pt = (*dummy).getnext();
        for (int i = 1; i < index; ++i)
        {
            pt = (*pt).getnext();
        }
        return pt;
    }
}

template<class T> void DList<T>::setitem(int index, T value)
{
    node<T> *pt;
    pt = locate(index);
    (*pt).setdata(value);
    return;
}

template<class T> T DList<T>::getitem(int index)
{
    node<T> *pt;
    pt = locate(index);
    return (*pt).getdata();
}

template<class T> void DList<T>::insert(int index, T value)
{
    node<T> *pt_i;
    pt_i = locate(index);
    node<T> *pt_i1;
    pt_i1 = (*pt_i).getprevious();
    node<T> *pt_new = new node<T>;
    (*pt_new).setdata(value);
    (*pt_new).setnext(pt_i);
    (*pt_new).setprevious(pt_i1);
    (*pt_i).setprevious(pt_new);
    (*pt_i1).setnext(pt_new);
    numitems += 1;
    return;
}

template<class T> void DList<T>::remove(int index)
{
    node<T> *pt_i;
    pt_i = locate(index);
    node<T> *pt_i1;
    pt_i1 = (*pt_i).getprevious();
    node<T> *pt_i2;
    pt_i2 = (*pt_i).getnext();
    (*pt_i1).setnext(pt_i2);
    (*pt_i2).setprevious(pt_i1);
    numitems -= 1;
    return;
}

template<class T> void DList<T>::concat(DList<T> *dlist)
{
    int num = (*dlist).getlength();
    if (num > 0)
    {
        node<T> *lpt;
        lpt = last();
        node<T> *pt0;
        pt0 = (*dlist).dummy;
        node<T> *pt1;
        pt1 = (*pt0).getnext();
        (*pt1).setprevious(lpt);
        (*lpt).setnext(pt1);
        node<T> *pt2;
        pt2 = (*pt0).getprevious();
        (*dummy).setprevious(pt2);
        (*pt2).setnext(dummy);
        numitems += num;
    }
    return;
}

template<class T> bool DList<T>::member(T value)
{
    bool result = false;
    node<T> *pt;
    pt = (*dummy).getnext();
    for (int i = 0; i < numitems; ++i)
    {
        if ((*pt).getdata() == value)
        {
            result = true;
            break;
        }
        else
        {
            pt = (*pt).getnext();
        }
    }
    return result;
}

template<class T> bool DList<T>::equal(DList<T> *dlist)
{
    bool result = true;
    if ((*dlist).getlength() != numitems)
    {
        result = false;
    }
    else
    {
        node<T> *pt;
        pt = (*dummy).getnext();
        node<T> *pt0;
        pt0 = (*dlist).dummy;
        node<T> *pt_other;
        pt_other = (*pt0).getnext();
        for (int i = 0; i < numitems; ++i)
        {
            if ((*pt).getdata() != (*pt_other).getdata())
            {
                result = false;
                break;
            }
            else
            {
                pt = (*pt).getnext();
                pt_other = (*pt_other).getnext();
            }
        }
    }
    return result;
}

template<class T> bool DList<T>::sublist(DList<T> *dlist)
{
    bool result = true;
    node<T> *pt;
    pt = (*dummy).getnext();
    node<T> *pt0;
    pt0 = (*dlist).dummy;
    node<T> *pt_other;
    pt_other = (*pt0).getnext();
    int numother = (*dlist).getlength();
    for (int i = 0, j = 0; (i < numother) && (j < numitems); ++i, ++j)
    {
        if ((*pt_other).getdata() == (*pt).getdata())
        {
            if ((j == numitems - 1) && (i < numother - 1))
            {
                result = false;
                break;
            }
            pt = (*pt).getnext();
            pt_other = (*pt_other).getnext();
        }
        else
        {
            if (j == numitems - 1)
            {
                result = false;
                break;
            }
            else
            {
                pt = (*pt).getnext();
                --i;
            }
        }
        
    }
    return result;
}





/*
*
*/
// ex.1 delete_last definition

template<class T> void DList<T>::delete_last(int k)
{
    int remain = 0;                 // stores the number of remaining nodes
    if (k < numitems){
        cout << "The last " << k << " elements are deleted." << endl;
        remain = numitems - k;
    }
    else{
        cout << "The last " << numitems << " elements are deleted. The list is now empty." << endl; 
        remain = 0;
    }

    node<T> *node_cur = dummy->getprevious();   // the pointer to the current node, initially to the last node,
                                                // then iterate through the linked list to delete the unwanted nodes
    for (int i = 0; i < numitems - remain; ++i){
        node_cur = node_cur->getprevious();
        delete node_cur->getnext();
    }
    node_cur->setnext(dummy);
    dummy->setprevious(node_cur);
    numitems = remain;
}

template<class T> void DList<T>::listDisplay()
{
    cout << "numItems: " << numitems << endl;
    cout << "List";
    node<T> *node_cur = dummy;
    for (int i = 0; i < numitems; ++i){
        node_cur = node_cur->getnext();
        cout << " -> " << node_cur->getdata();
    }
    cout << endl;
}
#endif /* dlist_h */