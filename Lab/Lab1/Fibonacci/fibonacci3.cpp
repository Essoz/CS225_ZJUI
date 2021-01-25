//
//  fibonacci3.cpp
//  
//
//  Created by KD on 08.01.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "fibonacci3.h"
using std::cout;
using std::cin;

long fib3(int n)
{
    long i = 1, j = 0, h = 1, k = 0;
    long temp;
    while (n > 0)
    {
        if (n % 2 != 0)
        {
            temp = j * h;
            j = i * h + j * k + temp;
            i = i * k + temp;
        }
        temp = h * h;
        h = 2 * k * h + temp;
        k = k * k + temp;
        n = n / 2;
    }
    return j;
}

int main()
{
    int n;
    long f;
    cout << "Enter a non-negative integer.\n";
    cin >> n;
    if (n >=0)
    {
        f = fib3(n);
        cout << "The " << n << "th Fibonacci number is " << f << " .\n";
        return(EXIT_SUCCESS);
    }
    else
    {
        cout << "Error: Input " << n << " is negative.\n";
        exit(EXIT_FAILURE);
    }
}
