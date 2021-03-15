//
//  bstmgt.cpp
//  
//
//  Created by KD on 14.03.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "bst.cpp"
using std::cout;
using std::cin;

int main()
{
    int type, op;
    BST<int> mytree1 = BST<int>();
    BST<double> mytree2 = BST<double>();
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
            cout << "1: insert\n";
            cout << "2: delete\n";
            cout << "3: find\n";
            cout << "4: display\n";
            cin >> op ;
        }
        while ((op < 0) && (op > 4));
        switch(op)
        {
            case 0: return(0);
            case 1:
            {
                cout << "Enter a value:\n";
                if (type == 0)
                {
                    int intitem;
                    cin >> intitem;
                    mytree1.insert(intitem);
                }
                else
                {
                    double doubleitem;
                    cin >> doubleitem;
                    mytree2.insert(doubleitem);
                }
                break;
            }
            case 2:
            {
                cout << "Enter a value:\n";
                if (type == 0)
                {
                    int intitem;
                    cin >> intitem;
                    mytree1.remove(intitem);
                }
                else
                {
                    double doubleitem;
                    cin >> doubleitem;
                    mytree2.remove(doubleitem);
                }
                break;
            }
            case 3:
            {
                cout << "Enter a value:\n";
                if (type == 0)
                {
                    int intitem;
                    cin >> intitem;
                    boolresult = mytree1.find(intitem);
                }
                else
                {
                    double doubleitem;
                    cin >> doubleitem;
                    boolresult = mytree2.find(doubleitem);
                }
                if (boolresult == true)
                    cout << "The value is in the BST.\n";
                else
                    cout << "The value is not in the BST.\n";
                break;
            }
            case 4:
            {
                if (type == 0)
                    mytree1.display();
                else
                    mytree2.display();
            }
        }
    }
    while (op != 0);
    return(0);
}
