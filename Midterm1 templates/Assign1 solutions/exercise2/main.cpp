#include <iostream>
#include "alist.h"
#include "dlist.h"

/*  
*   sample definitions of f and g
*   note that the lists I created are of types AList<int> or DList<double>
*   you can choose any types to play with as long as it works
*/

// the length function for alist
int f1_alist (int value){
    return 1;
};

int g1_alist (int val1, int val2){
    return val1 + val2;
}

// the length function for dlist
int f1_dlist (double value){
    return 1;       // one element contributes to one unit in the length, clearly...
};

int g1_dlist (int val1, int val2){
    return val1 + val2;
}

// modulo-3 function for alist: 
//              only the numbers which can be divided by 3 are listed

/* 
*   T' = AList<int>*
*   Since we are returning a list, we shall return the pointer to that list.
*   Following the convention from ece220, it is better to return the pointer,
*   rather than the reference in this case.
*/

AList<int>* f2_alist(int value){    
    AList<int>* newList = new AList<int>(1);    // dynamically create a new list
    if (value % 3 == 0){                        // if the value can be divided by 3, append it to the list
        newList->append(value);
    }
    return newList;
}

AList<int>* g2_alist(AList<int>* list1, AList<int>* list2){
    list1->concat(*list2);
    delete list2;
    return list1;
}

// for dlist:
//      find all the elements with only one decimal
DList<double>* f2_dlist(double value){
    DList<double>* newList = new DList<double>();
    if ((int)(value * 100) % 10 == 0){  // if the value has only one decimal, append it 
        newList->append(value);
    }
    return newList;
}

DList<double>* g2_dlist(DList<double>* list1, DList<double>* list2){
    list1->concat(list2);
    delete list2;
    return list1;
}




int main() {
    // create two lists first.
    AList<int> myAList = AList<int>(60);
    DList<double> myDList = DList<double>();

    for (int i = 0; i < 60; ++i){
        myAList.append(i);
    }
    for (int i = 0; i < 45; ++i){
        double num = i * 0.33;
        myDList.append(num);
    }

    // display the two lists.
    cout << "The original AList:" << endl;
    myAList.listDisplay();
    cout << endl;
    cout << "The original DList:" << endl;
    myDList.listDisplay();
 
    // call the length function using src
    cout << endl;
    cout << endl << "Find the length of AList using src function." << endl;
    cout << "The length is " << myAList.src<int>(0, f1_alist, g1_alist) << endl;
    cout << endl << "Find the length of DList using src function." << endl;
    cout << "The length is " << myDList.src<int>(0, f1_dlist, g1_dlist) << endl;

    // call the phi function using src
    cout << endl << "Find all the elements of AList that can be divided by 3." << endl;
    AList<int>* emptyA = new AList<int>(0);         // e is an empty list in this case
    AList<int>* targetAList = myAList.src<AList<int>*>(emptyA, f2_alist, g2_alist);
    targetAList->listDisplay();
    delete emptyA;

    // call the phi function using src
    cout << endl << "Find all the elements of DList that has only one decimal." << endl;
    DList<double>* emptyD = new DList<double>();    // e is an empty list in this case
    DList<double>* targetDList = myDList.src<DList<double>*>(emptyD, f2_dlist, g2_dlist);
    targetDList->listDisplay();
    delete emptyD;
}
