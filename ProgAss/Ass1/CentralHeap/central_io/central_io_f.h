#include "central_io.h"
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <vector>
using namespace std;



/* READ2HEAP
 * INPUT == NULL
 * OUTPUT == NULL
 * EFFECT
 * 1. It reads registrations from files generated by local registries, convert them into fibnodes and then insert all nodes into the fibheap
 * Algorithm Description
 * While inserting, it does the following things:
 * 1. Before insert, check if the ID is in hash table of the central heap (Check *withdrawn*, *centralheap*, *assigned*), if the id is not in hashtable, directly insert this node into the heap
 * if the node is in any of the three hash table, execute helper functions corresponding to the three cases.
 * 2. 
 * 3. 



 */
template<class T> bool CentralIO<T>::Read2Heap(){
    ifstream infile;
    infile.open(path, ifstream::in);
    if (infile.fail()) { 
        cout << "File not found" <<endl; 
        return false;
    }

        
    
    //check hash set

    //if in hashset

    //do corresponding insertions
    /*
     * Insert this node into the corresponding hash table
     * 
     */
        
    
    return true;
}

template<class T> bool CentralIO<T>::ReportWeekly(int key){
    /* Generate Weekly Report for 
     * 1. People who have been treated including their profession, age category, risk status, and the waiting time from registration to treatment
     * 2. the registered people with a set appointment including their profession category, age category, risk status and their waiting time until now
     * 3. the queueing people without a set appointment including their profession category, age category, risk status and their waiting time until now
     */

    
}
template<class T> bool CentralIO<T>::ReportMonthly(int key){

}

template<class T> bool CentralIO<T>::_WeeklyCured(){

}
template<class T> bool CentralIO<T>::_WeeklyAssigned(){

}
template<class T> bool CentralIO<T>::_WeeklyQueueing(){

}
template<class T> bool CentralIO<T>::_Monthly(){

}