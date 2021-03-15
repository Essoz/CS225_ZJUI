//
//  test cdeque.cpp
//
//  created by Xiong Neng on 21.01.21
//
//  circular double-ended queue
// 

#include <iostream>
#include "cdeque.h"

using namespace std;

int main()
{
    // set maxsize to 21 since one extra address is needed for checking isFull
	CircularDeque<int> dq(21);

    // three push options
	dq.pushFront(6);
    dq.pushBack(9);
    dq.pushFront(9);

    // display the deque
    dq.print();

    // three pop options
    cout << dq.popBack() << endl;
    cout << dq.popFront() << endl;
    cout << dq.popFront() << endl;

    // 10 random pushfront & pushback
    for (int i = 0; i < 10; ++i) {
        dq.pushFront(rand() % 20);
        dq.print();
    }
    for (int i = 0; i < 10; ++i) {
        dq.pushBack(rand() % 20);
        dq.print();
    }

    // 10 popfront & popback
    cout << "popback 10 times...\n";
    for (int i = 0; i < 10; ++i) {
        cout << dq.popBack() << '\n';
    }
    dq.print();
    cout << "popfront 10 times...\n";
    for (int i = 0; i < 10; ++i) {
        cout << dq.popFront() << '\n';
    }
    dq.print();

	return 0;
}