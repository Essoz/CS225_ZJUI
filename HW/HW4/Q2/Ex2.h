#ifndef Ex2_h
#define Ex2_h
#include<iostream>	
#include<math.h>
#include <cstdlib>
#include <map>
#include <vector>

// Define a structure to store the key value of a relation pair and the relation pair itself:
typedef struct Node_t
{
    int key;
    int value1;     // Two values in the relation pair, note value1 is the first value in the pair
    int value2;
} Node_t;

template<class T> class NumSet
{
public:
    NumSet(int * integer_set,int length);   
    ~NumSet();
    int Check_Relation(std::vector<std::pair<int,int> > R);
private:
    int *Set_A; 
    int Set_length;

    // Function that distribute the Relation Set_A into the hash table with length L:
    std::vector<std::vector<Node_t*> > Build_Hash(std::vector<std::pair<int,int> > R, int L);
    // Calculate the key value for a relation pair:
    int Calculate_Key(std::pair<int,int> P);
    // Build the structure for one pair:
    Node_t* Build_Str(int key, std::pair<int,int> P);
};

template<class T> NumSet<T>::NumSet(int *integer_set,int length)
{
    Set_A=(int *)malloc(sizeof(int) * length);
    Set_length=length;
    for (int i=0; i<length; i++)
        Set_A[i]=integer_set[i];
}

template<class T> NumSet<T>::~NumSet()
{
    delete[] Set_A;
}

#endif
