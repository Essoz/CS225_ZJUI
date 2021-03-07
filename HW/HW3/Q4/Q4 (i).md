![image-20210302224150501](C:\Users\Joshua\AppData\Roaming\Typora\typora-user-images\image-20210302224150501.png)



# (i)

### Same as in Max heap, simply add the k new elements into the end of the heap. Every time a new elements is added, one $sift\ up$ is executed.

### fake code :

#### Heap_add :

##### 	for k times :		

##### 		Heap[numitems] = new_elements

##### 		numitems++

##### 		$sift\ up$ ($\lfloor numitems/2 \rfloor$)

#### $sift\ up$(parent) :

##### while $\lfloor parent / 2 \rfloor$$>$ 1

##### left_child = 2*parent

##### 		right_child = 2*parent+1

##### 		parent = $Max${parent, left_child, right_child}

##### 		parent =$\lfloor parent / 2 \rfloor$

### 

