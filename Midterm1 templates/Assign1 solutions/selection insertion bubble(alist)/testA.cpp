//
//  mian.c for alist in Assignment 1
//  
//
//  Created by Xiong Neng on 21.01.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "alist.cpp"
using namespace std;

int main() {
    AList<int> MyAList;
    int len = 15;
    for (int i = 0; i < len ; ++i) {
        MyAList.append(rand() % 10);
    }
    cout << "           The original list:";
    MyAList.print();
    MyAList.SelectionSort();
    cout << "The result of Selection Sort:";
    MyAList.print();

    cout << MyAList.bSearch(1,15,7) << endl;

    for (int i = 0; i < len ; ++i) {
        MyAList.setitem(i+1, rand() % 10);
    }
    cout << '\n' << "           The original list:";
    MyAList.print();
    MyAList.InsertionSort();
    cout << "The result of Insertion Sort:";
    MyAList.print();

    for (int i = 0; i < len ; ++i) {
        MyAList.setitem(i+1, rand() % 10);
    }

    cout << '\n' << "           The original list:";
    MyAList.print();
    MyAList.BubbleSort();
    cout << "   The result of Bubble Sort:";
    MyAList.print();

    // testing SelectionSort
    // This part test SelectionSort with 100 random cases and compare the result with InsertionSort
    // You can uncomment this part to see the outcome
    // for (int i = 0; i < 100; ++i) {
    //     AList<int> A;
    //     for (int j = 0; j < 20; ++j) A.append(rand()%50);

    //     A.print();
    //     A.InsertionSort();
    //     A.print();
    //     A.SelectionSort();
    //     A.print();

    //     cout << endl;
    // }

    return 0;
}
