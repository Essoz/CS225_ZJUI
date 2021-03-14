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
    // First, build a hash table with length N/20 for input relation set:
    vector<vector<Node_t*> > hash_table;
    hash_table = Build_Hash(R, 20);

    /* For debugging:
    for (int i = 0; i < int(hash_table.size()); i++)
    {
        std::cout << int(hash_table[i].size()) << std::endl; 
    }
    */

    // Second, we need to check if the relation is symmetric:
    // If one of the entries of hash table has odd length, then the relation must not be symmetric:
    for (int i = 0; i < int(hash_table.size()); i++)
    {
        if (1 == int(hash_table[i].size()) % 2)
        {
            return 0;
        }
    }

    // If all entries have even length, we loop through all the entries:
    for (int i = 0; i < int(hash_table.size()); i++)
    {
        // For one entry:
        while (0 < int(hash_table[i].size()))
        {
            int check = 0;          // Check if the list has (b,a) to match the first pair (a,b)
            // Locate the matching pair:
            for (int k = 1; k < int(hash_table[i].size()); k++)
            {
                // Check for both key and values:
                if (hash_table[i][k]->key != hash_table[i].front()->key 
                    || hash_table[i][k]->relation_pair.second != hash_table[i].front()->relation_pair.first 
                    || hash_table[i][k]->relation_pair.first != hash_table[i].front()->relation_pair.second)
                {
                    continue;       // Not match, move to the next pair
                }

                // Reach here, means symmetric tuple found, we delete both tuples:
                hash_table[i].erase(hash_table[i].begin()+k);
                hash_table[i].erase(hash_table[i].begin());
                check = 1;
                break;      // Move on to the next "first relation pair"
            }

            if (0 == check)
            {
                return 0;
            }
        }
        // std::cout << int(hash_table[i].size()) << std::endl;
    }

    return 1;
};

// Build the hash table:
template<class T> vector<vector<Node_t*> > NumSet<T>::Build_Hash(vector<std::pair<int,int> > R, int L){
    int length = int(R.size()) / L;                       // Length of the hash table
    vector<vector<Node_t*> > result(length);              // Define the result vector

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
        int h_value = key % length;
        // Add the new structure to the hash table:
        result[h_value].push_back(node);
    }

    return result;
}

// Calculate the key value:
template<class T> int NumSet<T>::Calculate_Key(std::pair<int,int> P){
    return (P.first * P.second) >> 2;       // We use product and right shift for the key value of the pair
}

// Build the structure for one pair:
template<class T> Node_t* NumSet<T>::Build_Str(int key, std::pair<int,int> P){
    Node_t* node = new Node_t;
    node->key = key;
    node->relation_pair = P;
    return node;
}

int main(){
    int Set_A[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,100};
    NumSet<int> S(Set_A,20);
    //Here is for Test 1
    vector<pair<int,int> > Relation_R1;
    for (int i=0; i<20; i++){
        Relation_R1.push_back(make_pair(Set_A[i],Set_A[i]));
        for (int j=0; j<20; j++){
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