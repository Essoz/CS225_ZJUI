//
//  avl.cpp
//  
//
//  Created by KD on 18.03.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "avl.h"
using std::cout;
using std::cin;

/* The constructor for nodes in AVL trees */
template<class T> avlnode<T>::avlnode(T item, int bal, avlnode<T> *left, avlnode<T> *right)
{
    data = item;
    balance = bal;
    pt_left = left;
    pt_right = right;
}

/* get functions on AVL tree nodes */
template<class T> T avlnode<T>::getdata(void)
{
    return data;
}

template<class T> int avlnode<T>::getbalance(void)
{
    return balance;
}

template<class T> avlnode<T> *avlnode<T>::getleft(void)
{
    return pt_left;
}

template<class T> avlnode<T> *avlnode<T>::getright(void)
{
    return pt_right;
}

/* set functions on AVL tree nodes */
template<class T> void avlnode<T>::setdata(T item)
{
    data = item;
    return;
}

template<class T> void avlnode<T>::setbalance(int bal)
{
    balance = bal;
    return;
}

template<class T> void avlnode<T>::setleft(avlnode<T> *pt)
{
    pt_left = pt;
    return;
}

template<class T> void avlnode<T>::setright(avlnode<T> *pt)
{
    pt_right = pt;
    return;
}

/* the constructor for an AVL tree simply creates an empty tree, sio root is just a null pointer */
template<class T> AVL<T>::AVL(void)
{
    root = 0;
}

/* insert, remove and find are implemented recursively using the auxiliary functions _insert, _delete and _find; the first argument poits to the root of the tree of interest */
template<class T> void AVL<T>::insert(T item)
{
    root = _insert(root, item);
    return;
}

template<class T> void AVL<T>::remove(T item)
{
    root = _delete(root, item);
    return;
}

template<class T> bool AVL<T>::find(T item)
{
    return _find(root, item);
}

/* the recurse insertion function */
template<class T> avlnode<T> *AVL<T>::_insert(avlnode<T> *pt, T val)
{
    if (pt == 0)  // if the tree is empty, we have to create a root node
    {
        avlnode<T> *newnode = new avlnode<T>;
        (*newnode).setdata(val);  // the stored value is the one given as argument
        (*newnode).setbalance(0);  // the balance must be 0
        // note that left and right pointer are 0 by default
        /* for the upward propagation of balance changes (and rotations, if necessary) we initialise the bad child and bad grandchild */
        bchild = newnode;
        bgrandchild = 0;
        /* mode indicates, if balances need to be adjusted; a value false means that we are done */
        mode = true;
        return newnode;
    }
    if (val == (*pt).getdata())
    {
        /* the first case is the do-nothing case, when the given value already occurs in the AVL tree */
        mode = false;
        return pt;
    }
    if (val < (*pt).getdata()) // the case for insertion into the left successor tree
    {
        avlnode<T> *pt_new;
        /* the recursive call returns a pointer to an updated left successor tree; it remains to adjust the balance */
        pt_new = _insert((*pt).getleft(), val);
        (*pt).setleft(pt_new);
        /* the first case is the do-nothing case; the insertiion into the left successor did not alter the height */
        if (mode == false)
            return pt;
        else
        {
            /* first compute the new balance, i.e. decrement it, as the insertion was done in the left successor tree */
            int newbal = (*pt).getbalance() - 1;
            /* if the new balance is -1, 0 or 1, only the balance needs to be updated */
            if (newbal <= 1 && newbal >= -1)
            {
                (*pt).setbalance(newbal);
                /* if the new balance is 0, no more changes further up the tree are necessary */
                if (newbal == 0)
                    mode = false;
                else
                {
                    /* otherwise, the bad child and bad grandchild need to be moved one step up the tree */
                    bgrandchild = bchild;
                    bchild = pt;
                }
                return pt;
            }
            /* this leaves the case, when the old balance was already -1;
             the first case covers the bad grandchild being the left successor of the bad child; i.e., a single right rotation is required */
            if ((*bchild).getleft() == bgrandchild)
            {
                avlnode<T> *newnode;
                /* the new balance values 0, 0 are determined by the previous analysis; a single right rotation produces these values */
                newnode = rotateright(pt, bchild, 0, 0);
                /* as the root of the new subtree has balance 0, no more balance changes are needed */
                mode = false;
                return newnode;
            }
            /* the second case covers the bad grandchild being the right successor of the bad child; i.e., a left rotation with child and grandchild followed by a right rotation with parent and the former grandchild are required */
            avlnode<T> *newnode1;
            avlnode<T> *newnode2;
            /* again, new balance values are determined by the previous analysis; a left-right rotation produces these values */
            int c = 0, n = 0;
            if (val < (*bgrandchild).getdata())
                n = 1;
            else if (val > (*bgrandchild).getdata())
                c = -1;
            newnode1 = rotateleft(bchild, bgrandchild, c, 0);
            newnode2 = rotateright(pt, newnode1, n, 0);
            /* again, as the root of the new subtree has balance 0, no more balance changes are needed */
            mode = false;
            return newnode2;
        }
    }
    else // if (val > (*pt).getdata())
        // the dual case for insertion into the right successor tree
    {
        avlnode<T> *pt_new;
        /* the recursive call returns a pointer to an updated right successor tree; it remains to adjust the balance */
        pt_new = _insert((*pt).getright(), val);
        (*pt).setright(pt_new);
        /* the first case is the do-nothing case; the insertiion into the right successor did not alter the height */
        if (mode == false)
            return pt;
        else
        {
            /* first compute the new balance, i.e. increment it, as the insertion was done in the right successor tree */
            int newbal = (*pt).getbalance() + 1;
            if (newbal <= 1 && newbal >= -1)
            /* if the new balance is -1, 0 or 1, only the balance needs to be updated */
            {
                (*pt).setbalance(newbal);
                /* if the new balance is 0, no more changes further up the tree are necessary */
                if (newbal == 0)
                    mode = false;
                else
                {
                    /* otherwise, the bad child and bad grandchild need to be moved one step up the tree */
                    bgrandchild = bchild;
                    bchild = pt;
                }
                return pt;
            }
            /* this leaves the case, when the old balance was already 1;
             the first case covers the bad grandchild being the right successor of the bad child; i.e., a single left rotation is required */
            if ((*bchild).getright() == bgrandchild)
            {
                avlnode<T> *newnode;
                /* the new balance values 0, 0 are determined by the previous analysis; a single left rotation produces these values */
                newnode = rotateleft(pt, bchild, 0, 0);
                /* as the root of the new subtree has balance 0, no more balance changes are needed */
                mode = false;
                return newnode;
            }
            /* the second case covers the bad grandchild being the left successor of the bad child; i.e., a right rotation with child and grandchild followed by a left rotation with parent and the former grandchild are required */
            avlnode<T> *newnode1;
            avlnode<T> *newnode2;
            /* again, new balance values are determined by the previous analysis; a right-left rotation produces these values */
            int c = 0, n = 0;
            if (val < (*bgrandchild).getdata())
                c = 1;
            else if (val > (*bgrandchild).getdata())
                n = -1;
            newnode1 = rotateright(bchild, bgrandchild, c, 0);
            newnode2 = rotateleft(pt, newnode1, n, 0);
            /* again, as the root of the new subtree has balance 0, no more balance changes are needed */
            mode = false;
            return newnode2;
        }
    }
}

/* the recursive delete function */
template<class T> avlnode<T> *AVL<T>::_delete(avlnode<T> *pt, T val)
{
    // nothing needs to be done for an empty tree
    if (pt == 0)
        return pt;
    /* the first case occurs, when the sought value has been found */
    if (val == (*pt).getdata())
    {
        /* in case there is no left successor tree, the result of the delete is the right successor tree */
        if ((*pt).getleft() == 0)
        {
            mode = true;
            return (*pt).getright();
        }
        /* in case there is no right successor tree, the result of the delete is the left successor tree */
        if ((*pt).getright() == 0)
        {
            mode = true;
            return (*pt).getleft();
        }
        /* if both left and right successor trees are not empty, we use the auxiliary function findswapleft to swap the value to be deleted with the maximum in the left successor tree; in addition, the node containing this maximum is deleted, and the whole left successor tree is reorganised to become again an AVL tree */
        avlnode<T> *newnode;
        newnode = findswapleft(pt, (*pt).getleft());
        (*pt).setleft(newnode);
        /* still the balance needs to be adjusted; this is done in the same as below in the recursive case covering a deletion in the left successor tree */
        if (mode == false)  // no change of height, no action required
            return pt;
        else
        {
            // compute the new balance (increment)
            int newbal = (*pt).getbalance() + 1;
            /* if the new balance is -1, 0 or 1 only the new balance needs to be stored */
            if (newbal <= 1 && newbal >= -1)
            {
                (*pt).setbalance(newbal);
                /* in addition, a new balance != 0 indicates that the height has not been altered, so no more changes are needed further up the tree */
                if (newbal != 0)
                    mode = false;
                return pt;
            }
            /* if the old balance was already 1, rotations become necessary; for these determine the bad child and bad grandchild in the right successor tree */
            bchild = (*pt).getright();
            /* if the bad child had balance 0, only a single left rotation is needed */
            if ((*bchild).getbalance() == 0)
            {
                avlnode<T> *newnode;
                /* the new balance values are those that must result from such a single left rotation */
                newnode = rotateleft(pt, bchild, 1, -1);
                /* as the root of the new subtree has balance !=0, the height has not been altered, so no changes are need further up the tree indicated by mode */
                mode = false;
                return newnode;
            }
            /* also, if the bad child had balance 1, only a single left rotation is needed */
            if ((*bchild).getbalance() == 1)
            {
                avlnode<T> *newnode;
                /* the new balance values are those that must result from such a single left rotation */
                newnode = rotateleft(pt, bchild, 0, 0);
                /* in this case the new subtree has balance 0, so the height has been altered; further changes are needed further up the tree */
                return newnode;
            }
            /* the remaining case concerns a bad child with balance -1; in this case a right rotation followed by a left rotation are needed */
            bgrandchild = (*bchild).getleft();
            avlnode<T> *newnode1;
            avlnode<T> *newnode2;
            /* the new balance values are those that must result from such a left-right rotation */
            int c = 0, n = 0;
            if ((*bgrandchild).getbalance() == 1)
                n = -1;
            if ((*bgrandchild).getbalance() == -1)
                c = 1;
            newnode1 = rotateright(bchild, bgrandchild, c, 0);
            newnode2 = rotateleft(pt, newnode1, n, 0);
            /* in this case also the new subtree has balance 0, so the height has been altered; further changes are needed further up the tree */
            return newnode2;
        }
    }
    /* as long as the sought value has not been found a recursive descent is required; the first case continues the search in the left successor tree */
    if (val < (*pt).getdata())
    {
        avlnode<T> *pt_new;
        /* the recursive call returns an updated left successor tree, in which the sought value (if in there) has been deleted */
        pt_new = _delete((*pt).getleft(), val);
        (*pt).setleft(pt_new);
        /* mode indicates, if balance adjustments are still needed; the first case is the no-action case */
        if (mode == false)
            return pt;
        else
        {
            /* otherwise, first compute the new balance (increment) */
            int newbal = (*pt).getbalance() + 1;
            /* if the new balance is -1, 0 or 1 only the new balance needs to be stored */
            if (newbal <= 1 && newbal >= -1)
            {
                (*pt).setbalance(newbal);
                /* in addition, a new balance != 0 indicates that the height has not been altered, so no more changes are needed further up the tree */
                if (newbal != 0)
                    mode = false;
                return pt;
            }
            /* if the old balance was already 1, rotations become necessary; for these determine the bad child and bad grandchild in the right successor tree */
            bchild = (*pt).getright();
            /* if the bad child had balance 0, only a single left rotation is needed */
            if ((*bchild).getbalance() == 0)
            {
                avlnode<T> *newnode;
                /* the new balance values are those that must result from such a single left rotation */
                newnode = rotateleft(pt, bchild, 1, -1);
                /* as the root of the new subtree has balance !=0, the height has not been altered, so no changes are needed further up the tree indicated by mode */
                mode = false;
                return newnode;
            }
            /* also, if the bad child had balance 1, only a single left rotation is needed */
            if ((*bchild).getbalance() == 1)
            {
                avlnode<T> *newnode;
                /* the new balance values are those that must result from such a single left rotation */
                newnode = rotateleft(pt, bchild, 0, 0);
                /* in this case the new subtree has balance 0, so the height has been altered; further changes are needed further up the tree */
                return newnode;
            }
            /* the remaining case concerns a bad child with balance -1; in this case a right rotation followed by a left rotation are needed */
            bgrandchild = (*bchild).getleft();
            avlnode<T> *newnode1;
            avlnode<T> *newnode2;
            /* the new balance values are those that must result from such a left-right rotation */
            int c = 0, n = 0;
            if ((*bgrandchild).getbalance() == 1)
                n = -1;
            if ((*bgrandchild).getbalance() == -1)
                c = 1;
            newnode1 = rotateright(bchild, bgrandchild, c, 0);
            newnode2 = rotateleft(pt, newnode1, n, 0);
            /* in this case also the new subtree has balance 0, so the height has been altered; further changes are needed further up the tree */
            return newnode2;
        }
    }
    /* the second case continues the search in the right successor tree */
    else // if (val > (*pt).getdata())
    {
        avlnode<T> *pt_new;
        /* the recursive call returns an updated right successor tree, in which the sought value (if in there) has been deleted */
        pt_new = _delete((*pt).getright(), val);
        (*pt).setright(pt_new);
        /* mode indicates, if balance adjustments are still needed; the first case is the no-action case */
        if (mode == false)
            return pt;
        else
        /* otherwise, first compute the new balance (decrement) */
        {
            int newbal = (*pt).getbalance() - 1;
            /* if the new balance is -1, 0 or 1 only the new balance needs to be stored */
            if (newbal <= 1 && newbal >= -1)
            {
                (*pt).setbalance(newbal);
                /* in addition, a new balance != 0 indicates that the height has not been altered, so no more changes are needed further up the tree */
                if (newbal != 0)
                    mode = false;
                return pt;
            }
            /* if the old balance was already -1, rotations become necessary; for these determine the bad child and bad grandchild in the left successor tree */
            bchild = (*pt).getleft();
            /* if the bad child had balance 0, only a single right rotation is needed */
            if ((*bchild).getbalance() == 0)
            {
                avlnode<T> *newnode;
                /* the new balance values are those that must result from such a single right rotation */
                newnode = rotateright(pt, bchild, -1, 1);
                /* as the root of the new subtree has balance !=0, the height has not been altered, so no changes are needed further up the tree indicated by mode */
                mode = false;
                return newnode;
            }
            /* also, if the bad child had balance -1, only a single right rotation is needed */
            if ((*bchild).getbalance() == -1)
            {
                avlnode<T> *newnode;
                /* the new balance values are those that must result from such a single right rotation */
                newnode = rotateright(pt, bchild, 0, 0);
                /* in this case the new subtree has balance 0, so the height has been altered; further changes are needed further up the tree */
                return newnode;
            }
            /* the remaining case concerns a bad child with balance 1; in this case a left rotation followed by a right rotation are needed */
            bgrandchild = (*bchild).getright();
            avlnode<T> *newnode1;
            avlnode<T> *newnode2;
            /* the new balance values are those that must result from such a right-left rotation */
            int c = 0, n = 0;
            if ((*bgrandchild).getbalance() == 1)
                c = -1;
            if ((*bgrandchild).getbalance() == -1)
                n = 1;
            newnode1 = rotateleft(bchild, bgrandchild, c, 0);
            newnode2 = rotateright(pt, newnode1, n, 0);
            /* in this case also the new subtree has balance 0, so the height has been altered; further changes are needed further up the tree */
            return newnode2;
        }
    }
}

/* auxiliary recursive function searching for the maximum in the (non-empty) left successor tree with follow-on swap, deletion of the found node and reorganisation of the tree; pt_swap points to the node to which the maximum neds to be moved; here points to the root of the tree, in which the search is conducted */
template<class T> avlnode<T> *AVL<T>::findswapleft(avlnode<T> *pt_swap, avlnode<T> *here)
{
    /* if there is no right successor tree, the node with the maximum value has been found */
    if ((*here).getright() == 0)
    {
        /* move the found maximum into the node given by the first argument */
        (*pt_swap).setdata((*here).getdata());
        /* along the path leading down to the node, in which the maximum was found, balances need to be adjusted; rotations may become necessary*/
        mode = true;
        /* the node itself is deleted, i.e. replaced by the root of its left successor tree */
        return (*here).getleft();
    }
    avlnode<T> *pt_new;
    /* if the maximum has not yet been found, the search continues recursively; the recursive call returns the pointer to the root of the updated subtree, in which the maximum was found and removed */
    pt_new = findswapleft(pt_swap, (*here).getright());
    (*here).setright(pt_new);
    /* the no-section case, if the height of the updated subtree remained unchanged */
    if (mode == false)
        return here;
    else
        /* for balance adjustment we proceed as in the _delete function for the case of a delete in the left successor tree */
    {
        /* get the new balance (decrement) */
        int newbal = (*here).getbalance() - 1;
        /* if the new balance is -1, 0 or 1 only the new balance needs to be stored */
        if (newbal <= 1 && newbal >= -1)
        {
            (*here).setbalance(newbal);
            /* in addition, a new balance != 0 indicates that the height has not been altered, so no more changes are needed further up the tree */
            if (newbal != 0)
                mode = false;
            return here;
        }
        /* if the old balance was already -1, rotations become necessary; for these determine the bad child and bad grandchild in the left successor tree */
        bchild = (*here).getleft();
        /* if the bad child had balance 0, only a single right rotation is needed */
        if ((*bchild).getbalance() == 0)
        {
            avlnode<T> *newnode;
            newnode = rotateright(here, bchild, -1, 1);
            /* as the root of the new subtree has balance !=0, the height has not been altered, so no changes are needed further up the tree indicated by mode */
            mode = false;
            return newnode;
        }
        /* also, if the bad child had balance -1, only a single right rotation is needed */
        if ((*bchild).getbalance() == -1)
        {
            avlnode<T> *newnode;
            newnode = rotateright(here, bchild, 0, 0);
            /* in this case the new subtree has balance 0, so the height has been altered; further changes are needed further up the tree */
            return newnode;
        }
        /* the remaining case concerns a bad child with balance 1; in this case a left rotation followed by a right rotation are needed */
        bgrandchild = (*bchild).getright();
        avlnode<T> *newnode1;
        avlnode<T> *newnode2;
        int c = 0, n = 0;
        if ((*bgrandchild).getbalance() == 1)
            c = -1;
        if ((*bgrandchild).getbalance() == -1)
            n = 1;
        newnode1 = rotateleft(bchild, bgrandchild, c, 0);
        newnode2 = rotateright(here, newnode1, n, 0);
        /* in this case also the new subtree has balance 0, so the height has been altered; further changes are needed further up the tree */
        return newnode2;
    }
}

/* the auxiliary recursive _find function is the same as for BST */
template<class T> bool AVL<T>::_find(avlnode<T> *pt, T val)
{
    /* search in an empty tree leads to false */
    if (pt == 0)
        return false;
    /* if the value is found, true is returned */
    if ((*pt).getdata() == val)
        return true;
    /* proceed with the search in the left successor tree */
    if (val < (*pt).getdata())
        return _find((*pt).getleft(), val);
    /* proceed with the search in the right successor tree */
    return _find((*pt).getright(), val);
}

/* single left rotation */
template<class T> avlnode<T> *AVL<T>::rotateleft(avlnode<T> *parent, avlnode<T> *child, int pbal, int cbal)
{
    (*parent).setright((*child).getleft());
    (*parent).setbalance(pbal);
    (*child).setleft(parent);
    (*child).setbalance(cbal);
    return child;
}

/* single right rotation */
template<class T> avlnode<T> *AVL<T>::rotateright(avlnode<T> *parent, avlnode<T> *child, int pbal, int cbal)
{
    (*parent).setleft((*child).getright());
    (*parent).setbalance(pbal);
    (*child).setright(parent);
    (*child).setbalance(cbal);
    return child;
}

template<class T> void AVL<T>::display(void)
{
    cout << "\nAVL Tree\n\n";
    _display(root);
    cout << "\n\n";
}

/* Iterate through the tree in order of the order < on T, i.e. first the left subtree, then the root, then the right subtree. */
template<class T> void AVL<T>::_display(avlnode<T> * pt)
{
    if (pt != 0)
    {
        _display((*pt).getleft());
        cout << "Node:\n";
        cout << "Value: " << (*pt).getdata() << "\n";
        cout << "Balance: " << (*pt).getbalance() << "\n";
        avlnode<T> *pt_l;
        pt_l = (*pt).getleft();
        if (pt_l != 0)
            cout << "Left: " << pt_l << " with value " << (*pt_l).getdata() << "\n";
        else cout << "Left: Null\n";
        avlnode<T> *pt_r;
        pt_r = (*pt).getright();
        if (pt_r != 0)
            cout << "Right: " << pt_r << " with value " << (*pt_r).getdata() << "\n";
        else cout << "Right: Null\n";
        cout << "----\n";
        _display((*pt).getright());
    }
    return;
}
