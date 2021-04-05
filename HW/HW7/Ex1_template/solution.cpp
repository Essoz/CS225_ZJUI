#include "avl.cpp"
#include "fifo.cpp"


// your implementation

/*
*   Ex.1 (i)
*   return value:   a pointer to a new list containing the selected elements
*
*   notes:          typically, there are three variants of DFS in trees:
*                                       inorder, postorder and preorder.
*                   choose whichever you like the most.
*/
template<class T> AList<T>* AVL<T>::DFS(void){
    // First, create a new AList:
    AList<T>* result = new AList<T>(20);
    // Then, use inorder method, add all elements in the AVL tree into the AList:
    DFS_add(root, result);
    return result;
};


// The helper function is used recursively to insert the elements into the dynamically created alist.
template<class T> void AVL<T>::DFS_add(avlnode<T>* node, AList<T>* list){
    // First, we check if the input node is a NULL pointer:
    if (NULL == node)
    {
        return;
    }
    // Second, we need to check if the input node is a leaf node:
    if (NULL == node->pt_left && NULL == node->pt_right)
    {
        // If so, the path ends, add it into the AList:
        list->append(node->data);
        return;
    }
    // If the above two conditions are not satisfied, that means the node has at least
    // one children, apply the inorder method here:
    DFS_add(node->pt_left, list);   // The left subtree
    list->append(node->data);       // The root itself
    DFS_add(node->pt_right, list);  // The right subtree
    return;
}


/*
*   Ex.1 (ii)
*   return value:   a pointer to a new list containing the selected elements
*
*   notes:          BFS is usually implemented with a FIFO queue, you may
*                   want to make use of that. Typically, when pushing the
*                   children of a node, there are two orders:
*                                   left child first or right child first.
*                   choose whichever you like the most.
*/
template<class T> AList<T>* AVL<T>::BFS(void){
    // First, create a new AList and a new Queue for BFS:
    AList<T>* result = new AList<T>(20);
    fifo<avlnode<T>*>* queue = new fifo<avlnode<T>*>(20);
    // Then, use left child first method, add all elements in the AVL tree into the AList:
    queue->pushback(root);          // Add the root into the queue
    BFS_add(queue, result);         // Apply BFS operation
    return result;
};


template<class T> void AVL<T>::BFS_add(fifo<avlnode<T>*>* queue, AList<T>* list){
    // First, we check if the queue is empty:
    if (1 == queue->isempty())
    {
        return;     // The BFS is done, simply return
    }
    // If the queue is not empty, we get the first node in the queue and pop it out:
    avlnode<T>* node = queue->popfront();
    // Then, we check if the node is a NULL pointer in the middle of the queue:
    if (NULL == node)
    {
        BFS_add(queue, list);   // Move on to the next entry of the queue
        return;
    }
    // If it is not NULL, we need to check if the node is a leaf node:
    if (NULL == node->pt_left && NULL == node->pt_right)
    {
        // If so, the path ends, add it into the AList:
        list->append(node->data);
        BFS_add(queue, list);   // Move on to the next entry of the queue
        return;
    }
    // If the above two conditions are not satisfied, that means the node has at least
    // one children, apply the left child first method here:
        // First, add its children into the queue:
    queue->pushback(node->pt_left);
    queue->pushback(node->pt_right);
        // Second, add this root node into the Alist:
    list->append(node->data);
        // Third, apply BFS recursively:
    BFS_add(queue, list);
    return;
}


/*
*   Ex.1 (iii)
*   return value:   a pointer to a new list containing the selected elements
*/
template<class T> AList<T>* AVL<T>::range(T x, T y){
    // First, create a new AList pointer
    AList<T>* result;
    // Then, using DFS method, initialize this AList pointer:
    result = DFS();
    // Since we use inorder method for DFS, the output list is already sorted,
    // so we can easily find the element between x and y:
    for (int i = 1; i <= result->getlength(); i++)
    {
        // Compare the element at index i-1 with x and y:
        if (result->getitem(i) < x || result->getitem(i) > y)
        {
            // If the element is not in [x,y], delete it from the AList:
            result->remove(i);
            i--;
        }
    }
    return result;
};
