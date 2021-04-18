//
//  test.cpp
//
// for testing the graph class
//
//  Created by KD on 11.04.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "graph.cpp"
using std::cout;
using std::cin;

int main()
{
    vertexlist<int>* boys1 = new vertexlist<int>;
    vertexlist<int>* girls1 = new vertexlist<int>;
    boys1->append(1);
    boys1->append(2);
    boys1->append(3);
    boys1->append(4);
    girls1->append(5);
    girls1->append(6);
    girls1->append(7);
    girls1->append(8);

    vertexlist<int>* boys2 = new vertexlist<int>;
    vertexlist<int>* girls2 = new vertexlist<int>;
    boys2->append(1);
    boys2->append(2);
    boys2->append(3);
    boys2->append(4);
    girls2->append(5);
    girls2->append(6);
    girls2->append(7);
    girls2->append(8);

    edgelist<int>* edges1 = new edgelist<int>(0);
    edgelist<int>* edges2 = new edgelist<int>(0);
    edges1->add(1, 5);
    edges1->add(8, 1);
    edges1->add(7, 1);
    edges1->add(2, 5);
    edges1->add(6, 3);
    edges1->add(3, 7);
    edges1->add(4, 6);
    edges1->add(8, 4);

    edges2->add(1, 5);
    edges2->add(1, 7);
    edges2->add(5, 2);
    edges2->add(2, 6);
    edges2->add(8, 3);
    edges2->add(4, 8);

    Bipartite<int> * mygraph1 = new Bipartite<int>(boys1, girls1, edges1);
    bool a = mygraph1->is_perfect_match();
    if (true == a)
    {
        cout << "Graph 1 has a perfect matching." << endl;
    }
    else
    {
        cout << "Graph 1 has no perfect matching." << endl;
    }

    Bipartite<int>* mygraph2 = new Bipartite<int>(boys2, girls2, edges2);
    bool b = mygraph2->is_perfect_match();
    if (true == b)
    {
        cout << "Graph 2 has a perfect matching." << endl;
    }
    else
    {
        cout << "Graph 2 has no perfect matching." << endl;
    }
    return 0;
}
