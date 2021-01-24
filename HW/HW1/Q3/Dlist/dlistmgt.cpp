//
//  dlistmgt.cpp
//  
//
//  Created by KD on 14.01.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "dlist.cpp"
using std::cout;
using std::cin;

int main()
{
    int type, op;
    int pos, yes;
    int intitem, result1;
    DList<int> mylist1 = DList<int>();
    DList<double> mylist2 = DList<double>();
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
                    node<int>* lst_node;
                    lst_node = mylist1.popback();

                    // Check if the function succeeds:
                    if (NULL == lst_node)
                    {
                        cout << "The list is already empty.\n";
                        break;
                    }
                    
                    cout << "You get the last node, the value stored is: ";

                    // Print the value stored in the last node:
                    result1 = lst_node->getdata();
                    cout << result1 << "\n";
                }
                else
                {
                    node<double>* lst_node;
                    lst_node = mylist2.popback();

                    // Check if the function succeeds:
                    if (NULL == lst_node)
                    {
                        cout << "The list is already empty.\n";
                        break;
                    }
                    
                    cout << "You get the last node, the value stored is: ";

                    // Print the value stored in the last node:
                    result2 = lst_node->getdata();
                    cout << result2 << "\n";
                }
                break;
            }
            // popfront operation:
            case 5:
            {
                if (type == 0)
                {
                    node<int>* fst_node;
                    fst_node = mylist1.popfront();

                    // Check if the function succeeds:
                    if (NULL == fst_node)
                    {
                        cout << "The list is already empty.\n";
                        break;
                    }
                    
                    cout << "You get the first node, the value stored is: ";

                    // Print the value stored in the last node:
                    result1 = fst_node->getdata();
                    cout << result1 << "\n";
                }
                else
                {
                    node<double>* fst_node;
                    fst_node = mylist2.popfront();

                    // Check if the function succeeds:
                    if (NULL == fst_node)
                    {
                        cout << "The list is already empty.\n";
                        break;
                    }
                    
                    cout << "You get the first node, the value stored is: ";

                    // Print the value stored in the last node:
                    result2 = fst_node->getdata();
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
