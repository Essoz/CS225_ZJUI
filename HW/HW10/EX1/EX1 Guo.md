condition:

1.The order of the edges are not sorted, so can't use kruskal's Algorithm;

2.The edges are presented once, so the algorithm must be implemented edge-wise in the coming order of the edges;

3.It is undirected graph;

So the outline of the algorithm is stated as follow:
$$
\begin{align}
For&\ each\ edge\ E:\\ 
if&\ Tree.find(E.start)!=Tree.find(E.end)\\
&Tree.add(E)\\
el&se\ if\ Tree.find(E.start)=False\and\ Tree.find(E.end)=False\\
&Tree.add(E)\\
el&se\ // consider\ when\ start\ and\ end\ point\ are\ in\ the\ Tree\\
&find\ edge:\\
&edge1=edge\ in\ Tree\ with E.start\\
&edge2=edge\ in\ Tree\ with E.end\\
if&\ E<edge1\or\ E<edge2\\
&Tree.remove(edge1\or\ edge2)// remove\ the\ corresponding\ edge\\
&Tree.add(E)\\
\end{align}
$$
