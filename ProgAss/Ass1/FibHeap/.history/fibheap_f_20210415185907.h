#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "fibheap.h"

using std::cin;
using std::cout;
using std::endl;

#define INFIMUM -100000
/* FibHeap - Insert
 * Input
 1. a pointer to the node being inserted (the node is assumed to be without child)
 2. the heap structure
 * Output: NONE
 * Effect: 
 1. numitems ++
 2. the node is inserted to the left of the min node
 

 */



/* <===> Test Passed <===> */
template<class T> void FibHeap<T>::Insert(FibNode<T>* fib_node){
    if(min_ptr){
        //if the Heap structure is not empty
        min_ptr->left->right = fib_node;
        fib_node->left = min_ptr->left;
        fib_node->right = min_ptr;
        min_ptr->left = fib_node;
        // update the min 
        min_ptr = (min_ptr->key > fib_node->key) ? fib_node : min_ptr;
    } else {
        // if the Heap structure is empty
        min_ptr = fib_node;
        fib_node->left = fib_node;
        fib_node->right = fib_node;
	numitems = 0;
    }
    numitems++;
}
/* FibHeap - Decrease Key
 * Input: 
 1. a handle to any node;  
 2. a key;
 * Algorithm Description
 1. change the given node's key to the specified value
 2. check if the definition of the heap is violated, if so, cut the subtree and re-insert it.  

//  4. execute consolidate
 */
template<class T> void FibHeap<T>::DecreaseKey(FibNode<T>* handle, T new_key){
    int num = GetNum();
    handle->key = new_key;
    if(handle->parent && new_key < handle->parent->key){
        Cut(handle);
    }
    // Consolidate();
    numitems = num; //since insertions within Cut modifies Cut 
}
/* FibHeap - Cut
 * Input
 1. a handle to any node (that is guaranteed to have a parent)
 * Algorithm Description
 1. First check if handle == parent->child. If so, there will be two cases
    i. node handle is the only child of its parent: 
        check if the parent is marked, if so, do cascaded cut
        if not, mark the parent, decrement degree.
    2. node handle is 
 */


template<class T> void FibHeap<T>::Cut(FibNode<T>* handle){
    FibNode<T>* par_ptr = handle->parent;
    if (handle->left == handle){
        // if handle is the only child, just set child_ptr to NULL
        par_ptr->child = NULL;
    } else {
        // delete handle from the child list
        if (par_ptr->child == handle) 
            //shift the child_ptr 
            par_ptr->child = handle->left;
        handle->left->right = handle->right;
        handle->right->left = handle->left;
    }
    handle->parent = NULL;
    Insert(handle);
    numitems--;

    // do marking or cascaded cut
    if (par_ptr->mark == false){
        par_ptr->mark = true;   // TODO: Should root nodes be marked?
    } else {
        if (par_ptr->parent) Cut(par_ptr);
    }

    // decrement degree of the parent node
    par_ptr->degree--;
}

/* FibHeap - Consolidate
 * Input
 1. the heap structure itself
 * Output: None
 * Effect
 */
template<class T> void FibHeap<T>::Consolidate(){
    int D_n = log(GetNum())/log(2);
    D_n++;
    int num = GetNum();
    // initiate the auxillary array
    FibNode<T>** arr = new FibNode<T>* [D_n];
    for(int i = 0; i < D_n; i++){
        arr[i] = NULL;
    }
    FibNode<T>* node_x = min_ptr;
    FibNode<T>* node_y; 
    int x_degree = 0;
    // debug note : the for loop should be replaced by a while loop, and the above line should be 
    for (int i = 0; i <= num; i++){
        x_degree = node_x->degree;
        while(arr[x_degree] != NULL){
            node_y = arr[x_degree];
            if (node_x == node_y) break;
            if (node_x->key > node_y->key){
                // exchanging two pointers if necessary, making sure that node x has a smaller key.
                FibNode<T>* temp_ptr = node_x;
                node_x = node_y;
                node_y = temp_ptr;

            }
            // merge the two heaps
            HeapLink(node_x, node_y); // add node_y as a child of x
            arr[x_degree] = NULL;
   	    x_degree++;
        } 
        arr[x_degree] = node_x;
        node_x = node_x->right;
    }
    // PrintTree();
    min_ptr = NULL;
    for (int i = 0; i < D_n; i++){
        if (arr[i]) Insert(arr[i]); // all cases are handled by this insert function
    } 
    numitems = num; //since the insert operation will change numitems
    delete[] arr;
}
/* FibHeap - HeapLink
 * Input
 1. heap1 - A heap structure with smaller min
 2. heap2 - A heap structure with larger min
 * Output: NONE
 * Effect
 1. Unmark heap2
 2. heap2 will be linked to heap1 as a child of heap1
 */
template<class T> FibNode<T>* FibHeap<T>::HeapLink(FibNode<T>* heap1, FibNode<T>* heap2){
    FibNode<T>* temp = heap1->child;
    heap2->left->right = heap2->right;
    heap2->right->left = heap2->left;
    
    if (temp != 0){
	// link the second heap to the left of the child list 
	temp = temp->left;
        heap1->child->left = heap2;
        heap2->right = heap1->child;
        heap2->left = temp;
        temp->right = heap2;
    } else {
        heap1->child = heap2;
        heap2->right = heap2->left = heap2;
    }
    heap1->degree++;
    heap2->parent = heap1;
    heap2->mark = false;
    return heap1;
}

/* FibHeap - Minimum */
template<class T> FibNode<T>* FibHeap<T>::Minimum(){
    return min_ptr;
}
/* FibHeap - ExtractMin
 * Input: NONE
 * Output
 1. the minimum node in the heap or NULL(if the heap was empty);
 * Algorithm Description
 1. First find that if the structure is empty. If so, return NULL
 2. If the structure is not empty, then add all children of min_ptr to the root list
 3. Return the given node
 */
template<class T> FibNode<T>* FibHeap<T>::ExtractMin(){
    if (min_ptr){
        FibNode<T>* current_node = min_ptr->child;
        FibNode<T>* next_node = NULL;
        min_ptr->parent = NULL;
        
        int min_degree = min_ptr->degree;
        for (int i = 0; i < min_degree; i++){
            next_node = current_node->left;
            Cut(current_node);
            current_node = next_node;
        }
        min_ptr->degree = 0;
        current_node = min_ptr;
        numitems--;
        if (min_ptr == min_ptr->right){
            min_ptr = NULL;
        } else {
            min_ptr->right->left = min_ptr->left;
            min_ptr->left->right = min_ptr->right;
            min_ptr = min_ptr->right;

            Consolidate();
            // TODO: Fill the definition for FINDMIN()
            
	    //since finding the new min is handled by consolidation, no need for FindMin here
	    //FindMin();
	    
        }
        return current_node;
    } else {
        // the structure is empty
        cout <<"The heap structure has no node in it, exiting ExtractMin...\n" <<endl;
        return NULL;
    }
}

/* FibHeap - FindMin
 * Input
 1. The heap structure itself
 * Output: NONE
 * Effect
 Update min_ptr
 * Algorithm Description
 1. Traverse through all roots in the list
 */
template<class T> void FibHeap<T>::FindMin(){
    if (min_ptr) {
        FibNode<T>* current_node = min_ptr->left;
        FibNode<T>* current_min = min_ptr;
        while (current_node != min_ptr){
            if (current_node->key < current_min->key){
                // locate the new minimum 
                current_min = current_node;
            }
	    current_node = current_node->left;
        } 
	min_ptr = current_min;
    } else {
        // else do nothing
        ;
    }
}


/* FibHeap - Delete
 * Input
 1. A handle to the node to be deleted
 * Output
 1. The modified heap structure
 * Algorithm Description
 1. First set the node to be deleted to the infimum of all keys
 2. Then execute extract_minimum
 */
template<class T> void FibHeap<T>::Delete(FibNode<T>* handle){
    DecreaseKey(handle, INFIMUM);
    ExtractMin();
}

template<class T> FibHeap<T>* FibHeap<T>::Union(FibHeap<T>* heap1, FibHeap<T>* heap2){
    FibHeap<T>* new_heap = new FibHeap<T>;
    new_heap->numitems = heap1->numitems + heap2->numitems;

    // determine new min from the two heap structures
    new_heap->min_ptr = heap1->min_ptr;
    if (heap2->min_ptr && heap1->min_ptr && heap2->min_ptr->key < new_heap->min_ptr->key){
        new_heap->min_ptr = heap2->min_ptr;
    } 
    
    // concatenate the root lists
    if (new_heap->min_ptr == heap1->min_ptr){
        new_heap->min_ptr->right->left = heap2->min_ptr->right;
        heap2->min_ptr->right->left = new_heap->min_ptr->right;
        new_heap->min_ptr->right = heap2->min_ptr;
        heap2->min_ptr->right = new_heap->min_ptr;
        
        new_heap->min_ptr->right = heap2->min_ptr;
        heap2->min_ptr->left = new_heap->min_ptr;
        
    }
     
    

    
    return new_heap;
}

template<class T> int FibHeap<T>::GetNum(){
    return numitems;
}





/* This Function is for Testing */
template<class T> void FibHeap<T>::PrintTree(){
    cout << "\n=========================\n"; 
	
    if (min_ptr == NULL){
        cout << "The Heap Structure is Empty" <<endl;
        return;
    }
    
    FibNode<T>* root_pt = min_ptr;
    int i = 0;
    do{
        cout << "Heap " << i++ << " :: " <<root_pt->key;
        _PrintTree(root_pt->child);
        cout << "\n------------\n";
        // move to the next heap
        root_pt = root_pt->right;
    }while(root_pt != min_ptr);
    
}

/* Recursive Printing*/
template<class T> void FibHeap<T>::_PrintTree(FibNode<T>* node){
    if (node == NULL){return;}
    FibNode<T>* node_pt = node;
    cout << "[";
    do{
        cout<< node_pt->key <<", ";
        _PrintTree(node_pt->child);
        node_pt = node_pt->right;
    }while(node_pt != node);
    cout << "]";
}
