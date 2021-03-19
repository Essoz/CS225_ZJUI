#include <ctime>                /* For performance comparasion */
#include "hashset_f.h"
#include "hash_extend_f.h"


int main(){
    /******************* Put your own test here *******************/
    /* Your are expected to give adequate test to show the correctness of your implementation */
    /* Otherwise you may be deducted points */

    /**************************************************************/
    /* Check Point 1: Correctness */
    int input1[] = {1, 1, 1, 5, 2};
    int input2[] = {0, 2, 12, 3, 3, 3, 3, 4, 5, 5, 42};

    HashSet_LCFS<int> test1, test2;
    HashSet_RH<int> test3, test4;
    /* Add test to your container */
    for(auto i: input1){
        test1.add(i);
        test3.add(i);
    }


    for (auto i:input2){
        test2.add(i);
        test4.add(i);
    }


    /* Test on both inputs, missing operation would be deducted points */
    /* Test for LCFS Hash */
    

    /* Test for RH Hash */


    /**************************************************************/
    /* Check Point 2: Compare the performance with initial hashset as baseline */
    /* ctime is included for you to help */


    return 0; 
}