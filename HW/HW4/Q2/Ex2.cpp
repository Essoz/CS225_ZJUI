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
    // First, build a hash table with length 20 for that relation set:
    vector<vector<Node_t*> > hash_table;
    hash_table = Build_Hash(R, 20);

    // Second, given one pair (a,b), we need to check if the (b,a) is in the hash table:
    for (int i = 0; i < int(R.size()); i++)
    {
        // We do not need to check the pair like (a,a) since it is already symmetric:
        if (R[i].first == R[i].second)
        {
            continue;
        }

        int key = Calculate_Key(R[i]);
        int h_value = key % 20;
        int check = 0;

        // Find the entry with proper hash value:
        for (int j = 0; j < int(hash_table[h_value].size()); j++)
        {
            // Check for key and both values:
            if (key != hash_table[h_value][j]->key || R[i].second != hash_table[h_value][j]->value1 || R[i].first != hash_table[h_value][j]->value2)
            {
                continue;
            }

            check = 1;
            break;
        }

        if (check == 0)
        {
            return 0;
        }
    }

    return 1;
};

// Build the hash table:
template<class T> vector<vector<Node_t*> > NumSet<T>::Build_Hash(vector<std::pair<int,int> > R, int L){
    vector<vector<Node_t*> > result(L);              // Define the result vector

    // Loop through all pairs in the set:
    for (int i = 0; i < int(R.size()); i++)
    {
        // We do not need to check the pair like (a,a) since it is already symmetric:
        if (R[i].first == R[i].second)
        {
            continue;
        }

        // Calculate the key value for the current pair:
        int key = Calculate_Key(R[i]);
        // Build the structure for the current pair:
        Node_t* node = Build_Str(key, R[i]);
        // Get the hash value using hash function with mod:
        int h_value = key % L;
        // Add the new structure to the hash table:
        result[h_value].push_back(node);
    }

    return result;
}

// Calculate the key value:
template<class T> int NumSet<T>::Calculate_Key(std::pair<int,int> P){
    return (P.first ^ P.second);       // We use XOR function for the key value of the pair
}

// Build the structure for one pair:
template<class T> Node_t* NumSet<T>::Build_Str(int key, std::pair<int,int> P){
    Node_t* node = new Node_t;
    node->key = key;
    node->value1 = P.first;
    node->value2 = P.second;
    return node;
}

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