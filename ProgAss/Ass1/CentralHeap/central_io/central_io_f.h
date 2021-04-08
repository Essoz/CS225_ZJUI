#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <vector>
#include "central_io.h"
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
bool CentralIO::Read2Heap(){
    ifstream infile;
    infile.open(path, ifstream::in);

    // wait for information from local registries
    if (infile.eof()){
        infile.close();
        return false;
    }

    if (infile.fail()) { 
        cout << "File not found" <<endl; 
        return false;
    }
    vector<string> temp_list;
    string temp;
    string line;   
    while (true){
        ifstream::getline(infile, line);
        
        // terminate the reading process on encountering an empty line
        if (line.size() == 0) break; 
        
        // reading registrations from files generated from local registries
        for (int i = 0; i < line.size(); i++) {
            if (line[i] = ",") {
                // put this string into the vector
                temp_list.push_back(temp);
                // clear the temp string for the next argument
                temp.clear();
                continue;
            }
            temp.push_back(line[i]);
        }
    
    // clear this list for next use
    FibNode* newnode = new FibNode(temp_list);
    temp_list.clear();
    //check hash set
    if (newnode->withdraw) {
        if (newnode->withdraw == 1){
            /*
             * 1. remove the node from hash table
             * 2. remove the node from the heap
             * 3. insert the new node into the withdraw_table
             * 4. remove the node from ddl queue (if the node was in that queue)
             * 5. release memory occupied by the old node
             */
            FibNode* old;
            heap->withdraw_table_insert(newnode);

            if (hash_intable_check(newnode->getid())){
                old = heap->hash_table_remove(newnode->getid());
                heap->Delete(old);

            } else if (highrisk_intable_check(newnode->getid())){
                old = heap->highrisk_table_remove(newnode->getid());
                heap->highrisk_queue.Delete(old);
            } else if (assigned_intable_check(newnode->getid())) {
                // all above branches leave the case where the node is already assigned and not in any heaps
                old = assigned_table_find(newnode->getid());
                Appointment* app = old->getappoint();
                app->loc->removeAppointment(app);
                delete app;
            }

                // if the node was in the DDL queue, remove the node from the queue
            if (heap->ddl_incheck(old))
                heap->ddl_delete(old);      //TODO Bug here may not exist in the ddl queue
            // insert the new one in case of any update
            // heap->withdraw_table_insert(newnode);
            delete old;
            // withdraw == 1 (this indicates a withdraw has been prompted, we have to search this node in the hashtable and move the node from the heap to the withdrawn set, set withdraw = 2) 
            // put this node into the withdrawn hashset 
        } else {
            // withdraw == 2 (this indicates the node now needs an re-insertion into the heap with a 14-day extension )
            /*
             * 1. remove the node from withdraw_table
             * 2. add the node into hash_table
             * 3. insert the node into the heap
             * 4. if ddl, add this node into the ordered list of ddl
             */
            heap->withdraw_table_remove(newnode->getid());
            heap->hash_table_insert(newnode);

            if (newnode->getddl() != -1) {
                heap->ddl_insert(newnode);
            }
            heap->Insert(newnode);
            // heap->withdraw_table_remove(newnode->getid());
            heap->hash_table_insert(newnode);
            // remove this node from the withdrawn hashset.
        }
    } else if (heap->hash_intable_check(newnode)){
        // the node is in hashtable
        //invoke the swap function
        /*
         * 1. swap the two node in the hash table
         * 2. swap the two node in the fibonacci 
         */
        FibNode* old;
        old = heap->hash_table_swap(newnode); 
        // delete the older version of the previous registration

        
        heap->Delete(old);
        heap->Insert(newnode);  // TODO Actually I can invoke a decrease key function here

        // do ddl update (if necessary)
        if (old->getddl() != -1){
            heap->ddl_remove(old);
        }
        if (newnode->getddl() != -1){
            heap->ddl_insert(newnode);
        }
        
        delete old;
        // do node swap and delete the original node

        // but there are several cases to consider:
        // 1. the element is also in the ddl queues
    } else if (newnode->getrisk() == 3) {
        heap->highrisk_table_insert(newnode);
        heap->highrisk_queue.Insert(newnode);
    }
        // if high risk encountered
        heap->Insert(newnode);
        heap->hash_table_insert(newnode);
        if (newnode->getddl() != -1) {
            heap->ddl_insert(newnode);
        }    
    }
    return true;
}




/* TODO <=== Helper Function for Generating Reports ===> */
bool CentralIO::ReportWeekly(int week, int key){
    /* Generate Weekly Report for 
     * 1. People who have been treated including their profession, age category, risk status, and the waiting time from registration to treatment
     * 2. the registered people with a set appointment including their profession category, age category, risk status and their waiting time until now
     * 3. the queueing people without a set appointment including their profession category, age category, risk status and their waiting time until now
     */
    _WeeklyCured(week, key);
    _WeeklyAssigned(week, key);
    _WeeklyQueueing(week, key);
}
bool CentralIO::ReportMonthly(int month, int key){
    _Monthly(month, key);
}

bool CentralIO::_WeeklyCured(int week, int key){
    cout << "\nWeekly Cured, " << key;
}
bool CentralIO::_WeeklyAssigned(int week, int key){
    cout << "\nWeekly Assigned, " << key;
}
bool CentralIO::_WeeklyQueueing(int week, int key){
    cout << "\nWeeklyQueueing, " << key;
}
bool CentralIO::_Monthly(int month, int key){
    cout << "\n Monthly, " << key;
    return true;
}

/*
 * OUTPUT
 * 1. 0 (a >= b)
 * 2. 1 (a < b)
 */
<<<<<<< HEAD
bool CentralIO::compare(FibNode* a, FibNode* b, int key){
=======
template<class T> bool CentralIO<T>::compare(FibNode<int>* a, FibNode<int>* b, int key){
>>>>>>> a7397de2185cb5dc6672ca7f0ecbea58a85b8968
    if (key == 0) {
        return (a->getname() < b->getname());
    } 
    if (key == 1) {
        return (a->getpro() < b->getpro());
    }
    if (key == 2) {
        return (a->getage() < b->getage())
    }
}
template<class T> void CentralIO<T>::sortbykey(vector<FibNode<int>*> fiblist,int key)
{
    FibNode<int>* temp;
    for (int i = 0; i < fiblist.size()-1; i++)
    {
        for (int j = 0; j < fiblist.size()-1-i; j++)
        {
            if (!this->compare(FibNode<int>* fiblist[j], FibNode<int>* fiblist[j+1], int key))
            {
                temp=fiblist[j];
                fiblist[j]=fiblist[j+];
                fiblist[j+1]=temp;
            }
            
        }
        
    }
    
}