/*
 * @ Author     : Tianyu Zhang
 * 
 * @ File       : HW2/Q1
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
#include <time.h>
#include <stdlib.h>
using namespace std;

#define MAX 100


// You may modify the decleration and definenation by yourself, add help function etc.
template <class T> class Solution {
    public:
        Solution(vector<T> input){
            data = input;
            number_item = set_item(input);
        };

        vector<T> MergeSort_k(vector<T> lst, int k);
        vector<T> MergeSort_t(vector<T> lst, int t);
        vector<T> SelfSort(vector<T> lst);
        void vec_print(vector<T> vec);
        vector<T> data;
        void test(int k, int t);

        // Set the number of items in the solution list:
        int set_item(vector<T> lst);
        // Compare the speed of the Selfsort and Mergesort for a list with certain length:
        int compare_time(vector<T> lst);
        // Find the t value for the best performance within "max" value:
        static void find_t(int max);

    private:
        int number_item;    // The length of solution vector

        // Divide vector into k subvectors:
        vector<vector<T>> divide_k(vector<T> lst, int k, int l);
        // Merge k sorted subvectors into one sorted vector:
        vector<T> merge(vector<vector<T>> combined_list);
};


// Set the number of items in the solution list:
template <class T> int Solution<T>::set_item(vector<T> lst){
    return int(lst.size());
}


// Modify the following to finish ex1.1
template <class T> vector<T> Solution<T>::MergeSort_k(vector<T> lst, int k){
    // vec_print(lst);
    int numitems = Solution<T>::number_item;    // Total number of items in the vector
    int eachlength = numitems / k;              // The length of each subvector
    // Divide the input vector into k subvectors. Since k may not divide numitems, the last
    // subvector might have a different length:
    vector<vector<T>> concentrate;              // A vector conbining all the subvectors
    concentrate = divide_k (lst, k, eachlength);

    // Then, apply the mergesort to all items in the "concentrate" vector:
    for (int i = 0; i < int(concentrate.size()); i++){
        // No need to do further sort for the vector containing only 1 item:
        if (2 > concentrate[i].size()){
            continue;
        }
        concentrate[i] = MergeSort_k(concentrate[i], k);
    }

    // Now for merge operation:
    vector<T> Merged_list = merge(concentrate);
    vec_print(Merged_list);
    return Merged_list;
};


// Divide the vector into k subvectors:
template <class T> vector<vector<T>> Solution<T>::divide_k(vector<T> lst, int k, int l){
    vector<vector<T>> combine;                  // The return vector

    // We do not need to split if there is only 1 element:
    if (2 > int(lst.size())){
        combine.push_back(lst);
        return combine;
    }

    // Fill in the new vector:
    // First, we need to check if the vector can be split into k subvectors:
    if (int(lst.size()) < k){
        // If so, change the divisor k to the number of items in the vector:
        return divide_k(lst, int(lst.size()), 1);
    }

    // Else, we do as following:
    // First, fill in the first k-1 subvectors:
    for (int i = 0; i < k-1; i++){
        vector<T> tem;
        for (int j = i*l; j < (i+1)*l; j++){
            tem.push_back(lst[j]);
        }
        combine.push_back(tem);
    }
    
    // Fill the last subvector:
    vector<T> tem;
    for (int i = (k-1)*l; i < int(lst.size()); i++){
        tem.push_back(lst[i]);
    }
    combine.push_back(tem);
    return combine;
}


// Merge k (maybe smaller than k) sorted subvectors into one sorted vector:
template <class T> vector<T> Solution<T>::merge(vector<vector<T>> combined_list){
    vector<T> merged;                   // The returned vector
    int smallest_i;
    T smallest_item;

    // Do the following steps until the combined list gets empty:
    while (0 == combined_list.empty()){
        // If there is only one vector left, just add it to the merged list:
        if (1 == int(combined_list.size())){
            // vec_print(combined_list.front());
            for (int i = 0; i < int(combined_list.front().size()); i++){
                merged.push_back(combined_list.front()[i]);
                // vec_print(merged);
            }
            break;
        }

        smallest_i = 0;                 // Initialize the smallest item
        smallest_item = combined_list[0].front();

        // Compare the first element in all subvectors, and add the smallest one to the final vector:
        for (int i = 0; i < int(combined_list.size()); i++){
            if (smallest_item > combined_list[i].front()){
                smallest_item = combined_list[i].front();
                smallest_i = i;
            }
        }

        // Push the smallest one
        merged.push_back(smallest_item);
        // vec_print(merged);
        // Remove that item in the list
        combined_list[smallest_i].erase(combined_list[smallest_i].begin());

        // If the subvector becomes empty, remove it as well:
        if (1 == combined_list[smallest_i].empty()){
            combined_list.erase(combined_list.begin()+smallest_i);
        }
    }

    return merged;
}


// Modify the following to finish ex1.2
template<class T> vector<T> Solution<T>::MergeSort_t(vector<T> lst, int t){
    // Check if the length is greater than the threshold:
    if (t < int(lst.size())){
        return SelfSort(lst);
    }
    // If the length is greater, then use the mergesort splitting the list into 2 sublists:
    return MergeSort_k(lst, 2);
}


// You could implement either bubble sort, insert sort or selection sort
template<class T> vector<T> Solution<T>::SelfSort(vector<T> lst){
    // We implement the selection sort here:
    vector<T> result;
    T smallest_item;
    int smallest_index;

    // Perform the loop when the list is not empty:
    while (0 < int(lst.size())){
        // Find the smallest item in the list, and add the smallest one to the final vector:
        smallest_index = 0;
        smallest_item = lst.front();
        for (int i = 0; i < int(lst.size()); i++){
            if (smallest_item > lst[i]){
                smallest_item = lst[i];
                smallest_index = i;
            }
        }

        result.push_back(smallest_item);
        // For each loop, delete the smallest item:
        lst.erase(lst.begin()+smallest_index);
    }

    return result;
}


// Compare the speed of the Selfsort and Mergesort for a list (Note: For testing the type is vector<int>) with certain length:
template<class T> int Solution<T>::compare_time(vector<T> lst){
    // For selection sort:
    clock_t start1, end1;
    start1 = clock();
    SelfSort(lst);
    end1 = clock();
    double endtime1 = (double)(end1-start1)/CLOCKS_PER_SEC;
    cout << endtime1 << endl;

    // For Mergesort:
    clock_t start2, end2;
    start2 = clock();
    MergeSort_k(lst, 2);
    end2 = clock();
    double endtime2 = (double)(end2-start2)/CLOCKS_PER_SEC;
    cout << endtime2;

    // Compare and output the result:
    cout << "For the vector with length " << int(lst.size()) << ":" << endl;
    if (endtime1 >= endtime2){
        cout << "Mergesort is faster." << endl;
        return 1;
    } else {
        cout << "Selection sort is faster." << endl;
        return 0;
    }
}


// Find the t value for the best performance:
template<class T> void Solution<T>::find_t(int max){
    int cur_result = 0;
    int pre_result = 0;
    
    // Loop through the vectors with all possible lengths to find the t:
    // Note: Starting from i = 10 since in small length, the uncertainty is significant.
    for (int i = 10; i <= max; i++){
        // Create a vector with length i, and add random numbers into it:
        vector<T> test;
        for (int j = 0; j < i; j++){
            test.push_back(rand() % MAX);
        }
        cout << int(test.size())<<endl;

        // Create a class instance and call the functions:
        Solution<int> Test = Solution<int>(test);
        pre_result = cur_result;
        // cur_result = Test.compare_time(Test.data);

        // When the two results are different, we find the t value:
        if (pre_result != cur_result){
            cout << "The best t is: " << i-1;
            break;
        }
    }

    return;
}


// DO NOT modify the following
// This is to view the vector
template<class T> void Solution<T>::vec_print(vector<T> vec){
    for (T i: vec){
        cout << i << "  ";
    }
    cout << endl;
    return;
}


// This is for testing.
template <class T> void Solution<T>::test(int k, int t){
    cout << "Self-implemented Sort:          ";
    vec_print(SelfSort(data));
    cout << "Merge Sort with K sublist:      ";
    vec_print(MergeSort_k(data, k));
    cout << "Merge Sort with Selection Sort: ";
    vec_print(MergeSort_t(data, t));
}
#endif 
