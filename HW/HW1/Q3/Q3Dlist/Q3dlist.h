//
//  Q3dlist.h
//  
//
//  Created by KD on 16.01.21.
//

#ifndef Q3dlist_h
#define Q3dlist_h

template<class T> class DList;

template<class T> class node
{
    friend class DList<T>;
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

    // New functions defined for Exercise 3:
    void pushback (T value);
    void pushfront (T value);
    node<T>* popback (void);
    node<T>* popfront (void);

private:
    node<T> *dummy;
    int numitems;
    node<T> *locate(int index);
    node<T> *first(void);
    node<T> *last(void);
};

#endif /* Q3dlist_h */