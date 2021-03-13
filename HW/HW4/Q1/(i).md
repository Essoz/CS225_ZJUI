![image-20210308191851452](C:\Users\Joshua\AppData\Roaming\Typora\typora-user-images\image-20210308191851452.png)

## (i)

### Fake code of $siftUp(n)$:

#### $siftUp$($n$) :

##### $parent=\lfloor{\frac{n}{2}}\rfloor$	

##### $while\ \lfloor parent / 2 \rfloor>1$ :

##### 				$If\  parent \not= Max [parent,leftChild,rightChild]$ :

##### 						$Switch\ parent\ with\ Max[parent,leftChild,rightChild]$

​		$siftUp(parent)$

### For the worst case, n will go to $1$, so the time complexity is $O(log\ n)$ since the heap degree is $log\ n$.

### So the total complexity of insert is $O(1+log\ n)=O(log\ n)$.

## (ii)



### The $siftDown$ is now changed into two parts:

### 1.First change the value of the $siftDown$ node to be $-\infin$, and by using the normal $siftdown$ method, this node will be moved to bottom level of the heap (a leaf node, but may not the last leaf node). In this process by changing the $siftDown$ algorithm, the comparisons can be $logn$ (EX. add a $if$ condition by check whether the compared value is $-\infin$, if it is , exchange the biggest child with this parent node of value $-\infin$. Thus just one time comparison is exacuted.)

### 2. Now the $siftDown$ path is made, the second thing is to find where this node should be placed along the $siftDown$ path, in other words, we need to determine which heap level the node should be placed. By using the binary search, first check  the middle level of the heap. Then check iteratively the middle level of the previous level. We can find the target level with $O(lglgn)$, ($T(m)=T(\frac{m}{2})+\theta(1),m=lgn$).

### So the total complexity is $lgn+O(lglgn)$

