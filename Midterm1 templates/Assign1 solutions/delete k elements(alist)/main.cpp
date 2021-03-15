#include <iostream>
#include "alist.h"

using namespace std;

int main(){
    // create a list with numbers from 0 to 59
    AList <int> mylist = AList<int>(30);
    for (int i = 0; i < 60; ++i){
        mylist.append(i);
    }
    // display the list
    cout << "The original list:" << endl;
    mylist.listDisplay();
    cout << endl << "Perform a delete_last(20) operation." << endl;
    mylist.delete_last(20);
    mylist.listDisplay();
    cout << endl << "Perform a delete_last(45) operation." << endl;
    mylist.delete_last(45);
    mylist.listDisplay();
    return 0;
}