/*                                    tab:8
 *
 * dlist.cpp - source file for CS225 Linked List.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice and the following
 * two paragraphs appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE AUTHOR OR THE UNIVERSITY OF ILLINOIS BE LIABLE TO
 * ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
 * DAMAGES ARISING OUT  OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
 * EVEN IF THE AUTHOR AND/OR THE UNIVERSITY OF ILLINOIS HAS BEEN ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE AUTHOR AND THE UNIVERSITY OF ILLINOIS SPECIFICALLY DISCLAIM ANY
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE
 * PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND NEITHER THE AUTHOR NOR
 * THE UNIVERSITY OF ILLINOIS HAS ANY OBLIGATION TO PROVIDE MAINTENANCE,
 * SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Author:        Klaus-Dieter Schewe
 * Version:        2
 * Creation Date:   ?
 * Filename:        main.cpp
 * History:
 *    Klaus-Dieter Schewe    1    16 January 2021
 *        First written.
 *    Hao BAI    2    19 January 2021
 *        Annotations added.
 *
 */


#ifndef dlist_h
#define dlist_h

template<class T> class DList;

template<class T> class node
{
// private:
    friend class DList<T>;
public:
    node(T item = 0, node<T> *pt_n = 0, node<T> *pt_p = 0);
//    virtual ~node(void);
    T getdata(void);
    node<T> *getnext(void);
    node<T> *getprevious(void);
    void setdata(T item);    void setnext(node<T> *pt);
    void setprevious(node<T> *pt);
private:
    // these are the member data inside the class node.
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
private:
    // notice. DList can get access to class node to use this class type.
    //  this is because DList is a FRIEND of class node.
    //  refer C++ primer plus, friend class. (Chapter 15.1)
    //      you need to design a class TV and a class remote. is it better to define their
    //      relationships to be is-a, has-a, or connected-with? of course it's the last one.
    //      thus, it's better to define this relationship using a friend class.
    // notice. a friend class (DList) can access to the origin class (node), even the private
    //  members in the DList can be accessed as well.
    node<T> *dummy;
    int numitems;
    node<T> *locate(int index);
    node<T> *first(void);
    node<T> *last(void);
};

#endif /* dlist_h */
