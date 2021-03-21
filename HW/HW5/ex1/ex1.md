# CS225 Assignment 5 | Group 10

## -- ***Exercise 1***  --

#### 1.1

To implement $Change\_Key$, we make use of $Decrease\_Key$. Note that although $Decrease\_Key$ anticipated $k<x.key$, we assume that it can accept input $k>x.key$ and correctly modify the value of x.key despite further cut might be necessary.

> **Algorithm Description**

```c
if (k < x->key){
    // this situation is handled by decrease_key
    DecreaseKey(x,k);
} else if (k > x->key) {
    x->key = k;
    // check if heap's definition has been violated
    if (x->child){
        //traverse the children list of x
        
        FibNode<T>* temp_current = x->child;
        FibNode<T>* temp_next = x->child->left;
        
        int degree = x->degree;	// the degree will be changed once a Cut operation is executed.
        for (int i = 0, i < x->degree; i++){
            if (x->key > temp_current->key){
                use a cut-like operation to "cut" the child and re-insert into the root list
                but does not do cascaded cut here
                    
                //mark x
                x->mark = true;
            }
            temp_current = temp_next;
            temp_next = temp_next->left;
        }	        
    }
}
```

> Amortized Analysis

For the case where $k<x\rightarrow key$, the operation degenerates to $DecreaseKey$, which we have shown in the class that the amortized complexity of this operation is $O(1)$

For the case where $k = x\rightarrow key$, the operation is in $O(1)$ since no actual operations are executed and $\phi(H') - \phi(H) = 0$

For the case where $k > x \rightarrow key$, the operation is in $O(\log(n))$ where n denotes the number of items. 

> Traversing through the root





Another option: just concatenate the child list of x to the root list, which obviously takes $O(1)$  

#### 1.2

> Preparations

To delete $r < numitems$ nodes from a given Fibonacci heap structure, node-wise deletions are necessary. Thus the deletions alone take $O(r)$ actual time complexity. For the pursue of high efficiency, we needs to reduce the total actual complexity of $Prune$, which requires a minimum number of costly operations like "re-inserting all child nodes into the root list" and "traversing the tree structure to locate the next node to be deleted".

From what has been stated above, our $Prune$ operation deletes only **leaf nodes** *avoid unnecessary operations* and hence requires **a linked list of all leaf nodes** in the Fibonacci Heap structure to reduce i/o time needed to locate the next node to be deleted.

>  ***Algorithm Description***

```c
void FibHeap<T>::Prune(int r){
    // x points to the node to be deleted, while leaf points to the next node to be deleted.
    FibNode<T>* x = leaf;
    leaf = leaf->right;
    
    //delete n nodes
    for (int i = 0; i < r; i++){
        if (x == min_ptr){
            // if x is equal to heap.minimum, skip
            x = x->right;
            leaf = leaf->right;
        }
        // remove *x from the leaf list 
        x->left->right = leaf;
        leaf->left = x->left;
        
        // locate the first "non-marked" parent of x 
        FibNode<T>* unmarked_parent = x->parent;
        while (unmarked_parent->mark == true){
            unmarked_parent = unmarked_parent->parent;
        }    
        Delete(x); 			// call member function delete to actually delete node x
        // all cases including x is a root node; x is a child of some node, marking and cascaded cuts are all handled by the operation Delete	
        
        // add the previously "non-marked" parent to the leaf list
        leaf->left->right = unmarked_parent;
        unmarked_parent->left = leaf->left;
        unmarked_parent->right = leaf;
        leaf->left = unmarked_parent;
        
        // move to the next node
        leaf = leaf->right;
    }
    
    
    
}
```

