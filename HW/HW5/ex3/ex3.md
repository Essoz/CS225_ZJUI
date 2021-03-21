# CS225 Assignment 5 | Group 10
If $S$ is the set of elements stored in the hash table and M is the set of all entries, i.e. $|S| = n$ and $|M| = m$, we can write $X = \sum_{i\in M}\prod_{e\in S}X_{e,i}$ with Bernoulli-distributed random variables 
$$X_{e,i} = 
\begin{aligned}
\begin{cases}
& 1\qquad \text{if e is not stored in slot i}\\
& 0\qquad \text{else}\\
\end{cases}
\end{aligned}
$$
$$
E(X) = \sum_{i\in M}E(\prod_{e\in S}{X_{s,i}}) = m \cdot (\frac{1-m}m)^n
$$