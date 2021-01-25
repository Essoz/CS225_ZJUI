//
//  stack.h
//  
//
//  Created by KD on 17.01.21.
//

#ifndef stack_h
#define stack_h

template<class T> class stack
{
public:
    stack(int size = 10);
//    virtual ~stack();
    T &operator[](int index);
    int getheight(void);
    void push(T value);
    T pop(void);
    T top(void);
    bool isempty(void);
    
private:
    int maxsize, minsize;
    int numitems;
    T *reprarray;
    void allocate(void);
    void deallocate(void);
};

#endif /* stack_h */
