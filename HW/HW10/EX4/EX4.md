1.The example graph is in the png file;

2.It is obviously that for arbitrary triangle composed by 3 vertex A B C, if someone go from B to C, he will not pass again through A since the D(A,B)+D(A,C)>D(B,C), since this equation stands for all arbitrary triangle, the TSP solution can't contain a vertex for 2 more times;

3.The algorithm is simple:

(1). choose an arbitrary vertex as the start and end point;

(2). use prim's algorithm to find a MST which root is this point;

(3). output the order of vertex that the prim's algorithm explored, then add the root point at the end, the TSP route is finished;

This MST won't contain one vertex for 2 times (except the root point) since following the triangular equation;

So it can also be treated as a TSP route.