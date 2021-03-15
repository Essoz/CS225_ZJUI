//
//  alist.cpp
//  
//
//  Created by KD on 14.01.21.
//  Modified by KD on 23.01.21.
//  Modified by HB on 18.02.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "alistradix.h"
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


/* bubble sort (too easy so few annotations are added)
 * input:
 *  none.
 * output:
 *  none.
 * side-effects:
 *  use bubble sort to sort the array.
 */
template<class T> void AListsort<T>::bsort(void)
{
    // initialization & localization
    int numitems = AList<T>::numitems;
    T *reprarray;
    reprarray = AList<T>:: reprarray;

    // traditional bubble sort algorithm.
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

/******************* QUICKSORT is an advanced version of BUBBLESORT *******************/

/* quick sort based on Monte Carlo Method.
 * input:
 *  the threshold, thr.
 * output:
 *  none.
 * side-effects:
 *  when numitem is small, use bubblesort immediately;
 *  when numitem is large, use quicksort recursively
 */
template<class T> void AListsort<T>::qsort(int thr)
{
    // initialization and localization
    int numitems = AList<T>::numitems;
    T *reprarray;
    reprarray = AList<T>:: reprarray;

    // forcely range threshold into [20,100].
    if (thr < 20)
        thr = 20;
    if (thr > 100)
        thr = 100;

    // when access threshold, use bsort() immediately.
    if (numitems <= thr)
    {
        bsort();
        return;
    }

    // when not access threshold, perform as below:
    else
    {
        // set the Seed of RANDom number for rand()
        srand(time(0));

        // settle the random number inside the range [0, numitems - 1]
        int index = rand() % numitems;

        // define the pivot of quick sort (randomly, because it uses (index) )
        T pivot = reprarray[index];

        // create AList of size 10
        AListsort<T> lsmall = AListsort<T>(10);

        // create AList of size 5
        AListsort<T> lpivot = AListsort<T>(5);

        // create AList of size 10
        AListsort<T> llarge = AListsort<T>(10);

        // iterate through all the elements
        for (int i = 0; i < numitems; ++i)
        {
            // if the element is smaller than the chosen pivot
            if (reprarray[i] < pivot)

                // the AList used to store smaller elements is appended by this element
                lsmall.append(reprarray[i]);

            // if the element is equal the chosen pivot
            else if (reprarray[i] == pivot)

                // the AList used to store the same elements is appended by this element
                //  e.g. pivot == 5, then all elements == 5 will be stored into lpivot
                lpivot.append(reprarray[i]);

            // if the element is larger than the chosen pivot
            else

                // the AList used to store larger elements is appended by this element
                llarge.append(reprarray[i]);
        }

        // up to now, all detections are ended

        // use quicksort to sort the small and large ALists with the threshold again iterately
        lsmall.qsort(thr);
        llarge.qsort(thr);

        // iterate through all the elements AGAIN
        for (int i = 0; i < numitems; ++i)
        {
            // if the INDEX of selected element is in [0, lsmall_LENGTH]
            if (i < lsmall.getlength())

                // throw the selected element into the AList with smaller elements
                reprarray[i] = lsmall.getitem(i+1);

            // if the INDEX of selected element is in [lsmall_LENGTH, lsmall_LENGTH + lpivot_LENGTH]
            else if (i < (lsmall.getlength() + lpivot.getlength()))
                
                // throw the selected element into the AList with equal magnitude elements
                reprarray[i] = lpivot.getitem(i - lsmall.getlength() + 1);

            // if the INDEX of selected element is in [lsmall_LENGTH + lpivot_LENGTH, END]
            else
                // throw the selected element into the AList with larger magnitude elements
                reprarray[i] = llarge.getitem(i - lsmall.getlength() - lpivot.getlength() + 1);
        }
        return;
    }
}

/* Radix Sort
 * input:
 *  the number of buckets you want to divide into, K.
 * output:
 *  none.
 * side-effects:
 *  use radix sort to sort the given array reprarray[].
 */
template<class T> void AListrsort<T>::radixsort(int K)
{
    // range K into [2, 16]
    if (K < 2)
        K = 2;
    if (K > 16)
        K = 16;

    // initialization & localization
    int numitems = AList<T>::numitems;
    T *reprarray;
    reprarray = AList<T>::reprarray;

    // define the maximum distance from the minimum key to the maximum key
    int max = maxkey() - minkey();

    // initialization
    int numdigits = 1;
    int power = K;

    // iterate to find the best value for power and numdigits
    while (max >= power)
    {
        power = power * K;
        ++numdigits;
    }

    // for each digit
    for (int i = 0; i < numdigits; ++i)
    {
        // call bucket sort
        ksort(K, i);
    }
    return;
}

/* find the max value.
 * input:
 *  none.
 * output:
 *  none.
 * side-effects:
 *  find the maximum value in the whole array.
 */
template<class T> int AListrsort<T>::maxkey(void)
{
    // initialization and localization
    int numitems = AList<T>::numitems;
    T *reprarray;
    reprarray = AList<T>::reprarray;
    int result = 0;
    int key = 0;

    // find the element with the maximum value, call this VALUE (not index) key.
    for (int i = 0; i < numitems; ++i)
    {
        key = reprarray[i];
        if (key > result)
            result = key;
    }
    return result;
}

/* find the min value.
 * input:
 *  none.
 * output:
 *  none.
 * side-effects:
 *  find the minimum value in the whole array.
 */
template<class T> int AListrsort<T>::minkey(void)
{
    // initialization and localization
    int numitems = AList<T>::numitems;
    T *reprarray;
    reprarray = AList<T>::reprarray;
    int result = 0;
    int key = 0;

    // find the element with the minimum value, call this VALUE (not index) key.
    for (int i = 0; i < numitems; ++i)
    {
        key = reprarray[i];
        if (key < result)
            result = key;
    }
    return result;
}

/* ksort.
 * input:
 *  the number of buckets you want to divide all the elements into, K,
 *  the current digit you are performing on, d.
 * output:
 *  none.
 * side-effects:
 *  
 */
template<class T> void AListrsort<T>::ksort(int K, int d)
{
    // initialization and localization
    int numitems = AList<T>::numitems;
    T *reprarray;
    reprarray = AList<T>::reprarray;
    int key, bucketnumber;

    // pow(a,b) means a^b in math.
    // define p = K^d
    int p = pow(K,d);

    // create K buckets
    AList<T>* bucket[K];

    // iterate through K
    for (int i = 0; i < K; ++i)
    {
        // create an AList inside each bucket
        bucket[i] = new AList<T>;
    }

    // iterate all elements in the array
    for (int j = 0; j < numitems; ++j)
    {
        // define key to be difference of the current element and the minimum element
        key = reprarray[j] - minkey();

        // define the number of bucket
        bucketnumber = (key / p) % K;

        // append the number after the according AList inside the bucket
        (*bucket[bucketnumber]).append(reprarray[j]);
    }

    // initialization for rearranging
    int offset = 0;
    int count = 0;

    // for all elements in the array, put them back into the initial array one by one
    for (int i = 0; i < numitems; ++i)
    {
        if ((i - count) == (*bucket[offset]).getlength())
        {
            count += (*bucket[offset]).getlength();
            ++offset;
        }
        // put the element back into the given array
        reprarray[i] = (*bucket[offset]).getitem(i - count + 1);
    }
    return;
}
