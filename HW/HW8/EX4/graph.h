//
//  graph.h
//  
//
//  Created by KD on 11.04.21.
//

#ifndef graph_h
#define graph_h

template<class T> class vertexlist;

template<class T> class edgelist;

template<class T> class edge;

template<class T> class elist;
/*class vertex
*Every vertex is an element in the graph; It has :
*pointer to prev;
*pointer to next;
*edges;
*item;
* more information is contained in the vertexlist class
*/
template<class T> class vertex
{
    friend class vertexlist<T>;
public:
    vertex(T item = 0, vertex<T> *pt_next = 0, vertex<T> *pt_prev = 0);
    int numoutedges(void);
    T getitem(void);
    vertex<T> * getnext(void);
    vertex<T> * getprevious(void);
    elist<T> * getedges(void);
    void setitem(T item);
    void setnext(vertex<T> * pt_next);
    void setprevious(vertex<T> * pt_prev);
    void setedges(elist<T> * pt_edges);
private:
    T vertexid;
    vertex<T> * next;
    vertex<T> * previous;
    elist<T> * edgelist;
};
/*the list of all vertex
*/
template<class T> class vertexlist
{
public:
    vertexlist(void);
    int getlength(void);
    int countedges(void);
    void append(T item);
    void addvertex(T item);
    bool contains(T item);
    bool remove(T item);
    void addedge(T first, T second);
    void removeedge(T first, T second);
    edgelist<T> * outgoingedges(T item);
    void prettyprint(void); // only for testing
private:
    vertex<T> * dummy;
    int numvertices;
};
/*class neighbour:
*it is the neighbor vertex from one vertex
*/
template<class T> class neighbour
{
    friend class elist<T>;
public:
    neighbour(T item = 0, neighbour<T> * pt_next = 0, neighbour<T> * pt_prev = 0);
    T getitem(void);
    neighbour<T> * getnext(void);
    neighbour<T> * getprevious(void);
    void setitem(T item);
    void setnext(neighbour<T> * pt);
    void setprevious(neighbour<T> * pt);
private:
    /*contain the item of this neighbor vertex*/
    T secondvertex;
    neighbour<T> * next;
    neighbour<T> * previous;
};
/*the list of all neighbor edges
*every vertex has a elist contain all edge from this vertex
*elist is less useful from edge list, it only contain the first neighbour pointer,
*since the neighbors are in double linked, see the neighbor class def;
so in order to have a beter use, add a function called addall, which is used to convert 
*elist to edge list, because edge list class use an array to store all the pointers of edges
*which has a better behavior than elist
*/
template<class T> class elist
{
public:
    elist(T item);
    int getlength(void);
    void append(T item);
    void addvertex(T item);
    bool contains(T item);
    void remove(T item);
    void addall(T item, edgelist<T> * pt);
private:
    neighbour<T> * first;
    int length;
};
/*class edge:
*every edge has:
origin;
*destination;
*the first item is the origin 
*the second item is the destination
*more information in edgelist class
*/
template<class T> class edge
{
    friend class edgelist<T>;
public:
    edge(T first, T second);
    T origin(void);
    T destination(void);
    void setorigin(T item);
    void setdestination(T item);
    void prettyprint(void); // only for testing
private:
    T firstitem;
    T seconditem;
};
/*class edgelist:
*the list of edge that belong to one vertex
*every vertex has a edgelist
*/
template<class T> class edgelist
{
public:
    edgelist(void);
    int getnumedges(void);
    void add(T item1, T item2);
    void prettyprint(void); // only for testing
private:
    edge<T> ** reprarray;   //store the pointer to class edge type
    int numedges;
};
/*
Class graph:
*contain all information of vertex and edge
*include operation:
*total number;
*add
*delete
*insert
*/
template<class T> class graph
{
public:
    graph(void);
    
    int numvertices(void);
    int numedges(void);
    
    void addedge(T origin, T destination);
    void addvertex(T item);
    
    void deleteedge(T origin, T destination);
    void deletevertex(T item);
    
    edgelist<T> * outgoingedges(T item);
    void prettyprint(void); // only for testing
    
    void insert_edge(T origin, T destination);
    void insert_vertex(T item);
    
    void delete_edge(T origin, T destination);
    void delete_vertex(T item);
    
    edgelist<T> * incident_edges(T item);
    int is_perfect_match(void);
private:
    vertexlist<T> * vertices;
};

#endif /* graph_h */
