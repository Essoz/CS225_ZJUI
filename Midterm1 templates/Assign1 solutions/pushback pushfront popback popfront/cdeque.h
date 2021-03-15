//
//  cdeque.h
//
//  created by Xiong Neng on 21.01.21
//
//  circular double-ended queue
// 

#include <iostream>
using namespace std;
 
template <class T>
class CircularDeque {
public:
	CircularDeque(int size = 20);
	~CircularDeque(){delete[] data;}
	void pushFront(T value);
	void pushBack(T value);
    T popFront(void);
    T popBack(void);
	bool isEmpty(){ return front == back;}
	bool isFull(){ return ((back + 1) % maxsize == front % maxsize);}
	void print(void);
private:
	int front, back;
	int maxsize;
	int numitems;
    T *data;
};

// constructor
template<class T>
CircularDeque<T>::CircularDeque(int size) {
    front = 0;
    back = 0;
    numitems = 0;
    maxsize = size;
    data = new T[maxsize];
    cout << "maxsize is " << maxsize << endl;
}

// add element to the front of the queue
template<class T>
void CircularDeque<T>::pushFront(T value) {
    // if the queue is full, throw error
    if (isFull()) {
        cout << "Index error: push when queue is full\n";
        throw -1;
    }
    // move front pointer one step counter-clockwise and assign value
    front = (front - 1 + maxsize) % maxsize;
    data[front] = value;
    ++numitems;
}

// add element to the back of the queue
template<class T>
void CircularDeque<T>::pushBack(T value) {
    // if the queue is full, throw error
    if (isFull()) {
        cout << "Index error: push when queue is full\n";
        throw -1;
    }
    // assign value and move back pointer one step clockwise
    data[back] = value;
    back = (back + 1) % maxsize;
    ++numitems;
}

template<class T> T CircularDeque<T>::popFront(void) {
    // if the queue is empty, throw error
    if (isEmpty()){
        cout << "Index error: pop when list is empty\n";
        throw -1;
    }
    // store return value and move front pointer one unit clockwise
    T value = data[front];
    front = (front + 1) % maxsize;
    --numitems;
    return value;
}

template<class T> T CircularDeque<T>::popBack(void) {
    // if the queue is empty, throw error
    if (isEmpty()){
        cout << "Index error: pop when list is empty\n";
        throw -1;
    }
    // move back pointer one unit and return value
    back = (back - 1) % maxsize;
    --numitems;
    return data[back];
}

template<class T> void CircularDeque<T>::print(void) {
    if (0 == numitems) {
        cout << "The deque is now empty\n";
        return;
    }
    cout << "The deque is now: ";
    for (int i = 0; i < numitems; ++i)
        cout << data[(front + i) % maxsize] << ' ';
    cout << endl;
}
