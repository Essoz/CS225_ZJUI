//
//  bst.cpp
//  
//
//  Created by KD on 14.03.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "bst.h"
using std::cout;
using std::cin;

/* the constructor creates a node with the given value and left and right pointers */

template<class T> node<T>::node(T item, node<T> *left, node<T> *right)
{
    data = item;
    pt_left = left;
    pt_right = right;
}

/* the get and set operations are obvious */
template<class T> T node<T>::getdata(void)
{
    return data;
}

template<class T> node<T> *node<T>::getleft(void)
{
    return pt_left;
}

template<class T> node<T> *node<T>::getright(void)
{
    return pt_right;
}

template<class T> void node<T>::setdata(T item)
{
    data = item;
    return;
}

template<class T> void node<T>::setleft(node<T> *pt)
{
    pt_left = pt;
    return;
}

template<class T> void node<T>::setright(node<T> *pt)
{
    pt_right = pt;
    return;
}

/* the constructor contains a trivial BST containing just a null pointer at the root */
template<class T> BST<T>::BST(void)
{
    root = 0;
}

/* the insert, delete and find functions are realised recursively starting from the root using the corresponding auxiliary functions */
template<class T> void BST<T>::insert(T item)
{
    root = _insert(root, item);
    return;
}

template<class T> void BST<T>::remove(T item)
{
    root = _delete(root, item);
    return;
}

template<class T> bool BST<T>::find(T item)
{
    return _find(root, item);
}

template<class T> node<T> *BST<T>::_insert(node<T> *pt, T val)
{
    if (pt == 0)
    /*  First check, if the root of the tree (given by the pointer pt) into which the value val is to be inserted is empty.
        In this case create and return a new node with the given value val and nullpointers for left and right successors. */
    {
        node<T> *newnode = new node<T>;
        (*newnode).setdata(val);
        return newnode;
    }
    /* Otherwise, we either have to insert into the left or right successor tree. In both cases the returned pointer pt_new will become the new value of the left or right successor pointer, resp. */
    if (val < (*pt).getdata())
    {
        node<T> *pt_new;
        pt_new = _insert((*pt).getleft(), val);
        (*pt).setleft(pt_new);
    }
    else if (val > (*pt).getdata())
    {
        node<T> *pt_new;
        pt_new = _insert((*pt).getright(), val);
        (*pt).setright(pt_new);
    }
    return pt;
}

template<class T> node<T> *BST<T>::_delete(node<T> *pt, T val)
{
    /* _delete searches recursively for the node with the given value val. If a nullpointer is reached, val does not appear in the BST, so no change is made.  */
    if (pt == 0)
        return pt;
    node<T> *pt_new;
    /* If the value val is found, the left and right successor trees must be merged. The auxiliary merge function returns a pointer to the root of the merge tree. This must be returned and stored in the position (left or right) that issued the call. */
    if ((*pt).getdata() == val)
    {
        pt_new = merge((*pt).getleft(), (*pt).getright());
        return pt_new;
    }
    /* The recursive descent follows the left subtree or the right subtree. The call of _delete returns a pointer to the root of the modified tree. This must be returned and stored in the position (left or right) that issued the call.*/
    if (val < (*pt).getdata())
    {
        pt_new = _delete((*pt).getleft(), val);
        (*pt).setleft(pt_new);
    }
    else
    {
        pt_new = _delete((*pt).getright(), val);
        (*pt).setright(pt_new);
    }
    return pt;
}

/* _find works in the same way as _delete, but only a truth value is returned. */
template<class T> bool BST<T>::_find(node<T> *pt, T val)
{
    if (pt == 0)
        return false;
    if ((*pt).getdata() == val)
        return true;
    if (val < (*pt).getdata())
        return _find((*pt).getleft(), val);
    return _find((*pt).getright(), val);
}

template<class T> node<T> *BST<T>::merge(node<T> *pt1, node<T> *pt2)
{
    /* if there is no right successor tree, the left successor tree is automatically the result of the merge */
    if (pt2 == 0)
        return pt1;
    /* Otherwise, if the right successor tree has no left successor, make the given tree (pointed to by pt1) the new left successor instead of null. */
    if ((*pt2).getleft() == 0)
    {
        (*pt2).setleft(pt1);
        return pt2;
    }
    /* If the right successor (given by pointer pt2) has a non-empty left successor tree, insert the given tree (pointed to by pt1) into this left successor. */
    (*pt2).setleft(merge(pt1, (*pt2).getleft()));
    return pt2;
}

template<class T> void BST<T>::display(void)
{
    _display(root);
}

/* Iterate through the tree in order of the order < on T, i.e. first the left subtree, then the root, then the right subtree. */
template<class T> void BST<T>::_display(node<T> * pt)
{
    if (pt != 0)
    {
        _display((*pt).getleft());
        cout << (*pt).getdata() << " ; ";
        _display((*pt).getright());
    }
    return;
}
