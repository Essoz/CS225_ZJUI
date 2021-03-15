#include <iostream>
#include "alist.h"
#include "dlist.h"
#include "dlist.cpp"
using namespace std;


int main() {
    DList<int> Dlist;
    int length, elements,totalnumber;
    //list initializing. randome number will be push into the list
    cout << "array initialinzing, enter the total length (integer) : \n";
    cin>>length;
    for (int i = 0; i < length; i++)
        {
            elements = rand() % 1000; 
            Dlist.append(elements);
        }
    totalnumber = Dlist.getlength();
    for (int i = 1; i <= totalnumber; ++i)
    {
        elements = Dlist[i];
        cout << "List element " << i << " is " << elements <<".\n";
    }
    return 0;
}