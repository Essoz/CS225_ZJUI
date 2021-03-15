//
//  dlistsort.h
//  
//
//  Created by KD on 16.01.21.
//  Modified by KD on 23.01.21.
//  Modified by HB on 18.02.21.
//

// Defensive Declaration
#ifndef dlistsort_h
#define dlistsort_h

// content below has already shown in the previous code.
//  the author uses the DList for mergeSort() display.

template<class T> class DList;
template<class T> class DListsort;

template<class T> class node
{
    // method using friend class.
    friend class DList<T>;
    friend class DListsort<T>;
public:
    node(T item = 0, node<T> *pt_n = 0, node<T> *pt_p = 0);
//    virtual ~node(void);
    T getdata(void);
    node<T> *getnext(void);
    node<T> *getprevious(void);
    void setdata(T item);
    void setnext(node<T> *pt);
    void setprevious(node<T> *pt);
private:
    T dataitem;
    node<T> *pt_next;
    node<T> *pt_previous;
};

template<class T> class DList
{
public:
    DList(void);
//    virtual ~DList();
    T operator[](int index);
    int getlength(void);
    void setitem(int index, T value);
    T getitem(int index);
    void append(T value);
    void insert(int index, T value);
    void remove(int index);
    void concat(DList<T> *dlist);
    bool member(T value);
    bool equal(DList<T> *dlist);
    bool sublist(DList<T> *dlist);
protected:
    node<T> *dummy;
    int numitems;
    node<T> *locate(int index, node<T> *pt_start = 0);
private:
    node<T> *first(void);
    node<T> *last(void);
};

template<class T> class DListsort : public DList<T>
{
public:
    DListsort(void) : DList<T>(){};
//    virtual ~DListsort();
    void selectionsort(void);
    void mergesort(int thr);
private:
    node<T> *getminimum(node<T> *first, node<T> *last);
    void cut(node<T> *first, node<T> *last, node<T> *mincut);
    void add(node<T> *minadd, node<T> *outlastnode, node<T> *dummy);
    node<T> *ssort(int num, node<T> *firstnode, node<T> *lastnode, node<T> *outlastnode, node<T> *dummy);
    node<T> *msort(int num, node<T> *first, node<T> *last, int thr, node<T> *dummy, node<T> *outlastnode);
    node<T> *merge(node<T> *first1, node<T> *last1, node<T> *first2, node<T> *last2, node<T> *dummy, node<T> *outlast);
};

#endif /* dlistsort_h */
