#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "hashset.cpp"
using std::cout;
using std::cin;
using std::hash;

/* Assignment 6 Exercise 1 (ii)
 * Implement a variant of linear probing, where the size of the hash table is not m, but m+m'. 
 * In the search procedure in insert, find and delete increment the search index not considering the residue modulo m.
 * 
 * You will have to modify the given functions to use an overflow area.
 * When reaching A[m-1], instead of restart from A[0], A[1], ...
 * you should continue with A[m], ..., A[m+m'-1]. */

int main(){
    int i;
    hash<int> hashfunction;
    hashset<int> myhashtable;
    int test_input[14] = {99,23,22,65,10,5,7,19,30,39,1,79,59,3};
    /* your output should show that some of the elements are in the extra space */
    for (i = 0; i < 14; i ++){
        cout << test_input[i] << "'s desired position is:   " << hashfunction(test_input[i]) % 20 << "\n";
        myhashtable.add(test_input[i]);
    }
    cout << "========== test add ==========\n";
    myhashtable.display();
    cout << "========== test member ==========\n";
    cout << myhashtable.member(59) << "\n";
    cout << myhashtable.member(3) << "\n";
    cout << "========== test remove ==========\n";
    myhashtable.remove(30);
    myhashtable.remove(79);
    myhashtable.display();
    cout << "========== test add ==========\n";
    myhashtable.add(79);
    myhashtable.display();
}