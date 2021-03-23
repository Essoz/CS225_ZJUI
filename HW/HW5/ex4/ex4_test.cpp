#include <ctime>                /* For performance comparasion */
#include "hash_extend_f.h"
#include "hashset_f.h"
using namespace std;

int main(){
    /******************* Put your own test here *******************/
    /* Your are expected to give adequate test to show the correctness of your implementation */
    /* Otherwise you may be deducted points */

    /**************************************************************/
    /* Check Point 1: Correctness */
    int test[50];
    for (int i = 0; i < 50; i++)
    {
        test[i]=rand() % 10000;
    }
    
    HashSet_LCFS test1, test2,testExample1;
    HashSet_RH test3, test4,testExample2;
    hashset<int> testEcample0;
    /* Test on both inputs, missing operation would be deducted points */
    /* Test for LCFS Hash */
    //test the performance of add and rehash
    clock_t start0,finish0,start1, finish1,start2,finish2;
    
    start1=clock();
    for(auto i: test){
        testExample1.add(i);
    }
    finish1=clock();
//    testExample1.display();//if you want to see the content
    cout<<"time of LCFS hashing add performance : "<<(finish1-start1)<<"ms"<<endl;


    /* Test for RH Hash */
    start2=clock();
    for(auto i: test){
        testExample2.add(i);
    }
    finish2=clock();
    //    testExample2.display();//if you want to see the content
    cout<<"time of RH hashing add performance : "<<(finish2-start2)<<"ms"<<endl;

    /**************************************************************/
    /* Check Point 2: Compare the performance with initial hashset as baseline */
    /* ctime is included for you to help */
    /*test for nomal hash set*/
    start0=clock();
    for(auto i: test){
        testEcample0.add(i);
    }
//    testExample0.display();   //if you want to see the content
    finish0=clock();
    cout<<"time of ordinary hashing add performance : "<<(finish0-start0)<<"ms"<<endl;

    return 0; 
}