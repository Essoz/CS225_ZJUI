//
//  dlistsort.cpp
//  
//
//  Created by KD on 16.01.21.
//  Modified on 23.01.21
//  Modified by HB on 18.02.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "dlistsort.h"
using std::cout;
using std::cin;

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

/* used in mergesort
 * input: 
 *  the index, index,
 *  the start pointer, pt_start.
 * output:
 *  the new pointer, pt.
 * side-effects:
 *  
 */
template<class T> node<T> *DList<T>::locate(int index, node<T> *pt_start)
{
    // when the given index is out of range, throw an error and exit immediately.
    if ((index <= 0) || (index > numitems))
    {
        cout << "Error: index out of range.\n";
        exit(EXIT_FAILURE);
    }
    // when the index is valid, perform as below.
    else
    {
        // initialize the starter pointer as the first pointer.
        node<T> *pt;
        if (pt_start == 0)
            pt = (*dummy).getnext();
        else
            pt = pt_start;
        // traverse through [1,index] until pt gets the position index.
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

/* (from small to large) selection sort using linked list.
 * 1. find the smallest element in the whole list.
 * 2. push this element into the first place of the temporary list.
 * 3. repeat this step until all the elements in the initial list are gone.
 */

// starter function
template<class T> void DListsort<T>::selectionsort(void)
{
    // localize the numitems & dummy.
    // the usage of dummy is illustrated in the graph I drew.
    int numitems = DList<T>::numitems;
    node<T> * dummy;
    dummy = DList<T>::dummy;

    // when the total number of elements in the list is smaller or equal to 1,
    //  then return immediately.
    if (numitems <= 1)
        return;

    // define the firstnode and last node here.
    node<T> *firstnode;
    firstnode = (*dummy).getnext();
    node<T> *lastnode;
    lastnode = (*dummy).getprevious();

    // initialize outlastnode.
    node<T> *outlastnode;
    outlastnode = dummy;

    // isolate dummy so that it forms a new linked list.
    // NOTE. dummy act as the head of the new linked list.
    (*outlastnode).setnext(dummy);
    (*outlastnode).setprevious(dummy);

    // function body for the selection sort.
    // output the new outlastnode.
    outlastnode = ssort(numitems, firstnode, lastnode, dummy, outlastnode);
    return;
}

/* functional function
 * input: 
 *  the number of items in the array num,
 *  the initial linked list [firstnode, lastnode],
 *  the output linked list [dummy, outlastnode].
 * output:
 *  the last element in the new linked list.
 * side-effects:
 *  sort the linked list into a new linked list with last node called outlastnode.
 */ 
template<class T> node<T> *DListsort<T>::ssort(int num, node<T> *firstnode, node<T> *lastnode, node<T> *outlastnode, node<T> *dummy)
{
    // iterate num times.
    for (int c = num; c > 0; --c)
    {
        // find the node with the minimum value in the whole initial linked list.
        node<T> *minnode;
        minnode = getminimum(firstnode, lastnode);

        // if the first element has the smallest value, pop it.
        if (minnode == firstnode)
        {
            firstnode = (*firstnode).getnext();
        }

        // if the last element has the smallest value, pop it.
        else if (minnode == lastnode)
        {
            lastnode = (*lastnode).getprevious();
        }

        // if one element inside the array (not the first nor the last) has the
        //  smallest value, pop it out and make the linked list itself again.
        else
        {
            cut(firstnode, lastnode, minnode);
        }

        // NOTE. all three operations above cuts one element out, but they're NOT
        //  stored in anywhere, so we guess that we're going to make take them below.

        // add minnode between outlastnode & dummy.
        add(minnode, outlastnode, dummy);

        // update the outlastnode to be the last node of the new linked list.
        // NOTE that after minnode is added, the outlastnode is NOT the OUT LAST NODE any more.
        outlastnode = minnode;
    }

    // return the outlastnode we want.
    return outlastnode;
}

/* helper function
 * input:
 *  the element you want to add, minadd,
 *  the predecessor, pred,
 *  the successor, succ.
 * output:
 *  none.
 * side-effects:
 *  add one element into the given position.
 */
template<class T> void DListsort<T>::add(node<T> *minadd, node<T> *pred, node<T> *succ)
{
    // add one node (element) minadd between the two elements outlastnode & dummy.
    (*minadd).setprevious(pred);
    (*minadd).setnext(succ);
    (*pred).setnext(minadd);
    (*succ).setprevious(minadd);
    return;
}

/* helper function
 * input:
 *  the complete linked list to cut off, [first, last],
 *  the element you want to cut out, mincut.
 * output:
 *  none.
 * side-effects:
 *  cut off the linked list [first, last] on the cut-point mincut.
 */
template<class T> void DListsort<T>::cut(node<T> *first, node<T> *last, node<T> *mincut)
{
    // get the predecessor and successor of the element you want to cut out
    node<T> *pred;
    pred = (*mincut).getprevious();
    node<T> *succ;
    succ = (*mincut).getnext();

    // re-connect the the cut-off linked lists
    (*pred).setnext(succ);
    (*succ).setprevious(pred);
    return;
}

template<class T> node<T> *DListsort<T>::getminimum(node<T> *first, node<T> *last)
{
    node<T> *minpos;
    minpos = first;
    T mincandidate = (*first).getdata();
    T othercandidate;
    node<T> *cursor;
    cursor = first;
    while (cursor != last)
    {
        cursor = (*cursor).getnext();
        othercandidate = (*cursor).getdata();
        if (othercandidate < mincandidate)
        {
            mincandidate = othercandidate;
            minpos = cursor;
        }
    }
    return minpos;
}

// starter function
template<class T> void DListsort<T>::mergesort(int thr)
{
    // localize the variable numitems (because it was initially a friend, not a member).
    int numitems = DList<T>::numitems;
    // localize the variable dummy as a dummy (哑) node (because it was initially a friend, not a member).
    node<T> *dummy;
    dummy = DList<T>::dummy;

    // manipulate threshold to be between 20 and 100.
    // according to the slides, the threshold is typically around 60 or 70.
    if (thr < 20)
        thr = 20;
    if (thr > 100)
        thr = 100;

    // perform selectionsort when the scale is smaller than the threshold.
    if (numitems <= thr)
    {
        selectionsort();
        return;
    }

    // NOTE. only when numitems > thr you can get here, or you've already returned
    //  to the main program.

    // initialize the liked lists
    node<T> *firstnode;
    firstnode = (*dummy).getnext();
    node<T> *lastnode;
    lastnode = (*dummy).getprevious();

    // create the output node and perform the sort alogrithm
    node<T> *out;
    out = dummy;

    // perform the mergesort recursive function
    out = msort(numitems, firstnode, lastnode, thr, dummy, out);
    return;
}

// recursive function
template<class T> node<T> *DListsort<T>::msort(int num, node<T> *first, node<T> *last, int thr, node<T> *dummy, node<T> *outlastnode)
{
    // when the number of elements is smaller than the threshold, use selectionsort insdead of mergesort.
    if (num <= thr)
    {
        // after selectionsort, the last node of the result linked list is 
        //  stored in outlastnode.
        outlastnode = ssort(num, first, last, outlastnode, dummy);

        // return the recursive function immediately because already hit the
        //  threshold and have sorted well.
        return outlastnode;
    }

    // initialize nodes
    node<T> *splitnode;

    // get the node you want to cut (here it is the pointer in the middle.)
    splitnode = DList<T>::locate(num/2, first);
    node<T> *succnode;
    succnode = (*splitnode).getnext();
    node<T> *out1;
    node<T> *out2;

    // recursively mergesort the linked lists
    out1 = msort(num/2, first, splitnode, thr, dummy, outlastnode);
    out2 = msort((num+1)/2, succnode, last, thr, dummy, out1);

    // merge the two sorted lists
    first = (*outlastnode).getnext();
    succnode = (*out1).getnext();
    outlastnode = merge(first, out1, succnode, out2, dummy, outlastnode);
    return outlastnode;
}

// functional function: merge two sorted lists
template<class T> node<T> *DListsort<T>::merge(node<T> *first1, node<T> *last1, node<T> *first2, node<T> *last2, node<T> *dummy, node<T> *outlast)
{
    node<T> *temp;
    if ((*first1).getdata() <= (*first2).getdata())
    {
        temp = (*first1).getnext();
        add(first1, outlast, dummy);
        outlast = first1;
        if (first1 != last1)
        {
            first1 = temp;
            outlast = merge(first1, last1, first2, last2, dummy, outlast);
        }
        else
        {
            while (first2 != last2)
            {
                temp = (*first2).getnext();
                add(first2, outlast, dummy);
                outlast = first2;
                first2 = temp;
            }
            add(first2, outlast, dummy);
            outlast = first2;
        }
    }
    else
    {
        temp = (*first2).getnext();
        add(first2, outlast, dummy);
        outlast = first2;
        if (first2 != last2)
        {
            first2 = temp;
            outlast = merge(first1, last1, first2, last2, dummy, outlast);
        }
        else
        {
            while (first1 != last1)
            {
                temp = (*first1).getnext();
                add(first1, outlast, dummy);
                outlast = first1;
                first1 = temp;
            }
            add(first1, outlast, dummy);
            outlast = first1;
        }
    }
    return outlast;
}
