//
//  fibonacci1.cpp
//  
//
//  Created by KD on 08.01.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "fibonacci1.h"
using std::cout;
using std::cin;

int fib1(int n)
{
    int i = 1, j = 0;
    for (int k = 1; k <= n; ++k)
    {
        j = i + j;      // f(n+1) = f(n-1) + f(n)
        i = j - i;      // f(n) = f(n+1) - f(n-1)
    }
    return j;
}

int main()
{
    int n, f;
    cout << "Enter a non-negative integer.\n";
    cin >> n;
    if (n >=0)
    {
        f = fib1(n);
        cout << "The " << n << "th Fibonacci number is " << f << " .\n";
        return(EXIT_SUCCESS);
    }
    else
    {
        cout << "Error: Input " << n << " is negative.\n";
        exit(EXIT_FAILURE);
    }
}
