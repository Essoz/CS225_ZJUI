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



> ***Amortized Analysis***

From the procedure described above, we state that the amortized complexity of $Prune(r)$ is $O(1)$. 

First, in terms of the actual time complexity $Prune(r) = O(r) + \text{Cascading Cuts}$

In the following part, we first show that the amortized complexity of $Prune(r)$ with a leaf list is $O(n)$, then the change in operation complexities caused by maintaining the leaf list is discussed.
$$
Insert(x) = O(1) +=
\begin{cases}
\begin{aligned}
& O(1) - \text{Pruning node x}\\
& O(1) - \text{Remove x from the leaf list} \\
& O(1) - \text{Marking the first non-marked parent Z of x} \\
& O(1) - \text{Adding the first non-marked parent Z of x to the leaf list} \\
& O(1) - \text{Cascaded Cuts (possible)}
\end{aligned}
\end{cases}
$$
First, we charge Insert(x) for the O(1+1) cost when the node x is being removed from the leaf list and pruned. Then we charge Insert(x) O(1+1) for marking the first non-marked parent Z of x and adding Z to the leaf list. Finally, during $Prune(r)$, each node will only have one chance to be cascaded-cut into the root list, thus we charge $Insert$ O(1) for each node. In total we have charged Insert O(5), which maintained Insert's original complexity.  And the operation $Prune(r)$ is only left with $O(1)$.

Next we will show that using a proper method we can maintain a leaf list without affecting the complexities of methods of Fibonacci heaps.

> For $Insert$, it suffices to link the node to be inserted to the leaf list, which takes an extra O(1) complexity. Thus $Insert$ still have complexity $O(1)$.

> For $Union$, it suffices to further link the leaf lists of two heaps, which takes an extra O(1) complexity. Thus $Union$ still have complexity $O(1)$.

> For $Extract\_Min$, when the two nodes of degree 0 are linked, one leaf is removed from the leaf list. Whatever operation is charged for the link is also charged for that leaf list removal. This means that if Y becomes the child of X, then the operation charged for that leaf list removal. This means that if Y becomes the child of X, then the operation charged is the one responsible for Y (for instance, the INSERT of Y) and that "Y" operation is the one paying for X to be removed from the leaf list. This adds O(1) to the cost of the operation that is responsible for Y. 

> For $Decrease\_Key$, all insertions into the leaf list must be due to cascaded-cuts and re-insertions. Thus all insertions into the leaf list can be distributed evenly to each re-insertion by an O(1) complexity. And finally, the first "non-marked" parent of x is going to be marked and inserted into the leaf list, which adds an additional $O(1)$ complexity to $Decrease\_Key$.

