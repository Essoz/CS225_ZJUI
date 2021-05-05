# CS225 Assignment 9 | Group 10

## -- ***Exercise 4*** --

#### (a)

We modify Prim's Algorithm as described below:

```pseudocode
MST_PRIM(G, cost, r)
for each u in G.V
	u:key = INFINITY
	u:parent = nil
r:key = 0

Heap* Q
Q = HeapInit(G.V, min)		// construct a min heap using nodes in G.V

Edge edges[]
int extra_edges[]			// initialize an empty list to store indexes of additional edges for 
							// temporarily connecting components
while Q.size() != 0
	u = Q.ExtractMin()
		// START of The Modification
	if (u:key == INFINITY)	// This indicates the handle to a new conponent has been found
		Edge newedge(0)		// initialize a new edge of cost 0
		newedge->left = edges[0]->left	// connect new vertex to any vertex in the other component
		newedge->right = u
		extra_edges.Add(edges.size())
		edges.Add(newedge)
		// END of The Modification
    else 
		Edge newedge(u.key)
		newedge->left = u.parent
		newedge->right = u
		edges.Add(newedge)
		
	for each v in u.adj
		if v in Q and cost(u,v) < v.key
			v.parent = u
			v.key = cost(u,v)
	
Edge* Edges[]
Edges.Add(edges[0:extra_edges[0] - 1])
for i from 1 to (extra_edges.size - 2）
	Edges.Add(edges[extra_edges[i] + 1 : edges[extra_edges[i + 1] - 1]])
Edges.Add[edges[extra_edges[extra_edges.size-1] + 1 : edges.size - 1]]
return Edges
```

Briefly, the original Prim's algorithm will correctly generate the minimal spanning tree for the first encountered connected component. When a new vertex without parent and key being set is encountered, we have encountered a new component. In this case, the modified algorithm just connect the use a edge with cost 0. The total number of extra edges will be $n-1$ where $n$ denotes the number of connected components in the graph.



 #### (b)

Assume the contrary, that there are two different MSTs A and B. Since $A\neq B$ and all edges' weights are pairwise different, there exists at least one edge such that it belongs to one but not the other. Among such edges, let $e_1$ be the one with least weight.

W.l.o.g assume that, assume $e_1 \in A$

As B is an MST, ${e_1}\cup B$ must contain a cycle $C$ containing $e_1$.

As a tree, A contains no cycles, therefore $C$ must have an edge $e_2$ that is not in $A$

Since $e_1$ was chosen as the unique lowest-weight edge among those belonging to exactly one of $A$ and $B$, $\omega(e_2) > \omega(e_1)$.

As $e_1$ and $e_2$ are part of the cycle $C$, replacing $e_2$ with $e_1$ in B yields a spanning tree with a smaller weight.

Hence the definition of a minimal spanning tree of B is violated.



#### (c)

The constructed minimum spanning set of a tree will not necessarily be a tree, provided the existence of a negative cycle. For example, $V' = \{a,b,c\} \in V$ and $E' = \{(a,b,-1),\ (b,c,-2),\ (a,c,-3)\}$. Clearly a minimum spanning set of the graph $G = (V',E')$ will be $E’$ itself, which is a **cycle**.



Provided all edges have positive weight, the minimum spanning set will not contain any cycles. We prove the statement using contradiction:

Suppose the minimum spanning set $T$ contains cycles, which has total cost $C$, then removing any edge from a cycle will reduce the total cost to $C'$, violating the definition of $T$.