//
//  graphtraversal.cpp
//  
//
//  Created by KD on 12.04.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "graphtraversal.h"
#include "time.h"
using std::cout;
using std::cin;
using std::rand;
using std::srand;

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
    reprarray = new T[maxsize];
}

template<class T> T &fifo<T>::operator[](int index)
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

template<class T> void fifo<T>::pushback(T value)
{
    if (numitems == maxsize)
        allocate();
    last = ++last % maxsize;
    reprarray[last] = value;
    ++numitems;
    return;
}

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

/* The structure of a vertex is analogous to a node in a doubly linked list. In addition we keep an "edgelist" with each vertex, i.e. the list of neighbour vertices. */
template<class T> vertex<T>::vertex(T item, vertex<T> *pt_next, vertex<T> *pt_prev)
{
    vertexid = item;
    next = pt_next;
    previous = pt_prev;
    edgelist = 0;
}

template<class T> int vertex<T>::numoutedges(void)
{
    if (edgelist != 0)
        return (*edgelist).getlength();
    return 0;
}

template<class T> T vertex<T>::getitem(void)
{
    return vertexid;
}

template<class T> vertex<T> * vertex<T>::getnext(void)
{
    return next;
}

template<class T> vertex<T> * vertex<T>::getprevious(void)
{
    return previous;
}

template<class T> elist<T> * vertex<T>::getedges(void)
{
    return edgelist;
}

template<class T> void vertex<T>::setitem(T item)
{
    vertexid = item;
    return;
}

template<class T> void vertex<T>::setnext(vertex<T> *pt_next)
{
    next = pt_next;
    return;
}

template<class T> void vertex<T>::setprevious(vertex<T> *pt_prev)
{
    previous = pt_prev;
    return;
}

template<class T> void vertex<T>::setedges(elist<T> *pt_edges)
{
    edgelist = pt_edges;
    return;
}

/* A vertexlist is a doubly linked list with vertices and a dummy node. */
template<class T> vertexlist<T>::vertexlist(void)
{
    dummy = new vertex<T>;
    (*dummy).setnext(dummy);
    (*dummy).setprevious(dummy);
    numvertices = 0;
}

template<class T> int vertexlist<T>::getlength(void)
{
    return numvertices;
}

/* For counting edges we must add up the counts of outgoing edges for each vertex */
template<class T> int vertexlist<T>::countedges(void)
{
    int count = 0;
    vertex<T> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        count = count + (*pt).numoutedges();
        pt = (*pt).getnext();
    }
    return count;
}

/* append is analogous to linked lists, i.e. we add a new vertex at the end and adjust pointers. */
template<class T> void vertexlist<T>::append(T item)
{
    vertex<T> * pt_last = (*dummy).getprevious();
    vertex<T> * pt_new = new vertex<T>;
    (*pt_new).setitem(item);
    (*pt_new).setnext(dummy);
    (*pt_new).setprevious(pt_last);
    (*dummy).setprevious(pt_new);
    (*pt_last).setnext(pt_new);
    ++numvertices;
    return;
}

/* A new vertex is only added, if it is not yet in the list. */
template<class T> void vertexlist<T>::addvertex(T item)
{
    if (contains(item) == false)
        append(item);
    return;
}

/* To check if a vertex is already in the list the list is scanned until the element is found. */
template<class T> bool vertexlist<T>::contains(T item)
{
    bool result = false;
    vertex<T> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == item)
        {
            result = true;
            break;
        }
        else
            pt = (*pt).getnext();
    }
    return result;
}

/* In order to remove a vertex we have to find it in the list of vertices. If it has a non-empty list of neighbours, it cannot be deleted. It cannot be deleted, if it appwars in any edgelist. */
template<class T> bool vertexlist<T>::remove(T item)
{
    bool result = false;
    vertex<T> * location = 0;
    vertex<T> *pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == item)
        {
            if ((*pt).getedges() != 0)
            {
                cout << "The vertex " << item << " cannot be deleted, as it appears in an edge.\n";
                return result;
            }
            /* We may be able to delete the vertex at location pt, but we still have to check other edgelists. Therefore pt is stored in location. */
            location = pt;
            continue;
        }
        elist<T> * edges = (*pt).getedges();
        if (edges != 0 && (*edges).contains(item) == true)
            /* it is appears in an edgelist, there is no delete. */
        {
            cout << "The vertex " << item << " cannot be deleted, as it appears in an edge.\n";
            return result;
        }
        pt = (*pt).getnext();
    }
    /* Finally, we get to the deletion from the veertexlist. */
    if (location != 0)
    {
        result = true;
        vertex<T> * pt_prev = (*location).getprevious();
        vertex<T> * pt_next = (*location).getnext();
        (*pt_prev).setnext(pt_next);
        (*pt_next).setprevious(pt_prev);
        --numvertices;
    }
    /* The returned Boolean result indicates, if the vertex was deleted or not. */
    return result;
}

/* Adding an edge is done by first locating the origin vertex in the vertex list, then inserting the destination vertex into the associated edgelist. */
template<class T> void vertexlist<T>::addedge(T first, T second)
{
    vertex<T> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == first)
        {
            elist<T> * pt_edges = (*pt).getedges();
            if (pt_edges != 0)
                (*pt_edges).addvertex(second);
            else
            {
                elist<T> * newlist = new elist<T>(second);
                (*pt).setedges(newlist);
            }
            return;
        }
        pt = (*pt).getnext();
    }
    /* If the origin vertex is not yet in the vertex list, it is first appended to the vertex list. The associated edgelist contains a single vertex. */
    append(first);
    pt = (*dummy).getprevious();
    elist<T> * newlist = new elist<T>(second);
    (*pt).setedges(newlist);
    return;
}

/* Removing an edge is done by first locating the origin vertex in the vertex list, then searching for the destination vertex into the associated edgelist. In this case the edge is always deleted, if it is found. */
template<class T> void vertexlist<T>::removeedge(T first, T second)
{
    vertex<T> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == first)
        {
            elist<T> * pt_edges = (*pt).getedges();
            if (pt_edges != 0)
            {
                (*pt_edges).remove(second);
                if ((*pt_edges).getlength() == 0)
                    (*pt).setedges(0);
            }
            return;
        }
        pt = (*pt).getnext();
    }
    return;
}

template<class T> elist<T> * vertexlist<T>::edges(T node)
{
    vertex<T> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == node)
            return (*pt).getedges();
        pt = (*pt).getnext();
    }
    return 0;
}

/* To build list of outgoing edges for a given vertex, a new edge sequence is created for the output, then by scanning the associated edgelist edges (pairs of vertices) are added one by one. */
template<class T> edgelist<T> * vertexlist<T>::outgoingedges(T item)
{
    edgelist<T> * result = new edgelist<T>;
    vertex<T> * ptv = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*ptv).getitem() == item)
        {
            elist<T> * edges = (*ptv).getedges();
            if (edges != 0)
                (*edges).addall(item, result);
            return result;
        }
        ptv = (*ptv).getnext();
    }
    return result;
}

/* only for testing */
template<class T> void vertexlist<T>::prettyprint(void)
{
    vertex<T> *ptv = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        cout << "Edges with origin " << (*ptv).getitem() << " :\n";
        edgelist<T> * pte = outgoingedges((*ptv).getitem());
        (*pte).prettyprint();
        ptv = (*ptv).getnext();
    }
    return;
}

/* The edge list for each vertex is organised analogous to the vertexlist, but the are no assiciated edgelists. The elements of the list are organised by the neighbour class. */
template<class T> neighbour<T>::neighbour(T item, neighbour<T> *pt_next, neighbour<T> *pt_prev)
{
    secondvertex = item;
    next = pt_next;
    previous = pt_prev;
}

template<class T> T neighbour<T>::getitem(void)
{
    return secondvertex;
}

template<class T> neighbour<T> * neighbour<T>::getnext(void)
{
    return next;
}

template<class T> neighbour<T> * neighbour<T>::getprevious(void)
{
    return previous;
}

template<class T> void neighbour<T>::setitem(T item)
{
    secondvertex = item;
    return;
}

template<class T> void neighbour<T>::setnext(neighbour<T> * pt)
{
    next = pt;
    return;
}

template<class T> void neighbour<T>::setprevious(neighbour<T> * pt)
{
    previous = pt;
    return;
}

/* elist is the class used for the representation of doubly linked lists of vertices (no dummy node) associated with the vertices in the vertexlist. All functions are analogous to those defined for vertexlist. */
template<class T> elist<T>::elist(T item)
{
    first = new neighbour<T>;
    (*first).setitem(item);
    length = 1;
    (*first).setnext(first);
    (*first).setprevious(first);
}

template<class T> int elist<T>::getlength(void)
{
    return length;
}

template<class T> neighbour<T> * elist<T>::getfirst(void)
{
    return first;
}

template<class T> void elist<T>::append(T item)
{
    neighbour<T> * pt_last = (*first).getprevious();
    neighbour<T> * pt_new = new neighbour<T>;
    (*pt_new).setitem(item);
    (*pt_new).setnext(first);
    (*pt_new).setprevious(pt_last);
    (*first).setprevious(pt_new);
    (*pt_last).setnext(pt_new);
    ++length;
    return;
}

template<class T> void elist<T>::addvertex(T item)
{
    if (contains(item) == false)
        append(item);
    return;
}

template<class T> bool elist<T>::contains(T item)
{
    bool result = false;
    neighbour<T> * pt = first;
    for (int i = 0; i < length; i++)
    {
        if ((*pt).getitem() == item)
        {
            result = true;
            break;
        }
        else
            pt = (*pt).getnext();
    }
    return result;
}

template<class T> void elist<T>::remove(T item)
{
    neighbour<T> * pt = first;
    for (int i = 0; i < length; i++)
    {
        if ((*pt).getitem() == item)
        {
            neighbour<T> * pt_prev = (*pt).getprevious();
            neighbour<T> * pt_next = (*pt).getnext();
            (*pt_prev).setnext(pt_next);
            (*pt_next).setprevious(pt_prev);
            if (i == 0)
                first = pt_next;
            --length;
            return;
        }
        pt = (*pt).getnext();
    }
    return;
}
/* The function addall adds all pairs with the given item and the list members, i.e. all outgoing edges to the list given by the pointer pt. It exploit the function add on edgelists. */
template<class T> void elist<T>::addall(T item, edgelist<T> *pt)
{
    neighbour<T> * pte = first;
    for (int i = 0; i < length; i++)
    {
        (*pt).add(item, (*pte).getitem());
        pte = (*pte).getnext();
    }
    return;
}

/* Edges are simply pairs of vertices with obvious get and set functions. */
template<class T> edge<T>::edge(T first, T second)
{
    firstitem = first;
    seconditem = second;
}

template<class T> T edge<T>::origin(void)
{
    return firstitem;
}

template<class T> T edge<T>::destination(void)
{
    return seconditem;
}

template<class T> void edge<T>::setorigin(T item)
{
    firstitem = item;
    return;
}

template<class T> void edge<T>::setdestination(T item)
{
    seconditem = item;
    return;
}

/* only for testing */
template<class T> void edge<T>::prettyprint(void)
{
    cout << "(origin: " << origin() << ", destination: " << destination() << ") + ";
    return;
}

/* edgelists, i.e. sequences of pairs of vertices are only used for output purposes. */
template<class T> edgelist<T>::edgelist(void)
{
    reprarray = new edge<T>*[10000];
    numedges = 0;
}

template<class T> int edgelist<T>::getnumedges(void)
{
    return numedges;
}

template<class T> void edgelist<T>::add(T item1, T item2)
{
    edge<T> * newedge = new edge<T>(item1,item2);
    reprarray[numedges] = newedge;
    ++numedges;
    return;
}

template<class T> void edgelist<T>::prettyprint(void)
{
    for (int i = 0; i < numedges; i++)
    {
        edge<T> * pte = reprarray[i];
        (*pte).prettyprint();
    }
    cout << "\n      --------\n";
    return;
}

/* A graph object just contains a pointer to a vertexlist. */
template<class T> graph<T>::graph(void)
{
    vertices = new vertexlist<T>;
}

template<class T> int graph<T>::numvertices(void)
{
    return (*vertices).getlength();
}

template<class T> int graph<T>::numedges(void)
{
    return (*vertices).countedges();
}

template<class T> void graph<T>::addedge(T origin, T destination)
{
    (*vertices).addedge(origin, destination);
    (*vertices).addedge(destination, origin);
    return;
}

template<class T> void graph<T>::addvertex(T item)
{
    (*vertices).addvertex(item);
    return;
}

template<class T> void graph<T>::deleteedge(T origin, T destination)
{
    (*vertices).removeedge(origin, destination);
    (*vertices).removeedge(destination, origin);
    return;
}

template<class T> void graph<T>::deletevertex(T item)
{
    (*vertices).remove(item);
    return;
}

template<class T> edgelist<T> * graph<T>::outgoingedges(T item)
{
    return (*vertices).outgoingedges(item);
}

template<class T> void graph<T>::prettyprint(void)
{
    cout << "\n\n====== Graph ======\n\n";
    (*vertices).prettyprint();
    cout << "=================\n\n";
    return;
}

/* Treenodes are simply pairs of vertices (one for the parent) plus a distance value with obvious get and set functions. */
template<class T> treenode<T>::treenode(T label, T par, int dist, treenode<T> *pt)
{
    vertexlabel = label;
    parentlabel = par;
    distancetoroot = dist;
    next = pt;
}

template<class T> T treenode<T>::label(void)
{
    return vertexlabel;
}

template<class T> T treenode<T>::parent(void)
{
    return parentlabel;
}

template<class T> int treenode<T>::distance(void)
{
    return distancetoroot;
}

template<class T> treenode<T> * treenode<T>::getnext(void)
{
    return next;
}

template<class T> void treenode<T>::setlabel(T item)
{
    vertexlabel = item;
    return;
}

template<class T> void treenode<T>::setparent(T item)
{
    parentlabel = item;
    return;
}

template<class T> void treenode<T>::setdistance(int dist)
{
    distancetoroot = dist;
    return;
}

template<class T> void treenode<T>::setnext(treenode<T> * pt)
{
    next = pt;
    return;
}

/* only for testing */
template<class T> void treenode<T>::prettyprint(void)
{
    if (parent() != label())
        cout << "Parent vertex of " << label() << " is the vertex " << parent() << ". Distance to the root is " << distance() << ".\n";
    else
        cout << "Vertex " << label() << " is the root.\n";
    return;
}

/* A searchtree contains the output of a breadth-first search. */
template<class T> searchtree<T>::searchtree(void)
{
    first = 0;
    last = 0;
}

template<class T> void searchtree<T>::add(T label, T parentlabel, int dist)
{
    treenode<T> * newnode = new treenode<T>(label, parentlabel, dist);
    if (first == 0)
    {
        first = newnode;
        last = newnode;
        return;
    }
    (*last).setnext(newnode);
    last = newnode;
    return;
}

template<class T> bool searchtree<T>::hasparent(T node)
{
    bool result = false;
    if (first == 0)
        return result;
    treenode<T> * cursor = first;
    while (cursor != last)
    {
        if ((*cursor).label() == node)
        {
            result = true;
            break;
        }
        cursor = (*cursor).getnext();
    }
    if ((*last).label() == node)
        result = true;
    return result;
}

template<class T> void searchtree<T>::prettyprint(void)
{
    if (first == 0)
    {
        cout << "The graph is empty.\n";
        return;
    }
    treenode<T> * cursor = first;
    while (cursor != last)
    {
        (*cursor).prettyprint();
        cursor = (*cursor).getnext();
    }
    (*cursor).prettyprint();
    return;
}

/* Deeptreenodes are to store the output, i.e. triples of a vertex, its position in the dfs processing, and its finishing time. The get and set functions are obvious. */
template<class T> deeptreenode<T>::deeptreenode(T node, int pos, int finish, deeptreenode<T> *pt)
{
    nodelabel = node;
    dfspos = pos;
    finishingtime = finish;
    next = pt;
}

template<class T> T deeptreenode<T>::label(void)
{
    return nodelabel;
}

template<class T> int deeptreenode<T>::dfsnum(void)
{
    return dfspos;
}

template<class T> int deeptreenode<T>::finishtime(void)
{
    return finishingtime;
}

template<class T> deeptreenode<T> * deeptreenode<T>::getnext(void)
{
    return next;
}

template<class T> void deeptreenode<T>::setlabel(T node)
{
    nodelabel = node;
    return;
}

template<class T> void deeptreenode<T>::setdfsnum(int pos)
{
    dfspos = pos;
    return;
}

template<class T> void deeptreenode<T>::setfinishtime(int finish)
{
    finishingtime = finish;
    return;
}

template<class T> void deeptreenode<T>::setnext(deeptreenode<T> * pt)
{
    next = pt;
    return;
}

/* only for testing */
template<class T> void deeptreenode<T>::prettyprint(void)
{
    cout << "Node " << label() << " has dfs number " << dfsnum() << " and finishing time " << finishtime() << ".\n";
    return;
}

/* A deepsearchtree contains the output of a depth-first search. */
template<class T> deepsearchtree<T>::deepsearchtree(void)
{
    first = 0;
    last = 0;
}

template<class T> void deepsearchtree<T>::add(T node, int pos, int finish)
{
    deeptreenode<T> * newnode = new deeptreenode<T>(node, pos, finish);
    if (first == 0)
    {
        first = newnode;
        last = newnode;
        return;
    }
    (*last).setnext(newnode);
    last = newnode;
    return;
}

template<class T> void deepsearchtree<T>::setfinishtime(T node, int finish)
{
    deeptreenode<T> * cursor = first;
    while (cursor != 0)
    {
        if ((*cursor).label() == node)
        {
            (*cursor).setfinishtime(finish);
            return;
        }
        cursor = (*cursor).getnext();
    }
    return;
}

template<class T> bool deepsearchtree<T>::occurs(T node)
{
    bool result = false;
    if (first == 0)
        return result;
    deeptreenode<T> * cursor = first;
    while (cursor != last)
    {
        if ((*cursor).label() == node)
        {
            result = true;
            break;
        }
        cursor = (*cursor).getnext();
    }
    if ((*last).label() == node)
        result = true;
    return result;
}

template<class T> void deepsearchtree<T>::prettyprint(void)
{
    if (first == 0)
    {
        cout << "The graph is empty.\n";
        return;
    }
    deeptreenode<T> * cursor = first;
    while (cursor != last)
    {
        (*cursor).prettyprint();
        cursor = (*cursor).getnext();
    }
    (*cursor).prettyprint();
    return;
}

/* Marker objects are used to mark vertices when they have been explored in depth-first search. */
template<class T> marker<T>::marker(T item, marker<T> *pt)
{
    vertex = item;
    next = pt;
}

template<class T> T marker<T>::getitem(void)
{
    return vertex;
}

template<class T> marker<T> * marker<T>::getnext(void)
{
    return next;
}

template<class T> void marker<T>::setitem(T item)
{
    vertex = item;
    return;
}

template<class T> void marker<T>::setnext(marker<T> * pt)
{
    next = pt;
    return;
}

/* A markerlist contains the marked vertices. */
template<class T> markerlist<T>::markerlist(void)
{
    first = 0;
    last = 0;
}

template<class T> void markerlist<T>::mark(T item)
{
    marker<T> * newmarker = new marker<T>(item);
    if (first == 0)
    {
        first = newmarker;
        last = newmarker;
        return;
    }
    (*last).setnext(newmarker);
    last = newmarker;
    return;
}

template<class T> bool markerlist<T>::ismarked(T item)
{
    bool result = false;
    if (first == 0)
        return result;
    marker<T> * cursor = first;
    while (cursor != last)
    {
        if ((*cursor).getitem() == item)
        {
            result = true;
            break;
        }
        cursor = (*cursor).getnext();
    }
    if ((*last).getitem() == item)
        result = true;
    return result;
}

/* breadth-first search procedure */
template<class T> searchtree<T> * graphtraversal<T>::bfs(T startnode)
{
    vertexlist<T> * vertices = graph<T>::vertices;
    if ((*vertices).contains(startnode) == false)
    {
        cout << "There is no vertex " << startnode << " in the graph.\n";
        return 0;
    }
    searchtree<T> * output = new searchtree<T>;
    (*output).add(startnode, startnode, 0);
    int count = 0;
    fifo<T> * currentlayer = new fifo<T>(20);
    (*currentlayer).pushback(startnode);
    do
    {
        fifo<T> * nextlayer = new fifo<T>(20);
        count++;
        while ((*currentlayer).isempty() == false)
        {
            T currentnode = (*currentlayer).popfront();
            elist<T> * neighbours = (*vertices).edges(currentnode);
            if (neighbours != 0)
            {
                neighbour<T> * cursor = (*neighbours).getfirst();
                for (int i = 0; i < (*neighbours).getlength(); i++)
                {
                    T nextnode = (*cursor).getitem();
                    if ((*output).hasparent(nextnode) == false)
                    {
                        (*nextlayer).pushback(nextnode);
                        (*output).add(nextnode, currentnode, count);
                    }
                    cursor = (*cursor).getnext();
                }
            }
        }
        currentlayer = nextlayer;
    }
    while ((*currentlayer).isempty() == false);
    return output;
}

/* depth-first search procedure */
template<class T> deepsearchtree<T> * graphtraversal<T>::dfs(T startnode)
{
    vertexlist<T> * vertices = graph<T>::vertices;
    if ((*vertices).contains(startnode) == false)
    {
        cout << "There is no vertex " << startnode << " in the graph.\n";
        return 0;
    }
    deepsearchtree<T> * output = new deepsearchtree<T>;
    markerlist<T> * markedvertices = new markerlist<T>;
    int dfspos = 1;
    int finishingtime = 1;
    (*markedvertices).mark(startnode);
    _dfs(startnode, startnode, vertices, output, markedvertices, dfspos, finishingtime);
    return output;
}

/* auxiliary functions for depth-first search */
template<class T> void graphtraversal<T>::_dfs(T node1, T node2, vertexlist<T> * vertices, deepsearchtree<T> * output, markerlist<T> * markedvertices, int &dfspos, int &finishingtime)
{
    elist<T> * neighbours = (*vertices).edges(node2);
    if (neighbours != 0)
    {
        neighbour<T> * cursor = (*neighbours).getfirst();
        for (int i = 0; i < (*neighbours).getlength(); i++)
        {
            T nextnode = (*cursor).getitem();
            if ((*markedvertices).ismarked(nextnode) == true)
                _traverse_nontreeedge(node2, nextnode);
            else
            {
                _traverse_treeedge(node2, nextnode, output, dfspos);
                (*markedvertices).mark(nextnode);
                _dfs(node2, nextnode, vertices, output, markedvertices, dfspos, finishingtime);
            }
            cursor = (*cursor).getnext();
        }
    }
    _backtrack(node1, node2, output, dfspos, finishingtime);
    return;
}

template<class T> void graphtraversal<T>::_traverse_treeedge(T first, T second, deepsearchtree<T> * output, int &dfspos)
{
    if ((*output).occurs(first) == false)
        (*output).add(first, dfspos);
    dfspos++;
    return;
}

template<class T> void graphtraversal<T>::_traverse_nontreeedge(T first, T second)
{
    return;
}

template<class T> void graphtraversal<T>::_backtrack(T node1, T node2, deepsearchtree<T> * output, int &dfspos, int &finishingtime)
{
    if ((*output).occurs(node2) == false)
    {
        (*output).add(node2, dfspos, finishingtime);
    }
    else
        (*output).setfinishtime(node2, finishingtime);
    finishingtime++;
    return;
}

