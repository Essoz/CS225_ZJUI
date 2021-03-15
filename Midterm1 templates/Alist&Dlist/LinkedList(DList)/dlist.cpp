/*                                    tab:8
 *
 * dlist.cpp - source file for CS225 Linked List.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice and the following
 * two paragraphs appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE AUTHOR OR THE UNIVERSITY OF ILLINOIS BE LIABLE TO
 * ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
 * DAMAGES ARISING OUT  OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
 * EVEN IF THE AUTHOR AND/OR THE UNIVERSITY OF ILLINOIS HAS BEEN ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE AUTHOR AND THE UNIVERSITY OF ILLINOIS SPECIFICALLY DISCLAIM ANY
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE
 * PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND NEITHER THE AUTHOR NOR
 * THE UNIVERSITY OF ILLINOIS HAS ANY OBLIGATION TO PROVIDE MAINTENANCE,
 * SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Author:        Klaus-Dieter Schewe
 * Version:        2
 * Creation Date:   ?
 * Filename:        main.cpp
 * History:
 *    Klaus-Dieter Schewe    1    11 January 2021
 *        First written.
 *    Hao BAI    2    19 January 2021
 *        Annotations added.
 *
 */

// this file is to define the able-to-change part of the two classes.

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "dlist.h"
using std::cout;
using std::cin;

/* 
 * input: the item you want to store, the ptr to previous node, the ptr to next node.
 * output: none.
 * side-effects: localize the variables inside the object you created using class node.
 * overall-functionality: construct the node ctor.
 */
template<class T> node<T>::node(T item, node<T> *pt_n, node<T> *pt_p)
{
    dataitem = item;
    pt_next = pt_n;
    pt_previous = pt_p;
}

/* 
 * input: none.
 * output: the current item you're trying to deal with.
 * side-effects: none.
 * overall-functionality: get the item.
 */
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


/***** From this part we design DList *****>


/* 
 * input: none.
 * output: none.
 * side-effects: create a HEADER PTR dummy.
 * overall-functionality: construct the ctor for DList.
 */

// if you get any queries about the header ptr, please go back to slides & books.
// notice. dummy is called "muted node" or "void node", which is designed only to avoid the
//  situation that the node is empty.
template<class T> DList<T>::DList(void)
{
    // make dummy to point to a new node. 
    // notice. now dummy can use anything defined in the class node. 
    dummy = new node<T>;

    // these lines are to initialize the linked list.
    (*dummy).setnext(dummy);
    (*dummy).setprevious(dummy);

    // numitems is a variable under DList, not node.
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

// notice. the last of the linked list is just the previous element of
//  the header ptr.
template<class T> node<T> *DList<T>::last(void)
{
    return (*dummy).getprevious();
}

// notice. the first element in the linked list is just the NEXT element of
//  the header ptr.
template<class T> node<T> *DList<T>::first(void)
{
    return (*dummy).getnext();
}

// to append something is equi. to get another node appended at last.
template<class T> void DList<T>::append(T value)
{
    // lpt == the pointer pointing to the last element
    node<T> *lpt;
    lpt = last();

    // initialize the new pointer & element.
    node<T> *pt = new node<T>;
    (*pt).setdata(value);
    (*pt).setnext(dummy);
    (*pt).setprevious(lpt);
    (*dummy).setprevious(pt);

    // set the next-pointer for the element *lpt to be the new ptr.
    (*lpt).setnext(pt);
    ++numitems;
    return;
}

// this function is designed to find the pointer of the given index.
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

// this function is designed to insert one element into the linked list.
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

// this function is designed to concat two linked lists into one.
template<class T> void DList<T>::concat(DList<T> *dlist)
{
    int num = (*dlist).getlength();
    if (num > 0)
    {
        // lpt == the last ptr to the THIS linked list
        node<T> *lpt;
        lpt = last();

        // pt0 == the header ptr to the linked list PASSED IN
        node<T> *pt0;
        pt0 = (*dlist).dummy;

        // pt1 == the ACTUAL header ptr to the linked list PASSED IN
        node<T> *pt1;
        pt1 = (*pt0).getnext();

        // link the two linked lists from head to tail
        (*pt1).setprevious(lpt);
        (*lpt).setnext(pt1);

        // pt2 == the "last ptr" to the linked list PASSED IN
        node<T> *pt2;
        pt2 = (*pt0).getprevious();

        // link the two linked lists from tail to head
        (*dummy).setprevious(pt2);
        (*pt2).setnext(dummy);

        // the length is added by the number of elements stored in the linked list passed in.
        numitems += num;
    }
    return;
}

// this function is designed to check whether the given number is in the linked list.
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

// this function is designed to check whether two lists are exactly the same.
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

// this function is designed to check whether one list is a sublist of another list.
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
