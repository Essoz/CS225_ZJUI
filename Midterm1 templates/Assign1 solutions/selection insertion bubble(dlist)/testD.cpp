//
//  mian.c for alist in Assignment 1
//  
//
//  Created by Xiong Neng on 21.01.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "dlist.cpp"
using namespace std;

int main() {
    DList<int> MyDList;
    int len = 15;
    for (int i = 0; i < len ; ++i) {
        MyDList.append(rand() % 10);
    }
    cout << "           The original list:";
    MyDList.print();
    MyDList.SelectionSort();
    cout << "The result of Selection Sort:";
    MyDList.print();

    cout << MyDList.bSearch(1,15,7) << endl;

    for (int i = 0; i < len ; ++i) {
        MyDList.setitem(i+1, rand() % 10);
    }
    cout << '\n' << "           The original list:";
    MyDList.print();
    MyDList.InsertionSort();
    cout << "The result of Insertion Sort:";
    MyDList.print();

    for (int i = 0; i < len ; ++i) {
        MyDList.setitem(i+1, rand() % 10);
    }

    cout << '\n' << "           The original list:";
    MyDList.print();
    MyDList.BubbleSort();
    cout << "   The result of Bubble Sort:";
    MyDList.print();

    // testing SelectionSort
    // This part test SelectionSort with 100 random cases and compare the result with InsertionSort
    // You can uncomment this part to see the outcome
    // for (int i = 0; i < 100; ++i) {
    //     DList<int> A;
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