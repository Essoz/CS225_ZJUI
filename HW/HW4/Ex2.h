#ifndef Ex2_h
#define Ex2_h
#include<iostream>	
#include<math.h>
#include <cstdlib>
#include <map>
#include <vector>
template<class T> class NumSet
{
public:
    NumSet(int * integer_set,int length);   
    ~NumSet();
    int Check_Relation(std::vector<std::pair<int,int> > R);
private:
    int *Set_A; 
    int Set_length;    
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
