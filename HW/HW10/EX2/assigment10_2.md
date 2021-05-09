### -- ***Exercise 2*** --
**(i)**
Directed: For arbitrary two nodes $(p_1,t_1)$, $(p_2,t_2)$ connected by an edge, either $t_1 > t_2$ or $t_2 < t_1$ holds. Thus the graph will be directed.

Acyclic: There cannot be a backward edge, because for two nodes $(p_1,t_1)$, $(p_2,t_2)$ that is connected by a path from node 1 to node 2 (the two nodes can also be the same node), there cannot be a path from node 2 to node 1 since the condition $t_2 < t_1$ is violated.

**(ii)**
We can use DFS to find the route of interest.

INPUT:
> 1. The starting node of a shortest-path tree: p_start
> 2. Terminal of the nod of interest: p_end

Procedure;
> 1. do an DFS search on the tree. While searching, use a stack to keep track of the path from root to the current node
> On visiting a node, check if it is p_end.
> If yes, push the node and pop the entries in the stack into an array and return that array. The specific way of generating the array will be explained below.
> If not, if the node has further children, continue checking and push the node; if not, do nothing and return.


Since the existence of the waiting link, when poping the stack, 
1. We first pop the terminal and add it to the list.
2. For the rest of the nodes, we add a node to the list every time the stack has been popped twice.
