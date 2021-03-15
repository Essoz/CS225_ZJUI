# CS225 Exam Sample1 | Yuxuan Jiang
## Exercise 1
1. First sort the two list: sort list 1 using k-sort w.r.t keyword b; sort list2 using quicksort
2. Traverse the two lists. Add buckets with key in the second list to our result
3. Return result

#### 1.2
For complexity improvements, since T is already sorted, we don't need to sort list2, that saves $O(n\log{n})$ time and the complexity is reduced to $O(n)$

## Exercise 2
#### 2.1
Algorithm 
1. Sort the list(but cannot modify order)
2. find the minimum

#### 2.2
1. call find-median
2. traverse through the list while generating the two lists

## Exercise 3
#### 3.1
Using an k-sort-alike algorithm, the operation can be done.
1. First traverse through the list to find the maximum and minimum value of elements
2. initialize an array with size = maximum - minimum, initialize all entries of this array to NULL. 
3. Now traverse through the list, if the corresponding entry is empty, add the element to the entry, if not, delete the node
4. connect the nodes in the entry.
#### 3.2
To have an in-place operation, we can just traverse through the list one by one, then in a complexity of $O(n^2)$ the operation will be complete

## -- ***Exercise 4*** -- 
#### 4.1
1. keep pop elements from stack1, check if the element has value k. if not, push the popped elements to stack2 (if not found then print "no ocurrence"). If yes, put all elements in stack2 back to stack1, and return the element just found.


#### 4.2
For an in place check

## -- ***Exercise 5*** --
#### 5.1
with the aid of an additional stack the operation is easily done
#### 5.2
$O(n)$

## -- ***Exercise 6*** --
#### 6.1 
这题好捞啊
#### 6.2
radix sort

Reasoning:
1. bubble  sort takes $O(n^2)$ time for each trie, thus the total complexity is $O(k*n^2)$ where k is the maximal length of words
2. The range is fixed.


## -- ***Exercise 7*** --

## -- ***Exercise 10*** --