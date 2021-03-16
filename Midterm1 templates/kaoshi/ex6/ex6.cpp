
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "solution.h"

using std::cout;
using std::cin;
using std::endl;

int main(){
    //test #1
    fifo<int> f1;
    pair<int> p1(999,1);
    f1.pushback(p1);
    int ret1 = f1.pop_vip();
    cout <<"Test Case #1" << endl;  
    cout << "Expected Output: 999" << endl;   
    cout << ret1 << endl;
    cout << "Expected Output: true (1), the queue should be empty." << endl;
    cout << f1.isempty() << endl;
 
    //test #2
    //[(3,9),(0,7),(2,8),(5,3),(7,6),(8,5),(2,1),(9,4),(7,2),(10,0)]
    int input_t_list2[10] = {3,0,2,5,7,8,2,9,7,10};
    int input_n_list2[10] = {9,7,8,3,6,5,1,4,2,0};
    fifo<int> f2;
    for (int i=0; i<10; i++){
        pair<int> p2(input_t_list2[i],input_n_list2[i]);
        f2.pushback(p2);
    }
    int ret2 = f2.pop_vip();
    cout << endl << "Test Case #2" << endl;  
    cout << "Expected Output: 10" << endl;   
    cout << ret2 << endl;
    cout << "Expected Output: All pairs in the original order except (10, 0)." << endl;  
    pair<int> p2;
    for (int i=1; i <= f2.getlength(); i++){
        p2 = f2[i];
        p2.print_pairs();
    }


    //test #3
    int input_t_list3[11] = {8,94,12,-52,34,26,0,153,7,-33,27};
    int input_n_list3[11] = {5,2,3,9,7,8,1,4,-1,6,0};
    fifo<int> f3;
    for (int i=0; i<11; i++){
        pair<int> p3(input_t_list3[i],input_n_list3[i]);
        f3.pushback(p3);
    }
    int ret3 = f3.pop_vip();
    cout << endl << "Test Case #3" << endl;  
    cout << "Expected Output: 7" << endl;   
    cout << ret3 << endl;
    cout << "Expected Output: All pairs in the original order except (7,-1)." << endl;  
    pair<int> p3;
    for (int i=1; i <= f3.getlength(); i++){
        p3 = f3[i];
        p3.print_pairs();
    }

    return 0;
}
