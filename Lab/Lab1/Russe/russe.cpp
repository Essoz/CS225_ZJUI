//
//  russe.cpp
//  
//
//  Created by KD on 08.01.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "russe.h"
using std::cout;
using std::cin;

int russianmult(int n, int m)
{
    int s = 0;
    do
    {
        if (m % 2 != 0)
            s += n;
        n *= 2;
        m /= 2;
    }
    while (m != 0);
    return s;
}

int main()
{
    int n, m, p;
    cout << "Enter two non-negative integers.\n";
    cin >> n >> m;
    if (n >=0 && m >= 0)
    {
        p = russianmult(n, m);
        cout << "The product " << n << " * " << m << " is " << p << ".\n";
        return(EXIT_SUCCESS);
    }
    else
    {
        cout << "Error: one input " << n << " or " << m << " is negative.\n";
        exit(EXIT_FAILURE);
    }
}
