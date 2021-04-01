//
//  trie.h
//  
//
//  Created by KD on 20.03.21.
//

#ifndef trie_h
#define trie_h

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

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
private:
    int numitems;
    T *reprarray;
    int maxsize, minsize;
    void allocate(void);
    void deallocate(void);
};

template<class T> class trie;

template<class T> class trienode
{
    friend class trie<T>;
public:
    trienode(T item = 0, bool l = false, trienode<T> *pt_next = 0, trienode<T> *pt_follow = 0);
    T getdata(void);
    bool getlast(void);
    trienode<T> *getnext(void);
    trienode<T> *getfollow(void);
    void setdata(T item);
    void setlast(bool l);
    void setnext(trienode<T> *pt_next);
    void setfollow(trienode<T> *pt_follow);
private:
    T data;
    bool last;
    trienode<T> *next;
    trienode<T> *follow;
};

template<class T> class trie
{
public:
    trie(void);
    void insert(AList<T> list);
    bool intrie(AList<T> list);
    void display(void);   // only for testing
private:
    trienode<T> *start;
    /* _insert and contains are auxiliary functions to navigate recursively through the TRIE for insert and find */
    trienode<T> *_insert(trienode<T> *pt, AList<T> list);
    bool contains(trienode<T> *pt, AList<T> list);
    void _display(trienode<T> * pt, AList<T> list);   // only for testing

/* Function headers for Assignment.7 Ex.2
 * Return: - the given word itself if it is the in dictionary
 *         - an AList of words in accordance to the request otherwise
 *         - illegitimate if neither the word itself and requested words in dict
 */
public:
    AList<string> return_extend(AList<T> list, AList<string> &result);
    AList<string> return_prefix(AList<T> list, AList<string> &result);
    AList<string> return_diff(AList<T> list, AList<string> &result);

private:
    // helper function you may or may not use
    bool contains_extend(trienode<T> *pt, AList<T> list, AList<T> path, AList<string> &result);
    bool contains_diff(trienode<T> *pt, AList<T> list, AList<T> path, AList<string> &result, int diff);
};

#endif /* trie_h */
