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
 *    Klaus-Dieter Schewe    1    14 January 2021
 *        First written.
 *    Hao BAI    2    22 January 2021
 *        Annotations added.
 *
 */

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "fifo.h"
using std::cout;
using std::cin;

template<class T> fifo<T>::fifo(int size)
{
    maxsize = size;
    if (size < 10)
        minsize = size;
    else
        minsize = 10;

    // at first, the number of items is 0. nothing is in the fifo.
    numitems = 0;
    // at first, the first element should be the 0 index in the array.
    first = 0;
    // at first, the last element should be the -1 index in the array.
    //  actually, the stack used to use this kind of nonations too, but it seems that
    //  KD doesn't want to use that.
    last = -1;
    reprarray = new T[maxsize];
}

//template<class T> fifo<T>::~fifo()
//{
//    delete[] *reprarray;
//}

template<class T> T &fifo<T>::operator[](int index)
{
    if ((1 <= index) && (index <= numitems))
    {
        // note that something like "%" means you want to make a loop.
        //  still, it's inevitable to -1 at last, because KD makes the array to be 0-first.
        int relindex = (index + first -1) % maxsize;
        // the index is now arranged into a loop.
        return reprarray[relindex];
    }
    else
    {
        cout << "Error: index " << index << " out of range.\n";
        exit(EXIT_FAILURE);
    }
}

// easy.
template<class T> int fifo<T>::getlength(void)
{
    return numitems;
}

// easy.
template<class T> bool fifo<T>::isempty(void)
{
    if (numitems == 0)
        return true;
    else
        return false;
}

// this is to get the front element of the fifo.
template<class T> T fifo<T>::front(void)
{
    if (isempty() == false)
        return reprarray[first];
    else
    {
        cout << "The queue is empty.\n";
        exit(EXIT_FAILURE);
    }
}

// this is to get the back element of the fifo. note that you should always consider the edge case.
//  in this case, relindex is the back of the fifo.
template<class T> T fifo<T>::back(void)
{
    if (isempty() == false)
    {
        int relindex = (first + numitems - 1) % maxsize;
        return reprarray[relindex];
    }
    else
    {
        cout << "The queue is empty.\n";
        exit(EXIT_FAILURE);
    }
}

// you can ONLY push into the back.
template<class T> void fifo<T>::pushback(T value)
{
    if (numitems == maxsize)
        allocate();
    last = ++last % maxsize;
    reprarray[last] = value;
    ++numitems;
    return;
}

// you can ONLY pop out of the front.
template<class T> T fifo<T>::popfront(void)
{
    if ((numitems == maxsize / 4) && (maxsize > minsize))
        deallocate();
    if (isempty() == false)
    {
        T frontelement = reprarray[first];
        first = ++first % maxsize;
        --numitems;
        return frontelement;
    }
    else
    {
        cout << "The queue is empty.\n";
        exit(EXIT_FAILURE);
    }
}

// allocate space.
template<class T> void fifo<T>::allocate(void)
{
    int newsize = 2 * maxsize;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        int pos = (i + first) % maxsize;
        newarray[i] = reprarray[pos];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    first = 0;
    last = numitems -1;
    return;
}

// deallocate space.
template<class T> void fifo<T>::deallocate(void)
{
    int newsize = maxsize / 2;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        int pos = (i + first) % maxsize;
        newarray[i] = reprarray[pos];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    first = 0;
    last = numitems -1;
    return;
}
