#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "hashset.cpp"
using std::cout;
using std::cin;
using std::hash;


int main(){
    int i;
    hash<int> hashfunction;
    hashset<int> myhashtable;
    myhashtable = hashset<int>(20);
    int test_input[14] = {202,32,7,15,74,9,12,16,102,4,8,22,3,2};

    for (i = 0; i < 14; i ++){
        myhashtable.add(test_input[i]);
        cout << test_input[i] << "'s desired position:   " << hashfunction(test_input[i]) % 20 << "\n";
    }

    /* pay attention to 3, 2, 22's position */
    cout << "=============== my hashtable ===============\n";
    myhashtable.display();
    cout << "=============== remove 102 ===============\n";
    myhashtable.remove_modified(102);
    myhashtable.display();
}

