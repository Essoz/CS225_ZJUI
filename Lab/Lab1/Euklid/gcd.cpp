//
//  gcd.cpp
//  
//
//  Created by KD on 08.01.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "gcd.h"
using std::cout;
using std::cin;

int euklid(int n, int m)
{
    if (n == m)
        return n;
    else
        if (n > m)
            return euklid(n - m, m);
    else
        return euklid(m - n, n);
}

int main()
{
    int n, m, gcd;
    cout << "Enter two positive integers.\n";
    cin >> n >> m;
    if (n >0 && m > 0)
    {
        gcd = euklid(n, m);
        cout << "The greatest common divisor of " << n << " and " << m << " is " << gcd << ".\n";
        return(EXIT_SUCCESS);
    }
    else
    {
        cout << "Error: one input " << n << " or " << m << " is 0 or negative.\n";
        exit(EXIT_FAILURE);
    }
}
