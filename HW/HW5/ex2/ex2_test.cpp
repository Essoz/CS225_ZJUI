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
    MultiSet<int>* test1 = new MultiSet<int>(input1, 5);
    MultiSet<int>* test2 = new MultiSet<int>(input2, 11);
    test1->create_hashtable();
    test2->create_hashtable();

    test1->insertion(1);
    test1->display();
    test1->deletion(1);
    test1->display();
    pair<int, int>* result = test1->retrieval(1);
    cout << "Return value is " << result->first << endl;
    cout << "The multiplicity is " << result->second << endl;

    MultiSet<int>::setunion(input1, input2, 5, 11);
    MultiSet<int>::intersection(input1, input2, 5, 11);
    MultiSet<int>::difference(input2, input1, 11, 5);

    /* Test for part(ii) */
        // MultiSet_chaining<int> test3, test4;
    return 0;
}