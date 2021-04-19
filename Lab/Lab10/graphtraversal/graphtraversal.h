//
//  graphtraversal.h
//  
//
//  Created by KD on 12.04.21.
//

#ifndef graphtraversal_h
#define graphtraversal_h

template<class T> class fifo
{
public:
    fifo(int size = 10);
//    virtual ~fifo();
    T &operator[](int index);
    int getlength(void);
    bool isempty(void);
    T back(void);
    T front(void);
    void pushback(T value);
    T popfront(void);
private:
    int maxsize, minsize;
    int first, last;
    int numitems;
    T *reprarray;
    void allocate(void);
    void deallocate(void);
};

template<class T> class AList
{
public:
    AList(int size = 20);
    T &operator[](int index);
    int getlength(void);
    void setitem(int index, T value);
    T getitem(int index);
    void append(T value);
    void insert(int index, T value);
    void remove(int index);
    void concat(AList<T> &list);
    bool member(T value);
    bool equal(AList<T> &list);
    bool sublist(AList<T> &list);
protected:
    int numitems;
    T *reprarray;
private:
    int maxsize, minsize;
    void allocate(void);
    void deallocate(void);
};

template<class T> class AListsort : public AList<T>
{
public:
    AListsort(int size = 20) : AList<T>(size){};
    void bsort(void);
    void qsort(int thr);
};

template<class T> class vertexlist;

template<class T> class edgelist;

template<class T> class edge;

template<class T> class elist;

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
    elist<T> * edges(T node);
    edgelist<T> * outgoingedges(T item);
    void prettyprint(void); // only for testing
private:
    vertex<T> * dummy;
    int numvertices;
};

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
    T secondvertex;
    neighbour<T> * next;
    neighbour<T> * previous;
};

template<class T> class elist
{
public:
    elist(T item);
    int getlength(void);
    neighbour<T> * getfirst(void);
    void append(T item);
    void addvertex(T item);
    bool contains(T item);
    void remove(T item);
    void addall(T item, edgelist<T> * pt);
private:
    neighbour<T> * first;
    int length;
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
    edgelist(void);
    int getnumedges(void);
    void add(T item1, T item2);
    void prettyprint(void); // only for testing
private:
    edge<T> ** reprarray;
    int numedges;
};

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
protected:
    vertexlist<T> * vertices;
};

template<class T> class searchtree;

template<class T> class treenode
{
    friend class searchtree<T>;
public:
    treenode(T label, T par, int dist, treenode<T> *pt = 0);
    T label(void);
    T parent(void);
    int distance(void);
    treenode<T> * getnext(void);
    void setlabel(T item);
    void setparent(T item);
    void setdistance(int dist);
    void setnext(treenode<T> * pt);
    void prettyprint(void); // only for testing
private:
    T vertexlabel;
    T parentlabel;
    int distancetoroot;
    treenode<T> * next;
};

template<class T> class searchtree
{
public:
    searchtree(void);
    void add(T label, T parentlabel, int dist);
    bool hasparent(T node);
    void prettyprint(void); // only for testing
private:
    treenode<T> * first;
    treenode<T> * last;
};

template<class T> class deepsearchtree;

template<class T> class deeptreenode
{
    friend class deepsearchtree<T>;
public:
    deeptreenode(T node, int pos = 1, int finish = 1, deeptreenode<T> *pt = 0);
    T label(void);
    int dfsnum(void);
    int finishtime(void);
    deeptreenode<T> * getnext(void);
    void setlabel(T node);
    void setdfsnum(int pos);
    void setfinishtime(int finish);
    void setnext(deeptreenode<T> * pt);
    void prettyprint(void); // only for testing
private:
    T nodelabel;
    int dfspos;
    int finishingtime;
    deeptreenode<T> * next;
};

template<class T> class deepsearchtree
{
public:
    deepsearchtree(void);
    void add(T node, int pos, int finish = -1);
    void setfinishtime(T node, int finish);
    bool occurs(T node);
    void prettyprint(void); // only for testing
private:
    deeptreenode<T> * first;
    deeptreenode<T> * last;
};

template<class T> class markerlist;

template<class T> class marker
{
    friend class markerlist<T>;
public:
    marker(T item = 0, marker<T> * pt = 0);
    T getitem(void);
    marker<T> * getnext(void);
    void setitem(T item);
    void setnext(marker<T> * pt);
private:
    T vertex;
    marker<T> * next;
};

template<class T> class markerlist
{
public:
    markerlist(void);
    void mark(T item);
    bool ismarked(T item);
private:
    marker<T> * first;
    marker<T> * last;
};

template<class T> class graphtraversal : public graph<T>
{
public:
    graphtraversal(void) : graph<T>(){};
    searchtree<T> * bfs (T startnode);
    deepsearchtree<T> * dfs (T startnode);
private:
    void _dfs(T node1, T node2, vertexlist<T> * vertices, deepsearchtree<T> * output, markerlist<T> * markedvertices, int &dfspos, int &finishingtime);
        // first argument not used
    void _traverse_treeedge(T first, T second, deepsearchtree<T> * output, int &dfspos);
        // The second argument will not be used.
    void _traverse_nontreeedge(T first, T second);
        // This function will do nothing.
    void _backtrack(T node1, T node2, deepsearchtree<T> * output, int &dfspos, int &finishingtime);
        // first argument not used
};

#endif /* graphtraversal_h */
