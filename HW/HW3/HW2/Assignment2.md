# CS225 Assignment 2 | Group 10

## Exercise 1
#### (i)


$$
\begin{aligned}
&{\rm sorted\_list} \leftarrow sort({\rm unsorted\_list}) =\\
&\qquad	\boldsymbol{{\rm IF}}\ {\rm sorted\_list} = undef \\
&\qquad	\boldsymbol{\rm{THEN\ LET}}\ n = length({\rm unsorted\_list}) \\
&\qquad\qquad	\boldsymbol{\rm{IN\ PAR}} \\
&\qquad\qquad\qquad	\boldsymbol{\rm{IF}}\ {\rm sorted\_list_1} = undef\ \wedge\ ...\ \wedge\ {\rm sorted\_list_k} = undef \\
&\qquad\qquad\qquad		\boldsymbol{\rm THEN\ LET}\ {\rm list_1} = \boldsymbol{\rm I} L_1.length(L_1) = \lceil\frac nk\rceil)\wedge\exist{L'}.concat(L_1,L') = {\rm unsorted\_list} \\ 
&\qquad\qquad\qquad\qquad\boldsymbol{\rm IN\ \ \ \ LET}\ list_2 = \boldsymbol{\rm I}L_2.length(L_2) = \lceil \frac{n-\sum^1_{i=1}|L_i|}{k-1}\rceil\wedge \exist L'.concat(L_1,L_2,L') = {\rm unsorted\_list}\\
&\qquad\qquad\qquad\qquad\qquad \bold{IN} \ldots \\
&\qquad\qquad\qquad\qquad\qquad\qquad\qquad \bold{IN\ LET}\ list_k= \bold{I}L_k.length(L_k) = \lceil \frac{n-\sum^{k-1}_{i=1}|L_i|}{1}\rceil\wedge \exist L'.concat(L_1,L_2,L') = {\rm unsorted\_list}\\
&\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad \bold{IN\ PAR} {\rm \ sorted\_list_1} = sort({\rm list_1}) \\
&\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad \ldots\\
&\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\;\:\! {\rm sorted\_list_k} = sort({\rm list_k})\\
&\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\bold{ENDPAR}\\
&\qquad\qquad\qquad\bold{ENDIF}\\
&\qquad\qquad\qquad\bold{IF}\ {\rm sorted\_list_1} \neq undef \wedge \ldots \wedge {\rm sorted\_list_k} \neq undef\\
&\qquad\qquad\qquad\bold{THEN}\ {\rm sorted\_list} \leftarrow merge({\rm sorted\_list_1,\ldots,sorted\_list_k})\ \bold{ENDIF} \\
&\qquad\qquad\bold{ENDPAR}\\
&\qquad\bold{ENDIF}
\end{aligned}
$$

$$
\begin{aligned}
&{\rm merged\_list} \leftarrow merge({\rm inlist_1, \ldots, inlist_k})\\
& \bold{IF}\ {\rm merged\_list} = undef\ \bold{THEN}\\
& \qquad \bold{LET}\ x_1 = head({\rm inlist_1),\ restlist_1} = tail({\rm inlist_1}),\\
& \qquad\qquad\qquad \ldots \\
& \qquad\qquad\:\; x_k = head({\rm inlist_k}),\ {\rm restlist_k} = tail({\rm inlist_k})\ \bold{IN\ PAR}\\
& \qquad\qquad \bold{IF}\ x_1 \leq \forall x_i.\{i\neq 1\} \wedge {\rm merged\_restlist}=undef\\
& \qquad\qquad \bold{THEN}\ {\rm merged\_restlist} \leftarrow merge({\rm restlist_1,inlist_2,\ldots,inlist_k}) \ \bold{ENDIF}\\
& \qquad\qquad \bold{IF}\ x_2 \leq \forall x_i.\{i\neq 2\} \wedge {\rm merged\_restlist} = undef \\
& \qquad\qquad \bold{THEN}\ {\rm merged\_restlist} \leftarrow merge({\rm inlist_1,restlist_2,inlist_3,\ldots,inlist_k}) \ \bold{ENDIF}\\
& \qquad\qquad\qquad \ldots \\
& \qquad\qquad \bold{IF}\ x_k \leq \forall x_i.\{i\neq k\} \wedge {\rm merged\_restlist} = undef \\
& \qquad\qquad \bold{THEN}\ {\rm merged\_restlist} \leftarrow merge({\rm inlist_1,\ldots, inlist_{k-1},restlist_k})\ \bold{ENDIF}\\

& \qquad\qquad \bold{IF}\ x_1 \leq \forall x_i.\{i\neq 1\} \wedge {\rm merged\_restlist}\neq undef\\
& \qquad\qquad \bold{THEN}\ {\rm merged\_list} := concat([x_1], {\rm merged\_restlist})\ \bold{ENDIF}\\
& \qquad\qquad \bold{IF}\ x_2 \leq \forall x_i.\{i\neq 2\} \wedge {\rm merged\_restlist} \neq undef \\
& \qquad\qquad \bold{THEN}\ {\rm merged\_list} := concat([x_2], {\rm merged\_restlist})\ \bold{ENDIF}\\
& \qquad\qquad\qquad \ldots \\
& \qquad\qquad \bold{IF}\ x_k \leq \forall x_i.\{i\neq k\} \wedge {\rm merged\_restlist} \neq undef \\
& \qquad\qquad \bold{THEN}\ {\rm merged\_list} := concat([x_k], {\rm merged\_restlist})\ \bold{ENDIF}\\
& \qquad \bold{ENDPAR}\\
& \bold{ENDIF}
\end{aligned}
$$

**Note:** For the simplicity of expression of the algorithm, we omit the case where $n < thr $  in the original binomial mergesort algorithm.



Complexity Analysis:

​	First we see that for the merge algorithm, its complexity is in $\Theta(n)$.  (We omit the complexity analysis when $n < thr$ since it is trivial.) 
$$
f(n) = f(\lfloor{\frac nk}\rfloor) + f(\lfloor{\frac nk}\rfloor) + \ldots+f(n - (k-1) * \lfloor{\frac nk}\rfloor) + g(n) + d < k*f(\lfloor{\frac nk}\rfloor) + g(n) + d
$$
Replacing $n$ by $k^n$ this leads to a linear recurrence relation,
$$
h_n - k\cdot h_{n-1} = a_2\cdot k^n + b_2 + d
$$
 The characteristic polynomial is $(x-k)^2(x-1)$, which gives rise to 
$$
h_n = c_1 \cdot k^n + c_2 \cdot n\cdot k^n + c_3
$$
 and further 
$$
f_n = c_1 \cdot n + c_2\cdot \log_k(n)\cdot n + c_3 \in O(n\log(n) | \varphi(n))
$$
where the condition $\varphi(n)$ express that $n$ is a power of $k$.

As $n\log(n)$ is smooth and monotone increasing (almost everywhere), we can infer that $f_n \in O(n\log(n))$. 

And further because of the lower complexity bound of comparison-based sorting algorithm, $f_n \in \Theta(n\log{n})$. 



Finally we have shown that the complexity of the generalized Mergesort has invariant complexity under $k$.

#### Q1.3

From the pseudo-code provided in the class, we can get that:  
>	For selection_sort, if the length of the list is n, then we need to go through the loop for n times. Thus, we need:
>	n steps for checking if the list is empty
>	On average, searching through the list to find the smallest value needs 1/2 (n+n(n+1)/2)=(n+3)n/4 steps
>	n steps to add the smallest value into the new list
>	n steps to delete the smallest value in the old list
>Also, we need 1 step to go out the loop. So in total, we need (n+3)n/4+1+3n steps.

>	For Mergesort, if the length of list is n, then:
	For the division part, we need n-1 steps to separate the list into single element
	For merge part, since the depth of the division in the first part is logn, we need to deal with the whole list for logn times. In each time, we need to compare between different sublists for n times and add the smaller value into a new list for n times. So in total, we need 2n*logn in this part.
So for Mergesort, the total number of steps is 2n*logn+n-1.

To find the proper t, we let the steps of two sorting algorithms be equal.
i.e. 2n*logn+n-1=(n+3)n/4+1+3n
Finally, we get that n=26.54, so t=26.
For the experimental value, see the output of the program.






## Exercise 2
#### Q2.1
**Algorithm Description:**  
1. Input
    - K -- number of maximal available rooms in the hotel
    - bks -- A list (implemented using vector) of bookings
2. Output
    - **true** or **false** -- whether the bookings can be satisfied

3. Implementation of the algorithm  
The algorithm does three things  
        1. Traverse through the vector list ***bks*** of bookings to find *the latest date of arrival\/departure* and *the earliest date of arrival\/departure*. This information prepares for step 2 by finding the range of the dates of interest   
        2. use two arrays to record the number of arrivals and the number of departures respectively, which is implemented by using a k-sort-like algorithm and traverse through the vector list ***bks*** The indexes of the arrays correspond to dates.  
        3. Initialize a counter to 0, then loop on the range of the dates of interest. In each loop (day), counter = counter + #arrivals - #departures. If counter > ***K***, then ***false*** will be returned, else true will be returned.


4. Justification on time complexity of the algorithm:  
This algorithm has complexity in $O(n)$.  
**Proof**:  
Step 1 takes $O(n)$ time since it simply traverses through the vector list ***bks*** which has size $n$.   
Step 2 takes $O(n)$ time because it simply traverses through the vector list ***bks*** which has size $n$, and declaring two arrays takes time $O(1)$.  
For step 3,  the worst case will have complexity $O(n)$ because the range of the dates will be smaller than the length of the vector list of bookings. 

Thus the total complexity is $O(n) + O(n) + O(n) = O(n)$

## Exercise 3
Explained in a separate pdf file.

## Exercise 4
#### Q4.1

Since for $\forall\ x\ P(x) = \prod_{i=1}^{n}\ (x-e_i)\ - \prod_{i=1}^{n}(x-e_i')=0$ , take $x=[e_1,...,e_{n_i}]$ , get $x$ must equal to one of $[e'_1,..,e'_{n_i}]$ , so for $e \in [e_1,...,e_{n_i}]$, $e$ is equal to one of $[e'_1,..,e'_{i}]$, so $[e_1,...,e_{n_i}]$ is a permutation of  $[e'_1,..,e'_{i}]$.

#### Q4.2

 The polynomial $P(x) = \prod_{i=1}^{n}\ (x-e_i)\ - \prod_{i=1}^{n}(x-e_i')$ is of degree $n-1$, so according to the theorem, there are at most $n-1$ zeros, so the probability is $\frac{n-1}{p}$;

And since we can find one solution of these $n-1$ zeros by assigning that $e_i=e'_i$ except $e_n\not=e'_n$ since $[e_1,...,e_{n_i}]$ is not the permutation of $[e'_1,..,e'_{n_i}]$ .

In this way, we can take 
$$e_{max}=n-1$$ 

so  we get
$$p>Max\{\frac{n}{\varepsilon},n-1\}$$ 
Thus we have 
$$Sup({\rm Probabiltity}) = \lim_{n\rightarrow \infty}\frac{n-1}{\frac n\epsilon} = \lim_{n\rightarrow \infty}\frac{n-1}{n}\epsilon = \epsilon$$
Thus proven.
