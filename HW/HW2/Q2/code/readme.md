# HW2 Q2
## Author: Yuxuan Jiang, Group 10

### Q2.1
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

