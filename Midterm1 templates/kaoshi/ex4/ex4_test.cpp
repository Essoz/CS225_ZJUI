#include "solution.h"


int main()
{
    /* Test Case */
    int input1[] = {0,-4,1,2,-8,3,4,5,-1, 6,9,-7,-6,-5,7,-3,8,-2};
    int input2[] = {30,42,55,79,-5,264,187,56};

    AList<int> test1, test2;

    for (auto i: input1) test1.append(i);
    for (auto i: input2) test2.append(i);
    cout << "Input 1:";
    test1._print_();
    cout << "Input 2:";
    test2._print_();

    /* Check Exercise 4 (i) */
    cout << endl << "Ex4. (i) Select Check" << endl << "Input 1: Select (5)" << endl;
    test1.select(5)->_print_();

    cout << "Input 2: Select (0)" << endl;
    test2.select(0)->_print_();


    /* Check Exercise 4 (ii) */
    cout << endl << "Ex4. (ii) Median Check" << endl << "Input 1: median" << endl;
    cout << test1.median() << endl;
    

    cout << "Input 2: median" << endl;
    cout << test2.median() << endl; 
    

    /* Check Exercise 4 (ii) */
    cout << endl << "Ex4. (ii) select_low Check" << endl <<  "Input 1: select_low" << endl;
    test1.select_low()->_print_();

    cout << "Input 1: select_low" << endl;
    test2.select_low()->_print_();

    return 0;
}
