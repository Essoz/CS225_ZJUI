//
//  fibonacci2.cpp
//  
//
//  Created by KD on 08.01.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "fibonacci2.h"
using std::cout;
using std::cin;

int fib2(int n)
{
    if (n < 2)
        return(n);
    else return(fib2(n-1)+fib2(n-2));
}

int main()
{
    int n, f;
    cout << "Enter a non-negative integer.\n";
    cin >> n;
    if (n >=0)
    {
        f = fib2(n);
        cout << "The " << n << "th Fibonacci number is " << f << " .\n";
        return(EXIT_SUCCESS);
    }
    else
    {
        cout << "Error: Input " << n << " is negative.\n";
        exit(EXIT_FAILURE);
    }
}
