#include "solution.cpp"
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;


int main(){
    /******************Ex.1 (i) test******************/
    // golden output
    string test1_inorder = "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19";
    string test1_preorder = "7 3 1 0 2 5 4 6 15 11 9 8 10 13 12 14 17 16 18 19";
    string test1_postorder = "0 2 1 4 6 5 3 8 10 9 12 14 13 11 16 19 18 17 15 7";
    string test2_inorder = "1.2 2.3 3.4 4.5 5.6";
    string test2_preorder = "4.5 2.3 1.2 3.4 5.6";
    string test2_postorder = "1.2 3.4 2.3 5.6 4.5";
    string test1_BFS_1 = "7 3 15 1 5 11 17 0 2 4 6 9 13 16 18 8 10 12 14 19";
    string test1_BFS_2 = "7 15 3 17 11 5 1 18 16 13 9 6 4 2 0 19 14 12 10 8";
    string test1_range = "5 6 7 8 9 10 11 12 13 14 15 16";

    // Ex.1 (i) test 1
    cout << "Ex.1 (i) test 1" << endl;
    AVL<int> test1 = AVL<int>();
    for (int i = 0; i < 20; ++i){
        test1.insert(i);
    }
    AList<int>* DFS_res1;
    DFS_res1 = test1.DFS();
    cout << "Expected output:" << endl;
    cout << "Inorder:      " << test1_inorder << endl;
    cout << "Preorder:     " << test1_preorder << endl;
    cout << "Postorder:    " << test1_postorder << endl;
    cout << endl << "Your output:  ";
    DFS_res1->_print_();
    cout << "Your output should match exactly one provided sequence.";
    cout << endl << endl;


    // Ex.1 (i) test 2
    cout << "Ex.1 (i) test 2" << endl;
    AVL<double> test2 = AVL<double>();
    test2.insert(4.5);
    test2.insert(5.6);
    test2.insert(2.3);
    test2.insert(1.2);
    test2.insert(3.4);
    AList<double>* DFS_res2;
    DFS_res2 = test2.DFS();
    cout << "Expected output:" << endl;
    cout << "Inorder:      " << test2_inorder << endl;
    cout << "Preorder:     " << test2_preorder << endl;
    cout << "Postorder:    " << test2_postorder << endl;
    cout << endl << "Your output:  ";
    DFS_res2->_print_();
    cout << "Your output should match exactly one provided sequence.";
    cout << endl << endl;


    // Ex.1 (ii) test 1
    cout << endl << endl << "Ex.1 (ii) test 1" << endl;
    AList<int>* BFS_res1;
    BFS_res1 = test1.BFS();
    cout << "Expected output:" << endl;
    cout << "Left child first:    " << test1_BFS_1 << endl;
    cout << "Right child first:   " << test1_BFS_2 << endl;
    cout << endl << "Your output:         "; 
    BFS_res1->_print_();
    cout << "Your output should match exactly one provided sequence.";
    cout << endl << endl;


    // Ex.1 (iii) test 1
    cout << endl << endl << "Ex.1 (iii) test 1" << endl;
    AList<int>* range_res1;
    range_res1 = test1.range(5,16);
    cout << "Expected output:" << endl;
    cout << "Any order:      " << test1_range << endl;
    cout << endl << "Your output:    "; 
    range_res1->_print_();
    cout << "You can igonre the difference caused by order.";
    cout << endl << endl;
}

