//
//  fifo.h
//  
//
//  Created by KD on 18.01.21.
//

#ifndef fifo_h
#define fifo_h

template<class T> class fifo
{
public:
    fifo(int size = 10);
//    virtual ~fifo();
    T &operator[](int index);
    int getlength(void);
    bool isempty(void);
    T back(void);
    T front(void);
    void pushback(T value);
    T popfront(void);
    
private:
    int maxsize, minsize;
    int first, last;
    int numitems;
    T *reprarray;
    void allocate(void);
    void deallocate(void);
};

#endif /* fifo_h */
