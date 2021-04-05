# Centralized Queueing System | CS225 MP 1
## Author: Group 10 | Yuxuan Jiang

Current Development Progress:
1. Having Implemented and Tested the Naive Fibonacci Heap

To Be Done:
1. Define a new function FibNode::CalcDelay(), this function will set any necessary information including DDL
    1. Withdrawn? Add 2 week delay
    2. Medium RiskStatus? Add 1 month delay. This overwrites the above case.
    3. With a DDL? This node needs to be add to a separate list that is ordered according to the DDL date. If the node is extracted before the date of ddl, it may need to be deleted from the ordered list. **HOW?**
      Note that for each week? day? , we will run a check into the DDL list, and deal with the nodes that are about to expire. (The check does not only deal with assignments on that specific date to see if on a specific date the number of DDLs will exceed the number of available locations.

2. How to execute update(priority or withdraw)?

3. How to deal with nodes that have withdrawn? 

4. We need a new variable called daily capacity in for assignment, this calls for a new class called $LOCATION$, for each local registry we maintained an ordered list of all locations, each location has an $availability$ attribute.


5. what if all has been occupied? (it will have to wait in the heap) which adds another check for availability (maybe use a new function called bool assignable()) 


6. the UnderAssignment Queue (I can make use of this queue (if exceeds the maximal size of the queue to compllete the aviability check) will be wiped after each day.

7. The nodes that finished treating needs to be deleted from the hash table, but we will provide another way (similar to hash with chaining) to access it.  
    Specifically, we will use an array list whose entry can be accessed w.r.t to week, and hold a pointer to a linked list of all nodes treated that week.


TBD:
1. An Assignment 