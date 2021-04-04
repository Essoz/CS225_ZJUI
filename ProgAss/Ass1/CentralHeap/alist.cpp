/*                                    tab:8
 *
 * alist.cpp - source file for CS225 Linked List.
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
 *    Hao BAI    2    18 January 2021
 *        Annotations added.
 *
 */

// Alist == Linearlist : Arraylist

#include <stdio.h>
#include <iostream>
#include <cstdlib>
// cstdlib is the header from <stdlib.h>
#include "alist.h"
// for those you want to include written by YOURSELF, you need to use "" for reference (instead of <>).
using std::cout;
using std::cin;
// this is consistent with <iostream>. Without the namespace, this cpp program will fail because
//  the compiler doesn't know which <iostream> it is.

template<class T> // it's suggested to write template at a separate line.
T& AList<T>::operator[](int index) // binocular operator 双目运算符
// this part is pretty important. you need to refer to the book mentioned below.
//  refer. C++ Primer Plus. [Stephen Prata 6.] Chapter 11, Program List 11.6.
{
    return reprarray[index - 1];
    // this is a bit hard to understand. according to TA Fengqing Jiang,
    //  this class is designed for those who take 1 as the first element
    //  in the array. 

    // another story is, this line
    //      T *reprarray;
    //      reprarray = new T[maxsize];
    //  will ALWAYS be excuted. 
    // reason: we've got a default value for AList, so whether we input something or not
    //  we'll always get this ctor (also, we don't have any other ctors, so this is the only one
    //  to call if we want to define an object of class AList).
    // thus, the variable reprarray is ALWAYS initialized iff the class AList is called to create
    //  an object.

    // based on all above, now let's look at this line when this operator[] is called in the main() function.
    //      double doubleitem;
    //      AList<double> mylist2;
    //      doubleitem = mylist2[i];
    // in this line we see that a variable of type double is assigned by a variable of type AList<double>[i].
    //  this means that the operator[] is used to return the inner data of the class, not the class itself.
    
}

template<class T>
int AList<T>::getlength(void) // you can also ignore "void" here too.
{
    return numitems; // this is defined in alist.h file.
    // notice that when writing functions, you need to design your header file first.
    // the according to your header file, 
}

template<class T> 
void AList<T>::setitem(int index, T value)
// another member function in AList. note that this function is not an operator, so it can certainly
//  bear 2 or more parameters delivered in.
{
    if ((index > 0) && (index <= numitems))
    {
        reprarray[index - 1] = value;
        // again, note that reprarray is of type T*, so it's nothing more than a pointer (or array).
        //  you shouln't take it as something like AList - AList is the class to hold it, but they're
        //  not of the same type.
        return;
    }
    else
        cout << "Index error: index out of range\n";
}

template<class T>
T AList<T>::getitem(int index)
// easy member function.
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
    // in case of exceeding index of array.
    if (numitems == maxsize)
        allocate();
    // add one more element AT LAST.
    // same as push_back().
    reprarray[numitems] = value;
    ++numitems;
    return;
}

template<class T> void AList<T>::insert(int index, T value)
{
    if (numitems == maxsize)
        allocate();
    if (index < numitems)
    // in this case, you want to insert at some place (but not the end).
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
    // in this case, index == numitems, i.e. you want to insert at the end.
    {
        append(value);
        return;
    }
}

template<class T> void AList<T>::allocate(void)
{
    // use double multiplication. 二乘法扩容
    int newsize = 2 * maxsize;
    // we did NOT resize AList; we resize the array inside AList.
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        // deep copy, copy from initial to last ONE BY ONE.
        newarray[i] = reprarray[i];
    }
    // remember to delete the former pointer in case of memory leak.
    delete[] reprarray;
    reprarray = newarray;
    // take on the new maxsize.
    maxsize = newsize;
    return;
}

template<class T> void AList<T>::remove(int index)
{
    // notice. minsize will not change.
    // only when the number of elements is equal to 1/4 of the capacity of the array, deallocate the array.
    if ((numitems == maxsize / 4) && (maxsize > minsize))
        deallocate();
    if (index < numitems)
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
    // cut the length of the array by 2.
    int newsize = maxsize / 2;

    // all operations below are EXACTLY the same as defined in allocate(void).
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
    // concat one AList after another AList.
    // notice. although we operate on AList, the function actually calls append() and
    //  thus it's a function operating on reprarray().
    int length = list.getlength();
    for (int i = 1; i <= length; ++i)
    {
        append(list[i]);
    }
    return;
}

template<class T> bool AList<T>::member(T value)
// this function is to check whether the value you enter is a member inside array.
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
// this function is to check whether two reprarrays are EXACTLY the same.
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
// this function is to check 
{
    int length = list.getlength();
    bool result = true;
    for (int i = 1, j = 0; (i <= length) && (j < numitems); ++i, ++j)
    {
        if (list[i] == reprarray[j])
        // a.a. if the element in list[] is the same as in reprarray[],
        {
            if ((j == numitems - 1) && (i < length))
            // a.b. if j is the last element in reprarray AND i not yet approaching the end of list[],
            {
                result = false;
                break;
            }
        }
        else
        // b.a. if the element in list[] is NOT the same as in reprarray,
            if (j == numitems - 1)
            {
                // b.b. if j reaches the end of reprarray.
                result = false;
                break;
            }
            else
                --i;
    }
    return result;
}

// IT SEEMS THAT THIS FUNCTION WILL CRASH (PERMANENT ITERATION) IN MACOS.
