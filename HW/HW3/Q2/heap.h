#ifndef heap_h
#define heap_h

template<class T> class AList
{
public:
    AList(int size = 20);
    virtual ~AList();
    T &operator[](int index);
    int getlength(void);
    void setitem(int index, T value);
    T getitem(int index);
    void append(T value);
    void insert(int index, T value);
    void remove(int index);
    void concat(AList<T> &list);
    bool member(T value);
    bool equal(AList<T> &list);
    bool sublist(AList<T> &list);
    
private:
    int maxsize, minsize;
    int numitems;
    T *reprarray;
    void allocate(void);
    void deallocate(void);
};

template<class T> AList<T>::AList(int size)
{
    maxsize = size;
    if (size < 20)
        minsize = size;
    else
        minsize = 20;
    numitems = 0;
    reprarray = new T[maxsize];
}

template<class T> AList<T>::~AList()
{
    delete[] reprarray;
}


template<class T> 
class MaxHeap: public AList<T>
{
public:
    MaxHeap(int size = 20):AList<T>(size){}
    void build_heap(AList<T> &array);
    void sift_down(int i, int num_elements);
    void heap_sort(AList<T> &array);
    void swap(int i, int j);
    T max();
    void print_elements();
private:

};


#endif
