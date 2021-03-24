#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "bst.cpp"
using std::cout;
using std::cin;



int main(){
    int i;
    int input_data[6] = {5,2,8,1,7,10};
    /* mytree:
     *              5
     *        2           8
     *     1           7    10
     */

    BST<int> mytree1 = BST<int>();
    BST<int> mytree2 = BST<int>();
    BST<int> mytree3 = BST<int>();

    /* create three identical trees for the three tests */
    for (i = 0; i < 6; i++){
        mytree1.insert(input_data[i]);
        mytree2.insert(input_data[i]);
        mytree3.insert(input_data[i]);
    }

    /* test1: delete leaf node */
    cout << "========== test case 1: delete leaf node ========== \n";
    cout << "mytree before deletion: \n";
    mytree1.display();
    mytree1.remove_with_reinsert(7);
    cout << "\nmytree after deleting a leaf node: \n";
    mytree1.display();
    cout << "\n";

    /* test2: delete node with one child */
    cout << "\n========== test case 2: delete node with one child ========== \n";
    cout << "mytree before deletion: \n";
    mytree2.display();
    mytree2.remove_with_reinsert(2);
    cout << "\nmytree after deleting node with one child: \n";
    mytree2.display();
    cout << "\n";

    /* test3: delete node with two subtrees */
    cout << "\n========== test case 3: delete node with two subtrees ========== \n";
    cout << "mytree before deletion: \n";
    mytree3.display();
    mytree3.remove_with_reinsert(5);
    cout << "\nmytree after deleting node with two subtrees: \n";
    mytree3.display();

    return 1;
}