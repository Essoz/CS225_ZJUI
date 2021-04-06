#ifndef CENTRAL_HEAP_CPP
#define CENTRAL_HEAP_CPP

#include "fibheap.h"
#include "fibheap_f.h"

int main(){
    _Float64 timer = 0;
    int interval = 0.5  // unit in day
    int order;
    cout << "Please Choose how do you want to order the report" << endl;
        cout << "0: Name\n1: Profession Category\n2: Age Group (Ascending Order)\n";
        cin >> order;
        if ((type != 0) && (type != 1) && (type != 2))
            cout << "You must choose 0, 1 or 2\n\n";
    

    // read testcases (location)

    // initialize an IO instance for later use

    // initialize a Queue for ddl registrations 
        
    // initialize a HashTable for all elements in the heap, all element with a DDL

    // initialize a 


    while (/*file not empty*/){
        // time counter ++ 0.5
        timer+=0.5; 
        // read file from file
        
        

        // the wrapper function above 


        // start processing
        

        // check min_ptr pointer, see if assignable
        ExtractMin();

        // if assignable, assign this node (in half day) 
        if (node.assignable()){
            //assign this node

            //put this into the list for that specific location
            location.insert(node);
        }

        for (int i = 0; i < locations.size; i++){
            for (int j = 0; j < locations[i].size; i++){
                if ((locations[i][j].time - counter) >= locations[i][j].appointment.timeneeded){
                    locations[i].remove[j];
                }
            }
        }
        // remove cured registrations, put them into the archive list


        // if counter % 7 == 0, generate reports
        if (timer % 7 == 0){
            IO.ReportWeekly(order);
        }
        if (timer % 30 == 0){
            IO.ReportMonthly();
        }

        // if counter % 30 == 0, generate weekly reports


    }
    

}

#endif