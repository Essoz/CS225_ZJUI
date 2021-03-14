![image-20210314133526812](C:\Users\Joshua\AppData\Roaming\Typora\typora-user-images\image-20210314133526812.png)

### (ii)

### 1.$FindMin:$

#### 	$return$  	$heap.root$



### 2.$Merge(heap1.root,heap2.root):$

### 	If $heap1$ is empty:

#### 			return $heap2.root$

### 	If $heap2$ is empty:

#### 		    return $heap1.root$

### 	If $heap2.root>=heap1.root:$

#### 		    $heap1.root->child->youngestSibling:heap2.root$	//point to the heap1.root before

#### 			$heap2.root->youngerSibling:heap1.root$	

#### 			return $heap1.root$					

#### //don't change heap1.root->youngerSibling since it points to null

### 	Else:

#### 		    $heap2.root->child->youngestSibling:heap1.root$	

#### 		    //find the youngest sibling, which point to the heap2.root before

#### 			$heap1.root->youngerSibling:heap2.root$				

#### 			return $heap2.root$		

#### //don't change heap2.root->youngerSibling since it points to null

### 3. $Insert(heap,node)$:

### 			$heap.root->youngerSibling:node$

### 	 $node->youngerSibling:null$

### 4.$DecreaseKey(position,key):$

### 		If $position=heap.root:$

### 						$position.value-=key$

### 		Else:

### 		For $node$ in $heap$:

### 			If $node->youngerSibling=position$ $\or$ $node->child=position$

### 			$node->youngerSibling:position->youngerSibling$ $\or$$node->child:position->youngerSibling$

###  			//remove from the tree

### 			For $root$ in $heap.rootlist:$

### 				If $root->youngerSibling=null$:

### 				$root->youngerSibling:position$

### 				$position->youngerSibling:null$

### 				$position.value-=key$

### 5.$DeleteMin():$

### 		For $root$ in $heap.rootlist:$

### 		     $Minroot=root\ with\ the\ smallest\ root.value$

### 			$DecreaseKey(Minroot->child,0)$	//move the child to the rootlist

### 			For $node$ in $heap.rootlist$

### 				If $node->youngerSibling=Minroot:$

### 					$node->youngerSibling=Minroot->youngerSibling$	//remove from the list

### 			For $Node\ 1,Node\ 2$ in $heap.rootlist:$

### 					$Merge(Node\ 1,Node\ 2)$	//Combine all nodes in rootlist

