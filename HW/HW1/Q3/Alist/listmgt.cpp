//
//  listmgt.cpp
//  
//
//  Created by KD on 14.01.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "alist.cpp"
using std::cout;
using std::cin;

int main()
{
    int type, size, op;
    int pos, yes;
    int intitem, result1;
    AList<int> mylist1;
    AList<double> mylist2;
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
    cout << "Enter a positive integer for the size of your list:\n";
    cin >> size;
    if (size <= 0)
        size = 20;
    switch(type)
    {
        case 0:
        {
            AList<int> mylist1 = AList<int>(size);
            break;
        }
        case 1:
        {
            AList<double> mylist2 = AList<double>(size);
            break;
        }
    }
    do
    {
        do
        {
            cout << "Choose an operation:\n";
            cout << "O: quit\n";
            cout << "1: display\n";

            // For Exercise 3: 
            cout << "2: pushback\n";
            cout << "3: pushfront\n";
            cout << "4: popback\n";
            cout << "5: popfront\n";
            cin >> op ;
        }
        while ((op < 0) && (op > 11));
        switch(op)
        {
            case 0: return(0);
            case 1:
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

            // These are for Exercise 3:
            // pushback operation:
            case 2:
            {
                cout << "Enter a value:\n";
                if (type == 0)
                {
                    cin >> intitem;
                    mylist1.pushback(intitem);
                }
                else
                {
                    cin >> doubleitem;
                    mylist2.pushback(doubleitem);
                }
                break;
            }
            // pushfront operation:
            case 3:
            {
                cout << "Enter a value:\n";
                if (type == 0)
                {
                    cin >> intitem;
                    mylist1.pushfront(intitem);
                }
                else
                {
                    cin >> doubleitem;
                    mylist2.pushfront(doubleitem);
                }
                break;
            }
            // popback operation:
            case 4:
            {
                if (type == 0)
                {
                    result1 = mylist1.popback();

                    // Check if the function succeeds:
                    if (0 == result1 && 0 == mylist1.getlength())
                    {
                        cout << "The array is already empty.\n";
                        break;
                    }

                    // Print the last value:
                    cout << "You get the last value stored, it is: ";
                    cout << result1 << "\n";
                }
                else
                {
                    result2 = mylist2.popback();

                    // Check if the function succeeds:
                    if (0 == result2 && 0 == mylist2.getlength())
                    {
                        cout << "The array is already empty.\n";
                        break;
                    }

                    // Print the last value:
                    cout << "You get the last value stored, it is: ";
                    cout << result2 << "\n";
                }
                break;
            }
            // popfront operation:
            case 5:
            {
                if (type == 0)
                {
                    result1 = mylist1.popfront();

                    // Check if the function succeeds:
                    if (0 == result1 && 0 == mylist1.getlength())
                    {
                        cout << "The array is already empty.\n";
                        break;
                    }

                    // Print the first value:
                    cout << "You get the first value stored, it is: ";
                    cout << result1 << "\n";
                }
                else
                {
                    result2 = mylist2.popfront();

                    // Check if the function succeeds:
                    if (0 == result2 && 0 == mylist2.getlength())
                    {
                        cout << "The array is already empty.\n";
                        break;
                    }
                    
                    // Print the first value:
                    cout << "You get the first value stored, it is: ";
                    cout << result2 << "\n";
                }
                break;
            }
            default: return(0);
        }
    }
    while (op != 0);
    return(0);
}
