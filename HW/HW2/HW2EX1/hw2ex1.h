/*
 * @ Author     : 
 * 
 * @ File       : 
 * 
 * @ Purpose    : 
 * 
 * @ Usage      : 
 * 
 * @ Description: 
 * 
 * @ Input      : 
 * 
 * @ Output     : 
 * 
 */
#ifndef ex1
#define ex1

#include <iostream>
#include <vector>
using namespace std;

// You may modify the decleration and definenation by yourself, add help function etc.
template <class T> class Solution {
    public:
        Solution(vector<T> input){
            data = input;
        };

        vector<T> MergeSort_k(vector<T> lst, int k);
        vector<T> MergeSort_t(vector<T> lst, int t);
        vector<T> SelfSort(vector<T> lst);
        void vec_print(vector<T> vec);
        vector<T> data;
        void test(int k, int t);
    private:
        
};

// Modify the following to finish ex1.1
template <class T> vector<T> Solution<T>::MergeSort_k(vector<T> lst, int k){
    
};




// Modify the following to finish ex1.2
template<class T> vector<T> Solution<T>::MergeSort_t(vector<T> lst, int t){
   
}

// You could implement either bubble sort, insert sort or selection sort
template<class T> vector<T> Solution<T>::SelfSort(vector<T> lst){
    
}

// DO NOT modify the following
// This is to view the vector
template<class T> void Solution<T>::vec_print(vector<T> vec){
    for (T i: vec){
        cout << i << "  ";
    }
    cout << endl;
    return ;
}

// This is for testing.
template <class T> void Solution<T>::test(int k, int t){
    cout << "Self-implemented Sort:          ";
    vec_print(SelfSort(data));
    cout << "Merge Sort with K sublist:      ";
    vec_print(MergeSort_k(data, k));
    cout << "Merge Sort with Insertion Sort: ";
    vec_print(MergeSort_t(data, t));
}
#endif 

