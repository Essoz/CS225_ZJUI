//
//  trie.cpp
//  
//
//  Created by KD on 20.03.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "trie.h"
using std::cout;
using std::cin;

template<class T> AList<T>::AList(int size)
{
    maxsize = size;
    if (size < 20)
        minsize = size;
    else
        minsize = 20;
    numitems = 0;
    reprarray = new T[maxsize];
}

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

/* the constructor creates a node with the given value and next and follow pointers */
template<class T> trienode<T>::trienode(T item, bool l, trienode<T> *pt_next, trienode<T> *pt_follow)
{
    data = item;
    last = l;
    next = pt_next;
    follow = pt_follow;
}

/* the get operations */
template<class T> T trienode<T>::getdata(void)
{
    return data;
}

template<class T> bool trienode<T>::getlast(void)
{
    return last;
}

template<class T> trienode<T> *trienode<T>::getnext(void)
{
    return next;
}

template<class T> trienode<T> *trienode<T>::getfollow(void)
{
    return follow;
}

/* the set operations */
template<class T> void trienode<T>::setdata(T item)
{
    data = item;
    return;
}

template<class T> void trienode<T>::setlast(bool l)
{
    last = l;
    return;
}

template<class T> void trienode<T>::setnext(trienode<T> *pt_next)
{
    next = pt_next;
    return;
}

template<class T> void trienode<T>::setfollow(trienode<T> *pt_follow)
{
    follow = pt_follow;
    return;
}

/* the constructor creates an empty trie containing just a null pointer at the start */
template<class T> trie<T>::trie(void)
{
    start = 0;
}

/* the insert and intrie functions are realised recursively starting from the start using the corresponding auxiliary functions */
template<class T> void trie<T>::insert(AList<T> list)
{
    // copy the input list into a new Alist and use it as the input parameter of the function _insert
    AList<T> newlist;
    for (int i = 1; i <= list.getlength(); i++)
    {
        newlist.append(list[i]);
    }
    start = _insert(start, newlist);
    return;
}

template<class T> bool trie<T>::intrie(AList<T> list)
{
    // copy the input list into a new Alist and use it as the input parameter of the function _contains
    AList<T> newlist;
    for (int i = 1; i <= list.getlength(); i++)
    {
        newlist.append(list[i]);
    }
    return contains(start, newlist);
}
/* auxiliary function for insertion */
template<class T> trienode<T> *trie<T>::_insert(trienode<T> *pt, AList<T> list)
{
    if (list.getlength() == 0)  // empty input list, do nothing
        return 0;
    T key = list[1];  // take the first element of the new list
    if (pt == 0)  // case of null pointer: create a new trienode
    {
        list.remove(1);     // remove the first entry of the list while creating a new node
        trienode<T> *newnode = new trienode<T>;
        (*newnode).setdata(key);  // set the value of the new trienode
        /* mark the trienode as final, if the inout list is used up */
        if (list.getlength() == 0)      // The input string list is just one character
            (*newnode).setlast(true);
        /* recursively proceed with the next element of the input list */
        // continue to insert the rest of the string characters
        (*newnode).setfollow(_insert((*newnode).getfollow(), list));
        return newnode;
    }
    if ((*pt).getdata() == key) // case of a prefix already in the trie
    {
        list.remove(1);     // remove the current first entry of the list since it is already in the trie
        if (list.getlength() == 0)
        {
            (*pt).setlast(true);        // this means the input string is a substring of the trie entries
            return pt;
        }
        /* just skip over the prefix */
        // continue searching until the input list becomes empty or we meet a different character
        (*pt).setfollow(_insert((*pt).getfollow(), list));
    }
    else
        /* otherwise follow the next pointer */
        // meet a different character, you need to search or build a subentry in the trie
        (*pt).setnext(_insert((*pt).getnext(), list));
    return pt;
}

template<class T> bool trie<T>::contains(trienode<T> *pt, AList<T> list)
{
    if (list.getlength() == 0)
        return false;
    if (pt == 0)
        return false;
    T key = list[1];  // examine the first element of the input list
    if ((*pt).getdata() == key)
    {
        list.remove(1);
        /* if the input list is used up, check if the last element was marked as terminal in the trie */
        if (list.getlength() == 0)
            return (*pt).getlast();
        /* proceed recursively with the follow pointer */
        return contains((*pt).getfollow(), list);
    }
    /* otherwise follow the next pointer */
    return contains((*pt).getnext(), list);
}

template<class T> void trie<T>::display(void)
{
    AList<T> list;
    _display(start, list);
    cout << "\n";
}

template<class T> void trie<T>::_display(trienode<T> * pt, AList<T> list)
{
    if (pt != 0)
    {
        list.append((*pt).getdata());   // add the character into the new list
        if ((*pt).getlast() == true)    // meet a last node, that means we need to print a whole string in the trie
        {
            cout << "Trie entry: ";
            for (int i = 1; i <= list.getlength(); i++)
            {
                cout << list[i];
                if (i != list.getlength())
                    cout << " , ";
                else
                    cout << "\n";
            }
            if ((*pt).getfollow() != 0)     // this last node may not be the final node in this entry, we need to continue searching if it is not
                _display((*pt).getfollow(),list);
        }
        else
            _display((*pt).getfollow(), list);  // not a last node, move on the current entry
        // When reach here, that means the main entry is already printed
        list.remove(list.getlength());      // Delete the last entry in the list one by one and check if there is an subentry
        if ((*pt).getnext() != 0)           // there is! print the subentry
            _display((*pt).getnext(), list);
    }
    return;
}

// What is a substring? What is a subentry?
// e.g.
//      r - a - b - b - i - t
//          |
//          o - w
//
// If the input string is "rab" or "ro", then the insert operation is terminated at the character "b" and "o",
// meaning the two input strings are the substrings of the trie entries.
// 
// Here, "rabbit" in the trie is an "entry". And "row" is a subentry in the trie.
