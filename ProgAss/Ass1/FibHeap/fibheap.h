#ifndef _FIBHEAP_H
#define _FIBHEAP_H
/* Put your decleration here */

template<class T> class FibNode;

template<class T> class FibHeap{
    public:
        FibHeap();  // this operation builds the heap
        /* You should add other functions to make the structure as Fibonacci heap  */
        /* It is part of computing assignment, so we would not provide the basic implementation for you */
        void Insert(FibNode<T>* fib_node);
        FibNode<T>* Minimum();
        FibNode<T>* ExtractMin();
        void DecreaseKey(FibNode<T>* handle, T new_key);
        void Delete(FibNode<T>* handle);
        void Consolidate();
        void FindMin();
        void PrintTree();
        FibNode<T>* HeapLink(FibNode<T>* heap1, FibNode<T>* heap2);
        /* The following is required for this assignment */
        /* It is not complete, you should design the API by yourself */
        // void Change_Key(x, k);
        // void Prune(r);
        void Cut(FibNode<T>* handle);
        static FibHeap<T>* Union(FibHeap<T>* heap1, FibHeap<T>* heap2);
        // static void 
        int GetNum();
    private:
        void _PrintTree(FibNode<T>* node);
        FibNode<T>* min_ptr;
        int numitems;
};


// build an empty heap
template<class T> FibHeap<T>::FibHeap(){
    min_ptr = NULL;
    numitems = 0;

};

template<class T> class FibNode{
    public:
        friend class FibHeap<T>;
        FibNode(T key = 0);
        FibNode<T>* parent;
        FibNode<T>* child;
        FibNode<T>* left;
        FibNode<T>* right;
        bool mark;
        T key;
        int degree;
};

template<class T> FibNode<T>::FibNode(T key){
    parent = NULL;
    child = NULL;
    left = NULL;
    right = NULL;
    degree = 0;
    mark = false;       // default marking == false
    FibNode::key = key;
};

#endif
