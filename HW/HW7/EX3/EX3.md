EX3 (i)

The upper bound is composed by $x*h$, x is the maximum searching time in one node, h is the height of the tree, since one node is searched in each level of the tree.
$$
x = \lceil\log b\rceil\\
since\ for\ one\ node\ use\ the\ binary\ search\ method.\\n=1+2\sum_{i=0}^{h-2}a^{i}=1+\frac{2*(1-a^{h-1})}{1-a}<1+2*\frac{a^{h-1}}{a}=1+2*a^{h-2}\\\Rightarrow\ h<2+\log_a{\frac{n-1}{2}}\\\Rightarrow\ total\ compare\ time\ =x*h=\lceil\log b\rceil*(2+\log_a\frac{n-1}{2})
$$
EX3 (ii)
$$
Take $a=2^{k}\ \Rightarrow\ b\leq2^{k+1}\\ \Rightarrow\ x*h=O(\log b)+\frac{k+1}{k}*\log \frac{n-1}{2}=O(\log b)+O(\log \frac{n-1}{2})=O(\log b)+O(\log n)
$$


