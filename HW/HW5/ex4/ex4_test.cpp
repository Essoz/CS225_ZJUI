#include <ctime>                /* For performance comparasion */
#include "hash_extend_f.h"
using namespace std;

int main(){
    /******************* Put your own test here *******************/
    /* Your are expected to give adequate test to show the correctness of your implementation */
    /* Otherwise you may be deducted points */

    /**************************************************************/
    /* Check Point 1: Correctness */
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

    /**************************************************************/
    /* Check Point 2: Compare the performance with initial hashset as baseline */
    /* ctime is included for you to help */


    return 0; 
}