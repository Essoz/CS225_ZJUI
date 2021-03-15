#include<iostream>	
#include<math.h>
#include <cstdlib>
#include <map>
#include <vector>
#include "Ex2.h"
using namespace std;
template<class T> int NumSet<T>::Check_Relation(vector<pair<int,int> > R){
    /*
    Input:
        R: The relation to be checked. Each element in R is a pair(int,int)
    Output:
        0: The binary relation R is not symmetric
        1: The binary relation R is symmetric
    */
   
   return 1;
};
int main(){
    int Set_A[10]={1,2,3,4,5,6,7,8,9,10};
    NumSet<int> S(Set_A,10);
    //Here is for Test 1
    vector<pair<int,int> > Relation_R1;
    for (int i=0; i<10; i++){
        Relation_R1.push_back(make_pair(Set_A[i],Set_A[i]));
        for (int j=0; j<10; j++){
            if (i != j)
                Relation_R1.push_back(make_pair(Set_A[i],Set_A[j]));
        }
    }
    cout << "For Test 1:"<<endl;
    cout << "The correct answer should be Yes"<<endl;
    cout << "Your answer is:" << ((S.Check_Relation(Relation_R1) == 1)?"Yes":"No")<< endl;
    //Here is for Test 2
    vector<pair<int,int> > Relation_R2;
    for (int i=0; i<10; i++){
        Relation_R2.push_back(make_pair(Set_A[i],Set_A[i]));
        for (int j=0; j<10; j++){
            if ((i != j) && (j%2 != 1))
                Relation_R2.push_back(make_pair(Set_A[i],Set_A[j]));
        }
    }
    cout << "For Test 2:"<<endl;
    cout << "The correct answer should be No"<<endl;
    cout << "Your answer is:" << ((S.Check_Relation(Relation_R2)== 1)?"Yes":"No")<< endl;
    
    return 0;
}