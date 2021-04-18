//
//  graph.cpp
//  
//
//  Created by KD on 11.04.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "graph.h"
using std::cout;

/* The structure of a vertex is analogous to a node in a doubly linked list. In addition we keep an "edgelist" with each vertex, 
   i.e. the list of neighbour vertices. */
template<class T> vertex<T>::vertex(T item, vertex<T> *pt_next, vertex<T> *pt_prev)
{
    vertexid = item;
    next = pt_next;
    previous = pt_prev;
    selected = 0;
}

template<class T> T vertex<T>::getitem(void)
{
    return vertexid;
}

template<class T> vertex<T>* vertex<T>::getnext(void)
{
    return next;
}

template<class T> vertex<T>* vertex<T>::getprevious(void)
{
    return previous;
}

template<class T> bool vertex<T>::getselected(void)
{
    return selected;
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

template<class T> void vertex<T>::setselected(bool B)
{
    selected = B;
}

/* A vertexlist is a doubly linked list with vertices and a dummy node. */
template<class T> vertexlist<T>::vertexlist(void)
{
    dummy = new vertex<T>;
    (*dummy).setnext(dummy);
    (*dummy).setprevious(dummy);
    numvertices = 0;
}

/*the total number of vertex*/
template<class T> int vertexlist<T>::getlength(void)
{
    return numvertices;
}

template<class T> vertex<T>* vertexlist<T>::getdummy(void)
{
    return dummy;
}

/* append is analogous to linked lists, i.e. we add a new vertex at the end and adjust pointers. 
 * NOTE: never call this function directly, use addvertex(item)
 */
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

/* A new vertex is only added, if it is not yet in the list.*/
template<class T> void vertexlist<T>::addvertex(T item)
{
    if (contains(item) == false)
        append(item);
    return;
}

template<class T> vertex<T>* vertexlist<T>::retrieval(int id)
{
    vertex<T>* pt = (*dummy).getnext();
    for (int i = 0; i < id; i++)   // Go iteratively
    {
        pt = (*pt).getnext();
    }
    return pt;
}

/* To check if a vertex is already in the list the list is scanned until the element is found.
 * called by addvertex
 */
template<class T> bool vertexlist<T>::contains(T item)
{
    bool result = false;
    vertex<T> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)   //for all vertex, check iteratively
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
            location = pt;
            break;
        }
        pt = (*pt).getnext();
    }
    /* Finally, we get to the deletion from the vertexlist. */
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

/* only for testing
 * print one specific edge
 */
template<class T> void edge<T>::prettyprint(void)
{
    cout << "(origin: " << origin() << ", destination: " << destination() << ") + ";
    return;
}

/* edgelists, i.e. sequences of pairs of vertices are only used for output purposes.
 * NOTE: the upper bound of the edge array is 100 
 */
template<class T> edgelist<T>::edgelist(int m)
{
    if (0 == m)
    {   // Unordered edgelist
        arr = new edge<T>*[100];
        reprarray = NULL;
    }
    else
    {   // Ordered edgelist
        reprarray = new edge<T>*[100];
        arr = NULL;
    }
    mode = m;
    numedges = 0;
}

template<class T> void edgelist<T>::setarr(edge<T>** arra)
{
    if (0 == mode) {
        arr = arra;
    }
    reprarray = arra;
}

template<class T> void edgelist<T>::setnumedges(int n)
{
    numedges = n;
}

template<class T> void edgelist<T>::setmode(int m)
{
    mode = m;
}

template<class T> edge<T>** edgelist<T>::getarr()
{
    if (0 == mode) {
        return arr;
    }
    return reprarray;
}

template<class T> int edgelist<T>::getnumedges(void)
{
    return numedges;
}

template<class T> int edgelist<T>::getmode(void)
{
    return mode;
}

// Return a vector with all edges containing "item":
template<class T> vector<edge<T>*>* edgelist<T>::retrieval(T item)
{
    vector<edge<T>*>* result = new vector<edge<T>*>;
    // Go through the edgelist:
    for (int i = 0; i < numedges; i++)
    {
        if (mode == 1)
        {
            if (item == reprarray[i]->origin() || item == reprarray[i]->destination())
            {
                result->push_back(reprarray[i]);
            }
        }
        else
        {
            if (item == arr[i]->origin() || item == arr[i]->destination())
            {
                result->push_back(arr[i]);
            }
        }
    }
    return result;
}

// Check if the given list has no common edges of the edgelist:
template<class T> bool edgelist<T>::check_distinct(vector<edge<T>*>* set)
{
    // Go through the input set:
    for (int i = 0; i < int(set->size()); i++)
    {
        // Go through the edgelist:
        for (int j = 0; j < numedges; j++)
        {
            if (mode == 1)
            {
                if ((set->at(i)->origin() == reprarray[j]->origin() &&
                    set->at(i)->destination() == reprarray[j]->destination()))
                {
                    return false;
                }
            }
            else
            {
                if ((set->at(i)->origin() == arr[j]->origin() &&
                    set->at(i)->destination() == arr[j]->destination()) ||
                    (set->at(i)->origin() == arr[j]->destination() &&
                        set->at(i)->destination() == arr[j]->origin()))
                {
                    return false;
                }
            }
        }
    }
    return true;
}

/*first par is origin, sec is dest*/
/*For unordered list, the order doesn't matter, so two copies are contained*/
template<class T> void edgelist<T>::add(T item1, T item2)
{
    edge<T> * newedge = new edge<T>(item1,item2);
    if (0 == mode)
    {
        arr[numedges] = newedge;
    }
    else
    {
    reprarray[numedges] = newedge;
    }
    ++numedges;
    return;
}

/*print all edge start from one edge*/
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


/* Below are for HW8 EX3: */
/*****************************************************************************************/
// Construction for Bipartite graph:
template<class T> Bipartite<T>::Bipartite(vertexlist<T>* boys, vertexlist<T>* girls, edgelist<T>* edges)
{
    Boys = boys;
    Girls = girls;
    Edges = edges;
    //Partial_match = new edgelist<T>(0);
    //Di_graph = new edgelist<T>(1);
    //Path = new edgelist<T>(1);
    mode = init;
}

template<class T> vertexlist<T>* Bipartite<T>::getBoys()
{
    return Boys;
}

template<class T> vertexlist<T>* Bipartite<T>::getGirls()
{
    return Girls;
}

template<class T> edgelist<T>* Bipartite<T>::getEdges()
{
    return Edges;
}

template<class T> edgelist<T>* Bipartite<T>::getPartial_match()
{
    return Partial_match;
}

template<class T> edgelist<T>* Bipartite<T>::getDi_graph()
{
    return Di_graph;
}

template<class T> edgelist<T>* Bipartite<T>::getPath()
{
    return Path;
}

template<class T> Mode Bipartite<T>::getmode()
{
    return mode;
}

template<class T> void Bipartite<T>::setmode(Mode m)
{
    mode = m;
}

/*determine the perfect match*/
template<class T> bool Bipartite<T>::is_perfect_match()
{
	/*Implement your code here*/
    while (true)
    {
        // Check the mode:
        switch (mode)
        {
        case init:  // Initialization
        {
            mode = examine;
            Partial_match = new edgelist<T>(0);
            Partial_match->setnumedges(0);
            break;
        }
        case examine:   // Check if there are boys who have not been selected yet:
        {
            int check1 = 0;
            for (int i = 0; i < Boys->getlength(); i++)
            {   // Go through the Boys list:
                if (Boys->retrieval(i)->getselected() == 0)
                {
                    check1 = 1;
                    mode = build_digraph;
                    break;
                    //// If not, check if all edges with this boy are in the partial_match:
                    //vector<edge<T>*>* b_edge = Edges->retrieval(Boys->retrieval(i)->getitem());
                    //if (true == check_distinct(b_edge))
                    //{
                    //    mode = build_digraph;
                    //    check = 1;
                    //    break;
                    //}
                }
            }
            if (check1 == 0)
            {   // Have a perfect matching
                return true;
            }
            break;
        }
        case build_digraph:     // Build di-graph
        {
            Di_graph = new edgelist<T>(1);
            vector<edge<T>*>* list1 = G_to_B(Partial_match);
            vector<edge<T>*>* list2 = B_to_G(difference(Edges, Partial_match));
            for (int i = 0; i < int(list1->size()); i++)
            {
                Di_graph->getarr()[i] = list1->at(i);
                Di_graph->setnumedges(Di_graph->getnumedges() + 1);
            }
            for (int i = 0; i < int(list2->size()); i++)
            {
                Di_graph->getarr()[i + int(list1->size())] = list2->at(i);
                Di_graph->setnumedges(Di_graph->getnumedges() + 1);
            }
            mode = build_path;
            break;
        }
        case build_path:    // Build a path
        {
            // Choose a boy that has not been selected:
            vertex<T>* boy;
            vertex<T>* girl;
            for (int i = 0; i < Boys->getlength(); i++)
            {   // Go through the Boys list:
                if (Boys->retrieval(i)->getselected() == 0)
                {
                    boy = Boys->retrieval(i);
                    boy->setselected(1);
                    break;
                }
            }
            // Check if there are girls that have not been selected:
            int check2 = 0;
            Path = new edgelist<T>(1);
            for (int i = 0; i < Girls->getlength(); i++)
            {   // Go through the Girls list:
                if (Girls->retrieval(i)->getselected() == 0)
                {   // If not selected, then check if the girl is reachable to boy selected:
                    Path = reachable(boy->getitem(), Di_graph, Girls->retrieval(i)->getitem());
                    if (0 != Path->getnumedges())
                    {   // If so, then choose this girl:
                        girl = Girls->retrieval(i);
                        girl->setselected(1);
                        check2 = 1;
                        break;
                    }
                }
            }
            // If no girls are suitable, return false:
            if (0 == check2)
            {
                return false;
            }
            // If there is a girl suitable, build the path:
            mode = modify;
            break;
        }
        case modify:        // Update the partial_match
        {
            edgelist<T>* temp = Partial_match;
            Partial_match = new edgelist<T>(0);
            edgelist<T>* list3 = difference(Partial_match, unordered(Path));
            edgelist<T>* list4 = difference(unordered(Path), Partial_match);

            for (int i = 0; i < list3->getnumedges(); i++)
            {
                Partial_match->getarr()[i] = list3->getarr()[i];
                Partial_match->setnumedges(Partial_match->getnumedges() + 1);
            }
            for (int i = 0; i < list4->getnumedges(); i++)
            {
                Partial_match->getarr()[i + list3->getnumedges()] = list4->getarr()[i];
                Partial_match->setnumedges(Partial_match->getnumedges() + 1);
            }
            mode = examine;
            break;
        }
        default:
        {
            cout << "Error!" << endl;
            exit(1);
            break;
        }
        }
    }
}

// Make the unordered list ordered:
template<class T> vector<edge<T>*>* Bipartite<T>::G_to_B(edgelist<T>* list)
{
    vector<edge<T>*>* result = new vector<edge<T>*>;
    // Loop through the list:
    for (int i = 0; i < list->getnumedges(); i++)
    {
        T first = (list->getarr())[i]->origin();
        if (int(first) <= Boys->getlength())
        {   // Need to make reverse:
            T second = first;
            first = (list->getarr())[i]->destination();
            edge<T>* e = new edge<T>(first, second);
            result->push_back(e);
        }
        else
        {
            result->push_back(list->getarr()[i]);
        }
    }
    return result;
}

template<class T> vector<edge<T>*>* Bipartite<T>::B_to_G(edgelist<T>* list)
{
    vector<edge<T>*>* result = new vector<edge<T>*>;
    // Loop through the list:
    for (int i = 0; i < list->getnumedges(); i++)
    {
        T first = (list->getarr())[i]->origin();
        if (int(first) > Boys->getlength())
        {   // Need to make reverse:
            T second = first;
            first = (list->getarr())[i]->destination();
            edge<T>* e = new edge<T>(first, second);
            result->push_back(e);
        }
        else
        {
            result->push_back(list->getarr()[i]);
        }
    }
    return result;
}

// Get the difference of two edgelists:
template<class T> edgelist<T>* Bipartite<T>::difference(edgelist<T>* list1, edgelist<T>* list2)
{
    edgelist<T>* diff = new edgelist<T>(list1->getmode());
    // Go through the first set:
    for (int i = 0; i < list1->getnumedges(); i++)
    {
        int find = 0;
        // Go through the edgelist:
        for (int j = 0; j < list2->getnumedges(); j++)
        {
            if (mode == 1)
            {
                if ((list1->getarr()[i])->origin() == (list2->getarr()[j])->origin() &&
                    (list1->getarr()[i])->destination() == (list2->getarr()[j])->destination())
                {
                    find = 1;
                    break;
                }
            }
            else
            {
                if (((list1->getarr()[i])->origin() == (list2->getarr()[j])->origin() &&
                    (list1->getarr()[i])->destination() == (list2->getarr()[j])->destination()) ||
                    ((list1->getarr()[i])->origin() == (list2->getarr()[j])->destination() &&
                    (list1->getarr()[i])->destination() == (list2->getarr()[j])->origin()))
                {
                    find = 1;
                    break;
                }
            }
        }
        if (0 == find)
        {
            diff->add((list1->getarr()[i])->origin(), (list1->getarr()[i])->destination());
        }
    }
    return diff;
}

// Make the list from ordered to unordered:
template<class T> edgelist<T>* Bipartite<T>::unordered(edgelist<T>* list)
{
    // Store the array temporarily:
    edge<T>** temp = list->getarr();
    list->setarr(NULL);
    // Change the mode:
    list->setmode(0);
    // Switch the arrays:
    list->setarr(temp);
    return list;
}

// Check if the two people are reachable by building a path, if no path, return NULL:
template<class T> edgelist<T>* Bipartite<T>::reachable(T boy, edgelist<T>* gra, T girl)
{
    std::cout << boy << " " << girl << std::endl;
    // The input gra must be a ordered edgelist, we can apply DFS to find the path:
    for (int i = 0; i < gra->getnumedges(); i++)
    {
        // One edge is found:
        if (boy == (gra->getarr())[i]->origin())
        {
            // If the other side is the girl we need, add the edge to path:
            if (girl == (gra->getarr())[i]->destination())
            {
                Path->add(boy, girl);
                return Path;
            }
            // Call the function recursively, until we find the girl or no edge avaliable:
            T temp1 = (gra->getarr())[i]->origin();
            T temp2 = (gra->getarr())[i]->destination();
            Path = reachable(temp2, gra, girl);
            // If the path is not empty, means a path is found, fill the remaining:
            if (0 != Path->getnumedges())
            {
                Path->add(temp1, temp2);
                return Path;
            }
        }
    }
    // No other edges found, return the path:
    return Path;
}
/*********************************************************************************************/
