//
//  dlistmgt.cpp
//  
//
//  Created by KD on 23.01.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "dlistsort.cpp"
#include    <ctime>
using std::cout;
using std::cin;

int main()
{
    int type, op;
    int pos, yes;
    int intitem, result1;
    DListsort<int> mylist1 = DListsort<int>();
    DListsort<double> mylist2 = DListsort<double>();
    double doubleitem, result2;
    bool boolresult;
    do
    {
        cout << "Choose your element type:\n";
        cout << "0: int  1: double\n";
        cin >> type ;
        if ((type != 0) && (type != 1))
            cout << "You must choose 0 or 1\n\n";
    }
    while ((type != 0) && (type != 1));
    do
    {
        do
        {
            cout << "Choose an operation:\n";
            cout << "O: quit\n";
            cout << "1: list initializaiton\n";
            cout << "2: merge sort & insertion sort (for short list)\n";
            cout << "3: display\n";
            cin >> op ;
        }
        while ((op < 0) && (op > 3));
        switch(op)
        {
            case 0: return(0);
            case 1:
            {
                int length;
                cout << "array initialinzing, enter the total length (in integer) : \n";
                cin >> length;
                int v1;
                if (type == 0)
                {
                    for (int i = 0; i < length; i++)
                    {
                        v1 = rand() % 10000; 
                        mylist1.append(v1);
                    }
                }
                else
                {
                   for (int i = 0; i < length; i++)
                    {
                        v1 = (double) (rand() % 10000); 
                        mylist2.append(v1);
                    }
                }
                break;
            }
            case 2:
            {
                cout << "Enter a threshold value:\n";
                if (type == 0)
                {
                    cin >> intitem;
                    mylist1.mergesort(intitem);
                }
                else
                {
                    cin >> intitem;
                    mylist2.mergesort(intitem);
                }
                break;
            }
            case 3:
            {
                if (type == 0)
                {
                    int numelements = mylist1.getlength();
                    for (int i = 1; i <= numelements; ++i)
                    {
                        intitem = mylist1[i];
                        cout << "List element " << i << " is " << intitem <<".\n";
                    }
                }
                else
                {
                    int numelements = mylist2.getlength();
                    for (int i = 1; i <= numelements; ++i)
                    {
                        doubleitem = mylist2[i];
                        cout << "List element " << i << " is " << doubleitem <<".\n";
                    }
                }
                break;
            }
            default: return(0);
        }
    }
    while (op != 0);
    return(0);
}
