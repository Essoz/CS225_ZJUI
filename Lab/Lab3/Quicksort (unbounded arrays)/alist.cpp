//
//  alist.cpp
//  
//
//  Created by KD on 14.01.21.
//  Modified by KD on 22.01.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "alist.h"
#include "time.h"
using std::cout;
using std::cin;
using std::rand;
using std::srand;

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

template<class T> void AListsort<T>::bsort(void)
{
    int numitems = AList<T>::numitems;
    T *reprarray;
    reprarray = AList<T>:: reprarray;
    for (int i = 0; i < numitems - 1; ++i)
    {
        for (int j = i+1; j < numitems; ++j)
        {
            if (reprarray[i] > reprarray[j])
            {
                T temp;
                temp = reprarray[i];
                reprarray[i] = reprarray[j];
                reprarray[j] = temp;
            }
        }
    }
    return;
}

template<class T> void AListsort<T>::qsort(int thr)
{
    int numitems = AList<T>::numitems;
    T *reprarray;
    reprarray = AList<T>:: reprarray;
    if (thr < 20)
        thr = 20;
    if (thr > 100)
        thr = 100;
    if (numitems <= thr)
    {
        bsort();
        return;
    }
    else
    {
        srand(time(0));
        int index = rand() % numitems;
        T pivot = reprarray[index];
        AListsort<T> lsmall = AListsort<T>(10);
        AListsort<T> lpivot = AListsort<T>(5);
        AListsort<T> llarge = AListsort<T>(10);
        for (int i = 0; i < numitems; ++i)
        {
            if (reprarray[i] < pivot)
                lsmall.append(reprarray[i]);
            else if (reprarray[i] == pivot)
                lpivot.append(reprarray[i]);
            else
                llarge.append(reprarray[i]);
        }
        lsmall.qsort(thr);
        llarge.qsort(thr);
        for (int i = 0; i < numitems; ++i)
        {
            if (i < lsmall.getlength())
                reprarray[i] = lsmall.getitem(i+1);
            else if (i < (lsmall.getlength() + lpivot.getlength()))
                reprarray[i] = lpivot.getitem(i - lsmall.getlength() + 1);
            else
                reprarray[i] = llarge.getitem(i - lsmall.getlength() - lpivot.getlength() + 1);
        }
        return;
    }
}
