#ifndef multiset_h
#define multiset_h
#include <iostream>	
#include <math.h>
#include <cstdlib>
#include <map>
#include <vector>
using namespace std;

/* Put your decleration here */
template<class T> class MultiSet
{
    public:
        MultiSet(T* input_set, int length);
        /* You should add other functions to make the structure work  */
        void create_hashtable();            // Create a new set with explicit multiplicities
        int calculate_hashvalue(T item, int size);
        void display();

        /* The following is required for this assignment */
        /* It is not complete, you should design the APIs by yourself */
        void insertion(T item);
        void deletion(T item);
        std::pair<T, int>* retrieval(T item);

        static std::pair<T, int>** setunion(T* set1, T* set2, int length1, int length2);
        static std::pair<T, int>** intersection(T* set1, T* set2, int length1, int length2);
        static std::pair<T, int>** difference(T* set1, T* set2, int length1, int length2);

    private:
        int set_size;                       // The number of items in the original set
        T* ori_set;                         // The set after construction

        std::pair<T, int>** hashtable;      // The hashtable after reorganization
        int hash_numitems;                   // length of hashtable
        int hash_maxsize;                   // defines the size of the hashtable
        void rehash(int newsize);

        std::pair<T, int>* placeholder;     // used as placeholder
};

/*
template<class T> MultiSet_Chaining{
    public:
        MultiSet_Chaining();
        /* You should add other functions to make the structure work  */



        /* The following is required for this assignment */
        /* It is not complete, you should design the APIs by yourself */
/*        void insertion();
        void deletion();
        T retrieval();

        T* setunion();
        T* intersection();
        T* difference();

    private:
    int numitems;
    T* reparray;
};
*/
#endif /* multiset_h */
