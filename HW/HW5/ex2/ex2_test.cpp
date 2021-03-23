#include "multiset_f.h"
#include <iostream>	
#include <math.h>
#include <cstdlib>
#include <map>
#include <vector>
using namespace std;
using std::cout;
using std::cin;
using std::hash;

int main(){
    /******************* Put your own test here *******************/
    /* Your are expected to give adequate test to show the correctness of your implementation */
    /* Otherwise you may be deducted points */
    
    int input1[5] = {1, 1, 1, 5, 2};
    int input2[11] = {0, 2, 12, 3, 3, 3, 3, 4, 5, 5, 42};

    /* Add test to your container */
    /*
    for(auto i: input1){
        test1
        test3
    }

    for (auto i: input2){
        test2
        test4
    }
    */

    /* Test for all required operation on both inputs, missing operation would be deducted points */
    /* Test for part(i) */
    std::cout << "Tests for part(i):" << std::endl;
    MultiSet<int>* test1 = new MultiSet<int>(input1, 5);
    MultiSet<int>* test2 = new MultiSet<int>(input2, 11);
    test1->create_hashtable();
    test2->create_hashtable();

    test1->insertion(1);
    test1->display();
    test1->deletion(1);
    test1->display();
    test1->retrieval(1);

    test2->insertion(1);
    test2->display();
    test2->deletion(1);
    test2->display();
    test2->retrieval(1);

    MultiSet<int>::setunion(input1, input2, 5, 11);
    MultiSet<int>::intersection(input1, input2, 5, 11);
    // Difference here means set2 - set1:
    MultiSet<int>::difference(input2, input1, 11, 5);

    /* Test for part(ii) */
    std::cout << "Tests for part(ii):" << std::endl;
    MultiSet_Chaining<int>* test3 = new MultiSet_Chaining<int>(input1, 5);
    MultiSet_Chaining<int>* test4 = new MultiSet_Chaining<int>(input2, 11);

    test3->create_hashtable();
    test4->create_hashtable();

    test3->insertion(1);
    test3->display();
    test3->deletion(1);
    test3->display();
    test3->retrieval(1);

    test4->insertion(1);
    test4->display();
    test4->deletion(1);
    test4->display();
    test4->retrieval(1);

    MultiSet_Chaining<int>::setunion(input1, input2, 5, 11);
    MultiSet_Chaining<int>::intersection(input1, input2, 5, 11);
    // Difference here means set2 - set1:
    MultiSet_Chaining<int>::difference(input2, input1, 11, 5);

    return 0;
}
