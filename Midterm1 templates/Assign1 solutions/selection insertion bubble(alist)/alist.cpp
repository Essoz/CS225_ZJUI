//
//  alist.cpp
//  
//
//  Created by KD on 14.01.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "alist.h"
using std::cout;
using std::cin;
using std::endl;

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

// Exercise 4
// Created by Xiong Neng on 21.01.21

// This function displays the list
template<class T> void AList<T>::print(void){
    for (int i = 0; i < numitems; i++){
        cout << ' ' << reprarray[i];
    }
    cout << endl;
}

// Helper binary search function
// Return the index of the first element in range [start,end] that is smaller than value
template<class T> int AList<T>::bSearch(int start, int end, T value){
    start -= 1;
    end -= 1;
    int middle, half, len;
    len = end - start + 1;

    while(len > 0) {
        half = len >> 1;
        middle = start + half;
        if(reprarray[middle] < value) {
            start = middle + 1;
            len = len-half-1;
        }
        else
            len = half;
    }
    return start;
}

// The swap function needed for sorting algorithm
template<class T> void AList<T>::swap(int i, int j){
    T *temp = new(T);
    // using i-1, j-1 since the index of AList is starting from 1
    *temp = reprarray[i-1];
    reprarray[i-1] = reprarray[j-1];
    reprarray[j-1] = *temp;
}

template<class T> void AList<T>::SelectionSort(void){
    // We can swap the minimal element to the front so that in&out lists are one
    // loop through n-1 swaps
    for (int i = 1; i < numitems; i++){
        int minimal = i-1;
        // loop through unsorted part to find the minimal
        for (int j = i; j < numitems; j++){
            minimal = (reprarray[j] < reprarray[minimal]) ? j : minimal;
        }
        // swap the minimal element in the unsorted part to the front
        swap(i, minimal+1);
    }
}

template<class T> void AList<T>::InsertionSort(void){
    // loop through n-1 needed insertions
    for (int i = 1; i < numitems; i++){
        // without using binary search
        // for (int j = 0; j < i+1; j++){
        //     if (reprarray[j] >= reprarray[i]){
        //         insert(j,reprarray[i]);
        //         remove(i+2);
        //         break;
        //     }

        // using binary search
        insert(bSearch(1, i,reprarray[i]),reprarray[i]);
        remove(i+2);
    }
}


template<class T> void AList<T>::BubbleSort(void){
    for(int i = 0;i<numitems;i++){
        for(int j =1;j<numitems-i;++j){
            if(reprarray[j-1]>reprarray[j]) swap(j,j+1);
        }
    }
}
