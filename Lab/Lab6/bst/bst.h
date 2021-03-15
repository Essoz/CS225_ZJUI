//
//  bst.h
//  
//
//  Created by KD on 14.03.21.
//

#ifndef bst_h
#define bst_h

template<class T> class BST;

template<class T> class node
{
    friend class BST<T>;
public:
    node(T item = 0, node<T> *left = 0, node<T> *right = 0);
//    virtual ~node(void);
    T getdata(void);
    node<T> *getleft(void);
    node<T> *getright(void);
    void setdata(T item);
    void setleft(node<T> *pt);
    void setright(node<T> *pt);
private:
    T data;
    node<T> *pt_left;
    node<T> *pt_right;
};

template<class T> class BST
{
public:
    BST(void);
//    virtual ~BST(void);
    void insert(T item);
    void remove(T item);
    bool find(T item);
    void display(void);
private:
    node<T> *root;
    /* _insert, _delete and _find are auxiliary functions to navigate recursively through the BST for insert, delete and find */
    node<T> *_insert(node<T> *pt, T val);
    node<T> *_delete(node<T> *pt, T val);
    bool _find(node<T> *pt, T val);
    /* merge is an auxiliary function used, when a non-leaf node is deleted */
    node<T> *merge(node<T> *pt1, node<T> *pt2);
    /* merge iterates through the BST in depth-first way to display the values in all nodes; it can be extended to also display all pointers */
    void _display(node<T> * pt);
};

#endif /* bst_h */
