//
//  test.cpp
//  

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "avl.cpp"
using std::cout;
using std::cin;

// Test case:
int main()
{
    AVL<int> mytree = AVL<int>();
    // Test for insertion:
    // The theoritical result should be:
    //          6
    //      2       9
    //    1   4   8   10
    //
    mytree.insert(6);
    mytree.insert(8);
    mytree.insert(4);
    mytree.insert(2);
    mytree.insert(1);
    mytree.insert(9);
    mytree.insert(10);
    // 10 is in the AVL tree!
    mytree.insert(10);
    mytree.display();

    // Test for deletion:
    // The theoritical result should be:
    //          6
    //      4       8
    //  2
    //
    mytree.remove(1);
    // 5 is not in the AVL tree!
    mytree.remove(5);
    mytree.remove(9);
    mytree.remove(10);
    mytree.display();
    return 0;
}
