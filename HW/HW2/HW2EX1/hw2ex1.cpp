#include "hw2ex1.h"
#include <vector>
#include <iostream>
#include <stdio.h>
#include <cstdlib>

int main(){
    // ============ test 1 ==============
    Solution<int> test1 = Solution<int>(vector<int>({1, 3, 2,8, 0, 10, 4, 100, 90}));
    cout << "Test 1:" << endl << "Input: ";
    test1.vec_print(test1.data);
    cout << "Gold Output:" << "0  1  2  3  4  8  10  90  100" << endl << endl; 
    test1.test(4, 2);

    // ============ test 2 ==============
    Solution<float> test2 = Solution<float>(vector<float>({2.5, 3.4, 1.9, 7.8, 3.9, 1, 9, 0, -1.7}));
    cout << "\n \n Test 2:" << endl << "Input:         ";
    test2.vec_print(test2.data);
    cout << "Gold Output:        " << " -1.7  0  1  1.9  2.5  3.4  3.9  7.8  9" << endl << "--------------" << endl; 
    test2.test(4, 4);


    // You could add your own test example
    return 0;


}