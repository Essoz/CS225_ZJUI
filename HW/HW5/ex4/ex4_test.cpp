#include <ctime>                /* For performance comparasion */
<<<<<<< HEAD
#include "hash_extend_f.h"
using namespace std;
=======
#include "hashset_f.h"
#include "hash_extend_f.h"

>>>>>>> aae4578d063820c5f35143b6b721115953c023aa

int main(){
    /******************* Put your own test here *******************/
    /* Your are expected to give adequate test to show the correctness of your implementation */
    /* Otherwise you may be deducted points */

    /**************************************************************/
    /* Check Point 1: Correctness */
<<<<<<< HEAD
    int test[50];
    for (int i = 0; i < 300; i++)
    {
        test[i]=rand() % 10000;
    }
    
    HashSet_LCFS test1, test2,testExample1;
    HashSet_RH test3, test4,testExample2;
    /* Test on both inputs, missing operation would be deducted points */
    /* Test for LCFS Hash */
    //test the performance of add and rehash

    //test for add
    clock_t start1, finish1,start2,finish2;
    start1=clock();
    for(auto i: test){
        testExample1.add(i);
    }
    finish1=clock();
    cout<<"time of LCFS hashing add performance : "<<(finish1-start1)*10000<<endl;
//    cout<<"result for testEXample1 :\n";
//    testExample1.display();

    /* Test for RH Hash */
    start2=clock();
    for(auto i: test){
        testExample2.add(i);
    }
    finish2=clock();
    cout<<"time of RH hashing add performance : "<<(finish2-start2)*10000<<endl;
=======
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

>>>>>>> aae4578d063820c5f35143b6b721115953c023aa

    /**************************************************************/
    /* Check Point 2: Compare the performance with initial hashset as baseline */
    /* ctime is included for you to help */


    return 0; 
}