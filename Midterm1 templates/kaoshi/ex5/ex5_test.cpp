#include "solution.h"

int main(){

    int input1[] = {0,-4,1,2,-8,3,4,5,-1, 6,9,-7,-6,-5,7,-3,8,-2};
    int input2[] = {30,42,55,79,-5,264,187,56};

    DList<int> test1, test2;
    for (auto i: input1) test1.append(i);
    for (auto i: input2) test2.append(i);

    /* DO NOT MODIFY THE FOLLOWING */
    /* Write your solution in solution.h */
    /* Input 1 Check */
    cout << "Input 1: " << endl;
    test1._pprint_();
    test1._reverse_check_();

    /* Input 2 Check */
    cout << "Input 2: " << endl;
    test2._pprint_();
    test2._reverse_check_();

    return 0;
}