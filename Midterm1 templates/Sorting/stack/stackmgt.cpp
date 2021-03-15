//
//  stackmgt.cpp
//  
//
//  Created by KD on 17.01.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "stack.cpp"
using std::cout;
using std::cin;

int main()
{
    int type, size, op;
    // int pos, yes;
    int intitem;
    stack<int> stack1;
    stack<double> stack2;
    double doubleitem;
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
        size = 10;
    switch(type)
    {
        case 0:
        {
            stack<int> stack1 = stack<int>(size);
            break;
        }
        case 1:
        {
            stack<double> stack2 = stack<double>(size);
            break;
        }
    }
    do
    {
        do
        {
            cout << "Choose an operation:\n";
            cout << "O: quit\n";
            cout << "1: push\n";
            cout << "2: pop\n";
            cout << "3: top\n";
            cout << "4: isempty\n";
            cout << "5: getheight\n";
            cout << "6: display\n";
            cin >> op ;
        }
        while ((op < 0) && (op > 6));
        switch(op)
        {
            case 0: return(0);
            case 1:
            {
                cout << "Enter a value:\n";
                if (type == 0)
                {
                    cin >> intitem;
                    stack1.push(intitem);
                }
                else
                {
                    cin >> doubleitem;
                    stack2.push(doubleitem);
                }
                break;
            }
            case 2:
            {
                if (type == 0)
                {
                    intitem = stack1.pop();
                    cout << "The top element " << intitem << " was popped.\n";
                }
                else
                {
                    doubleitem = stack2.pop();
                    cout << "The top element " << doubleitem << " was popped.\n";
                }
                break;
            }
            case 3:
            {
                if (type == 0)
                {
                    intitem = stack1.top();
                    cout << "The top element is " << intitem << ".\n";
                }
                else
                {
                    doubleitem = stack2.top();
                    cout << "The top element is " << doubleitem << ".\n";
                }
                break;
            }
            case 4:
            {
                if (type == 0)
                    boolresult = stack1.isempty();
                else
                    boolresult = stack2.isempty();
                if (boolresult == true)
                    cout << "The stack is empty.\n";
                else
                    cout << "The stack is notempty.\n";
                break;
            }
            case 5:
            {
                if (type == 0)
                    intitem = stack1.getheight();
                else
                    intitem = stack2.getheight();
                cout << "The stack contains " << intitem << " elements.\n";
                break;
            }
            case 6:
            {
                cout << "The stack elements from top to bottom are:\n";
                if (type == 0)
                {
                    int num = stack1.getheight();
                    for (int i = num; i > 0; --i)
                    {
                        intitem = stack1[i];
                        cout << intitem <<"\n";
                    }
                }
                else
                {
                    int num = stack2.getheight();
                    for (int i = num; i > 0; --i)
                    {
                        doubleitem = stack2[i];
                        cout << doubleitem <<"\n";
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
