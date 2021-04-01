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
    return NULL;
};



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
    return NULL;
};



/*
*   Ex.1 (iii)
*   return value:   a pointer to a new list containing the selected elements
*/
template<class T> AList<T>* AVL<T>::range(T x, T y){
    return NULL;
};
