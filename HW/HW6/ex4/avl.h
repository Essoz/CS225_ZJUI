//
//  avl.h
//  
//
//  Created by KD on 18.03.21.
//

#ifndef avl_h
#define avl_h

template<class T> class AVL;

template<class T> class avlnode
{
    friend class AVL<T>;
public:
    avlnode(T item = 0, int bal = 0, avlnode<T> *left = 0, avlnode<T> *right = 0);
    T getdata(void);
    int getbalance(void);
    int get_num_balance(void);      // For HW6
    avlnode<T> *getleft(void);
    avlnode<T> *getright(void);
    void setdata(T item);
    void setbalance(int bal);
    void set_num_balance(int bal);      // For HW6
    void setleft(avlnode<T> *pt);
    void setright(avlnode<T> *pt);
private:
    T data;
    int balance;
    int num_balance;        // Added for HW6
    avlnode<T> *pt_left;
    avlnode<T> *pt_right;
};

template<class T> class AVL
{
public:
    AVL(void);
    void insert(T item);
    void remove(T item);
    bool find(T item);
    void display(void);
private:
    avlnode<T> *root;
    bool mode;
    avlnode<T> *bchild;
    avlnode<T> *bgrandchild;
    /* auxiliary functions for recursive insert, delete and find */
    avlnode<T> *_insert(avlnode<T> *pt, T val);
    avlnode<T> *_delete(avlnode<T> *pt, T val);
    bool _find(avlnode<T> *pt, T val);
    /* operations for single rotations with new balance values pbal and cbal for parent and child, respectively */
    avlnode<T> *rotateleft(avlnode<T> *parent, avlnode<T> *child, int pbal, int cbal);
    avlnode<T> *rotateright(avlnode<T> *parent, avlnode<T> *child, int pbal, int cbal);
    /* auxiliary operation to find the maximum in the left successor tree, swap it with the value in the node pointed to by the first argument, delete this node and propagate balance changes upwards to the start of the search for this maximum; the second pounter is used for recursive descent  */
    avlnode<T> *findswapleft(avlnode<T> *pt_swap, avlnode<T> *here);
    /* alternatively, we can search for the minimum in the right successor tree, swap it with the value in the node pointed to by the first argument and propagate balance changes back upwards; this alternative is not implemented here */
//    avlnode<T> *findswapright(avlnode<T> *pt_swap, avlnode<T> *here);
    void _display(avlnode<T> * pt);

    // For Homework Assignment 6:
    avlnode<T>* _insert_new(avlnode<T> *pt, T val);
    avlnode<T>* _delete_new(avlnode<T> *pt, T val);
    void _reset(T val, int mode);
    avlnode<T>* _check(avlnode<T> *pt);
    avlnode<T>* _reorganize(avlnode<T> *pt);
    avlnode<T>* _find_presuccessor(avlnode<T> *pt, T val);
    avlnode<T>* _find_successor(avlnode<T> *pt, T val);
};

#endif /* avl_h */
