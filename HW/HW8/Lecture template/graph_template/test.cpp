//
//  test.cpp
//
//for testing the graph class
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
    graph<int> * mygraph = new graph<int>;
    (*mygraph).addedge(2,3);
    (*mygraph).addedge(1,4);
    (*mygraph).addedge(1,2);
    (*mygraph).addedge(3,4);
    (*mygraph).addedge(2,4);
    (*mygraph).prettyprint();
    (*mygraph).addvertex(7);
    (*mygraph).prettyprint();
    (*mygraph).deletevertex(7);
    (*mygraph).deletevertex(3);
    (*mygraph).deletevertex(8);
    (*mygraph).prettyprint();
    (*mygraph).addedge(3,7);
    (*mygraph).addedge(7,2);
    (*mygraph).addedge(1,4);
    (*mygraph).prettyprint();
    edgelist<int> * myedgelist1 = (*mygraph).outgoingedges(1);
    (*myedgelist1).prettyprint();
    edgelist<int> * myedgelist3 = (*mygraph).outgoingedges(3);
    (*myedgelist3).prettyprint();
    edgelist<int> * myedgelist2 = (*mygraph).outgoingedges(2);
    (*myedgelist2).prettyprint();
    edgelist<int> * myedgelist4 = (*mygraph).outgoingedges(4);
    (*myedgelist4).prettyprint();
    edgelist<int> * myedgelist7 = (*mygraph).outgoingedges(7);
    (*myedgelist7).prettyprint();
    edgelist<int> * myedgelist5 = (*mygraph).outgoingedges(5);
    (*myedgelist5).prettyprint();
    (*mygraph).deleteedge(2,4);
    (*mygraph).deleteedge(2,8);
    (*mygraph).deleteedge(4,7);
    (*mygraph).prettyprint();
    //write your test here//
    
}
