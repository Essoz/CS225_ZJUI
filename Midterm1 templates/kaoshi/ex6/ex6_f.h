#include "ex6.h"
using std::cout;
using std::cin;
using std::endl;
template<class T> fifo<T>::fifo(int size)
{
    maxsize = size;
    if (size < 10)
        minsize = size;
    else
        minsize = 10;
    numitems = 0;
    first = 0;
    last = -1;
    reprarray = new pair<T>[maxsize];
}

template<class T> fifo<T>::~fifo()
{
   delete[] reprarray;
}

template<class T> pair<T> &fifo<T>::operator[](int index)
{
    if ((1 <= index) && (index <= numitems))
    {
        int relindex = (index + first -1) % maxsize;
        return reprarray[relindex];
    }
    else
    {
        cout << "Error: index " << index << " out of range.\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> int fifo<T>::getlength(void)
{
    return numitems;
}

template<class T> bool fifo<T>::isempty(void)
{
    if (numitems == 0)
        return true;
    else
        return false;
}

template<class T> pair<T> fifo<T>::front(void)
{
    if (isempty() == false)
        return reprarray[first];
    else
    {
        cout << "The queue is empty.\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> pair<T> fifo<T>::back(void)
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

template<class T> void fifo<T>::pushback(pair<T> value)
{
    if (numitems == maxsize)
        allocate();
    last = last + 1;
    last = last % maxsize;
    // last = ++last % maxsize;
    reprarray[last] = value;
    ++numitems;
    return;
}

template<class T> pair<T> fifo<T>::popfront(void)
{
    if ((numitems == maxsize / 4) && (maxsize > minsize))
        deallocate();
    if (isempty() == false)
    {
        pair<T> frontelement = reprarray[first];
        first = first + 1;
        first = first % maxsize;
        // first = ++first % maxsize;
        --numitems;
        return frontelement;
    }
    else
    {
        cout << "The queue is empty.\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> void fifo<T>::allocate(void)
{
    int newsize = 2 * maxsize;
    pair<T> *newarray = new pair<T>[newsize];
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

template<class T> void fifo<T>::deallocate(void)
{
    int newsize = maxsize / 2;
    pair<T> *newarray = new pair<T>[newsize];
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


template<class T> void pair<T>::print_pairs(){
    cout << "(" << this->pair_t << "," << this->pair_n << ")" << endl;
}



