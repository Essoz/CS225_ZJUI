//
//  trietest.cpp
//  
//
//  Created by KD on 20.03.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "trie.cpp"
using std::cout;
using std::cin;

int main()
{
    trie<char> mytrie = trie<char>();
    AList<char> mylist1 = AList<char>(10);
    AList<char> mylist2 = AList<char>(10);
    AList<char> mylist3 = AList<char>(10);
    AList<char> mylist4 = AList<char>(10);
    AList<char> mylist5 = AList<char>(10);
    AList<char> mylist6 = AList<char>(10);
    AList<char> mylist7 = AList<char>(10);
    AList<char> mylist8 = AList<char>(10);
    mylist1.append('c');
    mylist1.append('o');
    mylist1.append('w');
    mylist2.append('c');
    mylist2.append('a');
    mylist2.append('t');
    mylist3.append('d');
    mylist3.append('o');
    mylist3.append('g');
    mylist4.append('c');
    mylist4.append('a');
    mylist4.append('r');
    mylist4.append('r');
    mylist4.append('o');
    mylist4.append('t');
    mylist5.append('c');
    mylist5.append('o');
    mylist5.append('w');
    mylist5.append('a');
    mylist5.append('r');
    mylist5.append('d');
    mylist6.append('c');
    mylist6.append('a');
    mylist6.append('r');
    mylist7.append('p');
    mylist7.append('y');
    mylist7.append('t');
    mylist7.append('h');
    mylist7.append('o');
    mylist7.append('n');
    mylist8.append('c');
    mylist8.append('o');
    mylist8.append('o');
    mylist8.append('k');
    mytrie.insert(mylist1);
    mytrie.display();
    cout << "\n" << mytrie.intrie(mylist1) << "\n";
    cout << mytrie.intrie(mylist2) << "\n\n";
    mytrie.insert(mylist2);
    mytrie.display();
    mytrie.insert(mylist3);
    mytrie.display();
    mytrie.insert(mylist4);
    mytrie.display();
    mytrie.insert(mylist5);
    cout << "\n" << mytrie.intrie(mylist3) << "\n";
    cout << mytrie.intrie(mylist4) << "\n";
    cout << mytrie.intrie(mylist8) << "\n\n";
    mytrie.display();
    mytrie.insert(mylist6);
    mytrie.display();
    mytrie.insert(mylist7);
    mytrie.display();
    mytrie.insert(mylist8);
    cout << "\n" << mytrie.intrie(mylist5) << "\n";
    cout << mytrie.intrie(mylist6) << "\n";
    cout << mytrie.intrie(mylist7) << "\n";
    cout << mytrie.intrie(mylist8) << "\n\n";
    mytrie.display();
    return 0;
}
