#include "fibheap_f.h"
#include "alist.cpp"
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
    AList<FibNode<int>*> node_list_1;
    for (auto i: input1) {
        fib_nodes = new FibNode<int>(i);
        node_list_1.append(fib_nodes);

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


    if (false){
    /* PASSED <==== A Test for HeapLink ====> */ 
        // Test1: Trivial Case, Branch 1 (child == NULL)
    fib_heap_1->HeapLink(fib_heap_1->Minimum(), fib_heap_1->Minimum()->right);
    assert(fib_heap_1->GetNum() == 18);
    assert(fib_heap_1->Minimum()->degree == 1);
    assert(fib_heap_1->Minimum()->key == -8);
    fib_heap_1->PrintTree();

        // Test2: Branch 2 (child != NULL), Iterative Test
for (int i = 1; i < fib_heap_1->GetNum() - 1; i++){
        
        fib_heap_1->HeapLink(fib_heap_1->Minimum(), fib_heap_1->Minimum()->right);
        assert(fib_heap_1->GetNum() == 18);
        assert(fib_heap_1->Minimum()->degree == 1 + i);
	assert(fib_heap_1->Minimum()->key == -8);
	//fib_heap_1->PrintTree();
    }
    fib_heap_1->PrintTree();    
    
    }



    /* PASSED <==== A Test for ExtractMin & Consolidate ====> */ 
    
    cout << fib_heap_1->GetNum();
    FibNode<int>* min = fib_heap_1->ExtractMin();
    fib_heap_1->PrintTree();
    cout << fib_heap_1->Minimum()->key << endl;
    cout << min->key << "\n";
    assert(fib_heap_1->GetNum() == 17);
    assert(fib_heap_1->Minimum()->degree == 4);
    assert(fib_heap_1->Minimum()->key == -7);
 
    /* PASSED <==== A Test for DecreaseKey ====> */	
    fib_heap_1->DecreaseKey(node_list_1[2], -10); //decrease -4 to -10
    fib_heap_1->DecreaseKey(node_list_1[6], -20);
    
    fib_heap_1->DecreaseKey(node_list_1[1], -15);
    
    fib_heap_1->PrintTree();
    
    
    assert(fib_heap_1->GetNum() == 17);
    
    // assert(fib_heap_1->Minimum()->degree == 3);
    assert(node_list_1[12]->degree == 3);   //examine the degree of node -7
    assert(fib_heap_1->Minimum()->key == -10);


    //min = fib_heap_1->ExtractMin();
    //cout << min->key <<endl;


    /* <==== A Test for Union ====> */
    int input2[] = {20,30,5,-20};
    FibHeap<int>* fib_heap_2 = new FibHeap<int>; 
    for (auto i: input2) {
        fib_nodes = new FibNode<int>(i);

        if (fib_nodes == NULL){
            cout << "out of memory, terminating\n" << endl;
            return 3;
        }
        fib_heap_2->Insert(fib_nodes);
    }   
    fib_heap_2->PrintTree();

    FibHeap<int>* fib_heap_new; 
    fib_heap_new = FibHeap<int>::Union(fib_heap_1,fib_heap_2);

    assert(fib_heap_new->Minimum()->key == -20);
    assert(fib_heap_new->GetNum() == 17 + 4);
    fib_heap_new->PrintTree();
    return 0;
}
