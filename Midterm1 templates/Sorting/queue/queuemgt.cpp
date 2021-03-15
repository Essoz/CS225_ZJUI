//
//  queuemgt.cpp
//  
//
//  Created by KD on 18.01.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "fifo.cpp"
using std::cout;
using std::cin;

int main()
{
    int type, size, op;
    // int pos, yes;
    int intitem;
    fifo<int> queue1;
    fifo<double> queue2;
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
    cout << "Enter a positive integer for the size of your queue:\n";
    cin >> size;
    if (size <= 0)
        size = 10;
    switch(type)
    {
        case 0:
        {
            fifo<int> queue1 = fifo<int>(size);
            break;
        }
        case 1:
        {
            fifo<double> queue2 = fifo<double>(size);
            break;
        }
    }
    do
    {
        do
        {
            cout << "Choose an operation:\n";
            cout << "O: quit\n";
            cout << "1: pushback\n";
            cout << "2: popfront\n";
            cout << "3: front\n";
            cout << "4: back\n";
            cout << "5: isempty\n";
            cout << "6: getlength\n";
            cout << "7: display\n";
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
                    queue1.pushback(intitem);
                }
                else
                {
                    cin >> doubleitem;
                    queue2.pushback(doubleitem);
                }
                break;
            }
            case 2:
            {
                if (type == 0)
                {
                    intitem = queue1.popfront();
                    cout << "The front element " << intitem << " was popped.\n";
                }
                else
                {
                    doubleitem = queue2.popfront();
                    cout << "The front element " << doubleitem << " was popped.\n";
                }
                break;
            }
            case 3:
            {
                if (type == 0)
                {
                    intitem = queue1.front();
                    cout << "The front element is " << intitem << ".\n";
                }
                else
                {
                    doubleitem = queue2.front();
                    cout << "The front element is " << doubleitem << ".\n";
                }
                break;
            }
            case 4:
            {
                if (type == 0)
                {
                    intitem = queue1.back();
                    cout << "The back element is " << intitem << ".\n";
                }
                else
                {
                    doubleitem = queue2.back();
                    cout << "The back element is " << doubleitem << ".\n";
                }
                break;
            }
            case 5:
            {
                if (type == 0)
                    boolresult = queue1.isempty();
                else
                    boolresult = queue2.isempty();
                if (boolresult == true)
                    cout << "The queue is empty.\n";
                else
                    cout << "The queue is notempty.\n";
                break;
            }
            case 6:
            {
                if (type == 0)
                    intitem = queue1.getlength();
                else
                    intitem = queue2.getlength();
                cout << "The queue contains " << intitem << " elements.\n";
                break;
            }
            case 7:
            {
                cout << "The queue elements from front to back are:\n";
                if (type == 0)
                {
                    int num = queue1.getlength();
                    for (int i = 1; i <= num; ++i)
                    {
                        intitem = queue1[i];
                        cout << intitem <<"\n";
                    }
                }
                else
                {
                    int num = queue2.getlength();
                    for (int i = 1; i <= num; ++i)
                    {
                        doubleitem = queue2[i];
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
