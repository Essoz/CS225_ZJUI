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
 *    Klaus-Dieter Schewe    1    17 January 2021
 *        First written.
 *    Hao BAI    2    22 January 2021
 *        Annotations added.
 *
 */


#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "stack.h"
using std::cout;
using std::cin;

template<class T> stack<T>::stack(int size)
{
    // the max size of a stack should be the initial size.
    maxsize = size;
    // the min size should be no more than 10.
    if (size < 10)
        minsize = size;
    else
        minsize = 10;
    numitems = 0;
    reprarray = new T[maxsize];
}

//template<class T> stack<T>::~stack()
//{
//    delete[] reprarray;
//}

// if we want to get the index of the array, we need to use the operator[],
//  and as the same in the arrayList, KD makes the index human-oriented, which means that 
//  he is going to use index-1 for the array index.
template<class T> T &stack<T>::operator[](int index)
{
    return reprarray[index - 1];
}

// the height of a satck is just the number of items.
template<class T> int stack<T>::getheight(void)
{
    return numitems;
}

// if we want to push an element onto the stack, it's equivalent to
//  add one element at the end of the array.
template<class T> void stack<T>::push(T value)
{
    if (numitems == maxsize)
        allocate();
    reprarray[numitems] = value;
    ++numitems;
    return;
}

// if we want to pop out an element out of the stack, we only need to
//  remove the top element. however, if the stack is empty, we should not
//  pop up. also, if the array capacity is too large, we need to deallocate.
template<class T> T stack<T>::pop(void)
{
    if (numitems > 0)
    {
        T result = reprarray[numitems - 1];
        if ((numitems <= maxsize / 4) && (maxsize >= 2 * minsize))
            deallocate();
        --numitems;
        return result;
    }
    else
    {
        cout << "The stack is empty.";
        exit(EXIT_FAILURE);
        // exit() means to return everything immediately.
    }
}

// this funciton is designed to get the top of the stack.
//  also consider that, if the stack is empty, then it's impossible to pop out.
template<class T> T stack<T>::top(void)
{
    if (numitems > 0)
        return reprarray[numitems - 1];
    else
    {
        cout << "The stack is empty.";
        exit(EXIT_FAILURE);
    }
}

// this function checks whether the stack is empty.
template<class T> bool stack<T>::isempty(void)
{
    if (numitems > 0)
        return false;
    else
        return true;
}

// this funciton allocates memory space for the stack.
//  all the content has nothing new.
template<class T> void stack<T>::allocate(void)
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

// this funciton deallocates memory space for the stack.
//  all the content has nothing new.
template<class T> void stack<T>::deallocate(void)
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
