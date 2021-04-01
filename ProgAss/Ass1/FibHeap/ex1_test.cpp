#include "fibheap_f.h"
#include <assert.h>

int main(){

    /******************* Put your own test here *******************/
    /* Your are expected to give adequate test to show the correctness of your implementation */
    /* Otherwise you may be deducted points */
    
    // initiate the first heap structure for test
    int input1[] = {0,-4,1,2,-8,3,4,5,-1, 6,9,-7,-6,-5,7,-3,8,-2};
    FibHeap<int>* fib_heap_1 = new FibHeap<int>;
    // FibHeap<int>* fib_heap_2 = new FibHeap<int>;
    FibNode<int>* fib_nodes = NULL;
    for (auto i: input1) {
        fib_nodes = new FibNode<int>(i);

        if (fib_nodes == NULL){
            cout << "out of memory, terminating\n" << endl;
            return 3;
        }   
        // Insert the all nodes into the heap structure
        fib_heap_1->Insert(fib_nodes);
        // test if the heap Insert functions well
    }
        cout << fib_heap_1->GetNum() <<endl;
        assert(fib_heap_1->GetNum() == 18);
        assert(fib_heap_1->Minimum()->key == -8);
        fib_heap_1->PrintTree();

    FibNode<int>* min = fib_heap_1->ExtractMin();
    cout << min->key <<endl;
//    fib_heap_1->PrintTree();
 
    min = fib_heap_1->ExtractMin();
    cout << min->key <<endl;
 
    return 0;
}
