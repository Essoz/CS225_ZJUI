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
    int type, size, op, k, length;
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
            AList<int> mylist2 = AList<int>(size);
            break;
        }
    }
    do
    {
        do
        {
            cout << "Choose an operation:\n";
            cout << "O: quit\n";
            cout << "1: array initialization\n";
            cout << "2: insert\n";
            cout << "3: delete\n";
            cout << "4: set\n";
            cout << "5: get\n";
            cout << "6: in\n";
            cout << "7: length\n";
            cout << "8: concat\n";
            cout << "9: sublist\n";
            cout << "10: equal\n";
            cout << "11: display\n";
            cout << "12: delete the last k elements\n";
            cout << "13: implement the selection sort\n";
            cout << "14: implement the bubble sort\n";
            cin >> op ;
        }
        while ((op < 0) && (op > 11));
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
                    if (mylist1.getlength()!=0)
                    {
                        mylist1.remove_k_elements(mylist1.getlength());
                    }
                    
                    for (int i = 0; i < length; i++)
                    {
                        v1 = rand() % 10000; 
                        mylist1.append(v1);
                    }
                }
                else
                {
                   if (mylist2.getlength()!=0)
                    {
                        mylist2.remove_k_elements(mylist2.getlength());
                    }
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
                cout << "Enter a position and a value:\n";
                cin >> pos;
                if (type == 0)
                {
                    cin >> intitem;
                    mylist1.insert(pos, intitem);
                }
                else
                {
                    cin >> doubleitem;
                    mylist2.insert(pos, doubleitem);
                }
                break;
            }
            case 3:
            {
                cout << "Enter a position:\n";
                cin >> pos;
                if (type == 0)
                    mylist1.remove(pos);
                else
                    mylist2.remove(pos);
                break;
            }
            case 4:
            {
                cout << "Enter a position and a value:\n";
                cin >> pos;
                if (type == 0)
                {
                    cin >> intitem;
                    mylist1.setitem(pos, intitem);
                }
                else
                {
                    cin >> doubleitem;
                    mylist2.setitem(pos, doubleitem);
                }
                break;
            }
            case 5:
            {
                cout << "Enter a position:\n";
                cin >> pos;
                if (type == 0)
                {
                    result1 = mylist1.getitem(pos);
                    cout << result1 << "\n";
                }
                else
                {
                    result2 = mylist2.getitem(pos);
                    cout << result2 << "\n";
                }
                break;
            }
            case 6:
            {
                cout << "Enter a value:\n";
                if (type == 0)
                {
                    cin >> intitem;
                    boolresult = mylist1.member(intitem);
                }
                else
                {
                    cin >> doubleitem;
                    boolresult = mylist2.member(doubleitem);
                }
                cout << boolresult << "\n";
                break;
            }
            case 7:
            {
                if (type == 0)
                    result1 = mylist1.getlength();
                else
                    result1 = mylist2.getlength();
                cout << result1 << "\n";
                break;
            }
            case 8:
            {
                if (type == 0)
                {
                    AList<int> mylistnew1 = AList<int>(10);
                    do
                    {
                        cout << "Do you want to enter more list elements?\n";
                        cout << "1: yes  anything else: no\n";
                        cin >> yes;
                        if (yes == 1)
                        {
                            cout << "Enter a value for your new list:\n";
                            cin >> intitem;
                            mylistnew1.append(intitem);
                        }
                    }
                    while (yes == 1);
                    mylist1.concat(mylistnew1);
                }
                else
                {
                    AList<double> mylistnew2 = AList<double>(10);
                    do
                    {
                        cout << "Do you want to enter more list elements?\n";
                        cout << "1: yes  anything else: no\n";
                        cin >> yes;
                        if (yes == 1)
                        {
                            cout << "Enter a value for your new list:\n";
                            cin >> doubleitem;
                            mylistnew2.append(doubleitem);
                        }
                    }
                    while (yes == 1);
                    mylist2.concat(mylistnew2);
                }
                break;
            }
            case 9:
            {
                if (type == 0)
                {
                    AList<int> mylistnew1 = AList<int>(10);
                    do
                    {
                        cout << "Do you want to enter more list elements?\n";
                        cout << "1: yes  anything else: no\n";
                        cin >> yes;
                        if (yes == 1)
                        {
                            cout << "Enter a value for your new list:\n";
                            cin >> intitem;
                            mylistnew1.append(intitem);
                        }
                    }
                    while (yes == 1);
                    boolresult = mylist1.sublist(mylistnew1);
                }
                else
                {
                    AList<double> mylistnew2 = AList<double>(10);
                    do
                    {
                        cout << "Do you want to enter more list elements?\n";
                        cout << "1: yes  anything else: no\n";
                        cin >> yes;
                        if (yes == 1)
                        {
                            cout << "Enter a value for your new list:\n";
                            cin >> doubleitem;
                            mylistnew2.append(doubleitem);
                        }
                    }
                    while (yes == 1);
                    boolresult = mylist2.sublist(mylistnew2);
                }
                if (boolresult == true)
                {
                    cout << "The new list is a sublist.\n";
                }
                else
                    cout << "The new list is not a sublist.\n";
                break;
            }
            case 10:
            {
                if (type == 0)
                {
                    AList<int> mylistnew1 = AList<int>(10);
                    do
                    {
                        cout << "Do you want to enter more list elements?\n";
                        cout << "1: yes  anything else: no\n";
                        cin >> yes;
                        if (yes == 1)
                        {
                            cout << "Enter a value for your new list:\n";
                            cin >> intitem;
                            mylistnew1.append(intitem);
                        }
                    }
                    while (yes == 1);
                    boolresult = mylist1.equal(mylistnew1);
                }
                else
                {
                    AList<double> mylistnew2 = AList<double>(10);
                    do
                    {
                        cout << "Do you want to enter more list elements?\n";
                        cout << "1: yes  anything else: no\n";
                        cin >> yes;
                        if (yes == 1)
                        {
                            cout << "Enter a value for your new list:\n";
                            cin >> doubleitem;
                            mylistnew2.append(doubleitem);
                        }
                    }
                    while (yes == 1);
                    boolresult = mylist2.sublist(mylistnew2);
                }
                if (boolresult == true)
                {
                    cout << "The new list is equal.\n";
                }
                else
                    cout << "The new list is not equal.\n";
                break;
            }
            case 11:
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
            case 12:
            {
                cout << "enter a number k that is smaller than the total lenth\n";
                cout << "total lenth is ";
                if (type == 0)
                    result1 = mylist1.getlength();
                else
                    result1 = mylist2.getlength();
                cout << result1 << "\n";
                cin >> k;
                if (k > result1)
                {
                    cout << "your number is greater than the total length\n";
                    break;
                }
                else
                {
                    if(type==0)
                    {
                        mylist1.remove_k_elements(k);
                        length= mylist1.getlength();
                    }
                    else
                    {
                        mylist2.remove_k_elements(k);
                        length= mylist2.getlength();
                    }
                }    
                break;
            }
            case 13:
            {
                if (type==0)
                {
                    mylist1.selection_sorting();
                }
                else
                {
                    mylist2.selection_sorting();
                }
                
                break;
            }
            case 14:
            {
                if (type==0)
                {
                    mylist1.bubblesort();
                }
                else
                {
                    mylist2.bubblesort();
                }
                break;
            }
            default: return(0);
        }
    }
    while (op != 0);
    return(0);
}
