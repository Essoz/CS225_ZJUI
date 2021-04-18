//
//  graph.h
//  
//
//  Created by KD on 11.04.21.
//
#ifndef graph_h
#define graph_h
#include <vector>
using namespace std;

enum Mode {
    init, examine, build_digraph, build_path, modify
};

template<class T> class vertexlist;
template<class T> class edgelist;
template<class T> class edge;

template<class T> class vertex
{
    friend class vertexlist<T>;
public:
    vertex(T item = 0, vertex<T> *pt_next = 0, vertex<T> *pt_prev = 0);
    T getitem(void);
    vertex<T> * getnext(void);
    vertex<T> * getprevious(void);
    bool getselected(void);
    void setitem(T item);
    void setnext(vertex<T> * pt_next);
    void setprevious(vertex<T> * pt_prev);
    void setselected(bool B);
private:
    T vertexid;
    vertex<T> * next;
    vertex<T> * previous;
    bool selected;
};

template<class T> class vertexlist
{
public:
    vertexlist(void);
    int getlength(void);
    vertex<T>* getdummy();
    void append(T item);
    void addvertex(T item);
    vertex<T>* retrieval(int id);
    bool contains(T item);
    bool remove(T item);
private:
    vertex<T> * dummy;
    int numvertices;
};

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

template<class T> class edgelist
{
public:
    edgelist(int m);
    void setarr(edge<T>** arra);
    void setnumedges(int n);
    void setmode(int m);
    edge<T>** getarr();
    int getnumedges(void);
    int getmode(void);
    vector<edge<T>*>* retrieval(T item);
    bool check_distinct(vector<edge<T>*>* set);
    void add(T item1, T item2);
    void prettyprint(void); // only for testing
private:
    edge<T>** arr;          // Unordered
    edge<T> ** reprarray;   // Ordered
    int numedges;   // Number of edges
    int mode;       // 0 means unordered, 1 means ordered
};

// For HW8 EX3:
// We only reuse some of the templates provided above:
template<class T> class Bipartite
{
public:
    Bipartite(vertexlist<T>* boys, vertexlist<T>* girls, edgelist<T>* edges);
    bool is_perfect_match();
    vector<edge<T>*>* G_to_B(edgelist<T>* list);
    vector<edge<T>*>* B_to_G(edgelist<T>* list);
    edgelist<T>* difference(edgelist<T>* list1, edgelist<T>* list2);
    edgelist<T>* unordered(edgelist<T>* list);
    edgelist<T>* reachable(T boy, edgelist<T>* gra, T girl);

    vertexlist<T>* getBoys();
    vertexlist<T>* getGirls();
    edgelist<T>* getEdges();
    edgelist<T>* getPartial_match();
    edgelist<T>* getDi_graph();
    edgelist<T>* getPath();
    Mode getmode();
    void setmode(Mode m);

private:
    // Two sets of vertices with equal size:
    vertexlist<T>* Boys;
    vertexlist<T>* Girls;
    // Two non-ordered edgelists:
    edgelist<T>* Edges;
    edgelist<T>* Partial_match;
    // Two ordered edgelists:
    edgelist<T>* Di_graph;
    edgelist<T>* Path;
    // Mode to call different functions:
    Mode mode;
};

#endif /* graph_h */
