//
//  dlist.cpp
//  
//
//  Created by KD on 16.01.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "dlist.h"
using std::cout;
using std::cin;
using std::endl;

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


// Exercise 4
// Created by Xiong Neng on 21.01.21

// This function displays the list
template<class T> void DList<T>::print(void){
    node<T> * curr;
    curr = dummy->getnext();
    for (int i = 0; i < numitems; i++){
        cout << ' ' << curr->getdata();
        curr = curr->getnext();
    }
    cout << endl;
}

//// Helper binary search function
//// Return the index of the first element in range [start,end] that is smaller than value
template<class T> int DList<T>::bSearch(int start, int end, T value){
    int middle, half, len;
    len = end - start + 1;

    while(len > 0) {
        half = len >> 1;
        middle = start + half;
        if(locate(middle)->getdata() < value) {
            start = middle + 1;
            len = len-half-1;
        }
        else
            len = half;
    }
    return start;
}

// The swap function needed for sorting algorithm
template<class T> void DList<T>::swap(int i, int j){
    node<T> * pt_i, * pt_j;
    pt_i = locate(i);
    pt_j = locate(j);

    T temp = pt_i->getdata();
    pt_i->setdata(pt_j->getdata());
    pt_j->setdata(temp);
}

template<class T> void DList<T>::SelectionSort(void){
    // We can swap the minimal element to the front so that in&out lists are one
    // loop through n-1 swaps
    for (int i = 1; i < numitems+1; i++){
        int minimal = i;
        // loop through unsorted part to find the minimal
        for (int j = i; j < numitems+1; j++){
            minimal = ((locate(j))->getdata() < (locate(minimal))->getdata()) ? j : minimal;
        }
        // swap the minimal element in the unsorted part to the front
        swap(i, minimal);
    }
}

template<class T> void DList<T>::InsertionSort(void){
    // loop through n-1 needed insertions
    for (int i = 1; i < numitems; i++){
        insert(bSearch(1, i, locate(i+1)->getdata()), locate(i+1)->getdata());
        remove(i+2);
    }
}

template<class T> void DList<T>::BubbleSort(void){
    for(int i = 1 ; i < numitems + 1 ; i++){
        for(int j = 1 ; j < numitems - i + 1 ; ++j){
            if(locate(j)->getdata()>locate(j+1)->getdata()) swap(j,j+1);
        }
    }
}
