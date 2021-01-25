//
//  intbubble.cpp
//  
//
//  Created by KD on 08.01.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "intbubble.h"
using std::cout;
using std::cin;

template<class T> void swap(T *pt_x, T *pt_y)
{
    T temp;
    temp = *pt_x;
    *pt_x = *pt_y;
    *pt_y = temp;
}

template<class T> void bubblesort(T pt[], int n)
{
    T *pt_end1, *pt_end2, *pt_rest;
    pt_end2 = pt + n;
    pt_end1 = pt_end2 - 1;
    while (pt < pt_end1)
    {
        pt_rest = pt + 1;
        while (pt_rest < pt_end2)
        {
            if (*pt > *pt_rest)
                swap(pt, pt_rest);
            ++pt_rest;
        }
        ++pt;
    }
}

int main()
{
    int a[100];
    double b[100], x = 3.937e2;
    for (int i = 0; i < 100; ++i)
    {
        a[i] = (35 * i * i * (49 - i)) % 97;
        b[i] = x * i * (13 - i * i) + 1.0 / x;
    }
    bubblesort<int>(&a[33], 50);
    bubblesort<double>(b, 97);
    for (int i = 0; i < 100; ++i)
    {
        cout << "a[" << i << "] = " << a[i] << "\n";
    }
    cout << "\n";
    for (int i = 0; i < 100; ++i)
    {
        cout << "b[" << i << "] = " << b[i] << "\n";
    }
}
