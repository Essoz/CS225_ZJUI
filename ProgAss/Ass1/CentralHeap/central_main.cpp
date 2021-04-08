#ifndef CENTRAL_HEAP_CPP
#define CENTRAL_HEAP_CPP

#include "fibheap.h"
#include "fibheap_f.h"

int timer = 0;
const int interval = 1; // unit in day
string path = "xxx/submission.csv";
int date;
int main(){
    int order;
    cout << "Please Choose how do you want to order the report" << endl;
        cout << "0: Name\n1: Profession Category\n2: Age Group (Ascending Order)\n";
        cin >> order;
        if ((type != 0) && (type != 1) && (type != 2))
            cout << "You must choose 0, 1 or 2\n\n";
    
    /* <======= TEST CASES ======> */
    // testcases (location)
    vector<string>* time_slot_0 = {"", "","",};
    vector<string>* time_slot_1 = {"", "","",};
    vector<string>* time_slot_2 = {"", "","",};
    vector<string>* time_slot_3 = {"", "","",};
    vector<string>* time_slot_4 = {"", "","",};

    Location Location_0(0, &time_slot_0);
    Location Location_1(1, &time_slot_1);
    Location Location_2(2, &time_slot_2);
    Location Location_3(3, &time_slot_3);
    Location Location_4(4, &time_slot_4);

    vector<Location*> location_list;
    location_list.push_back(&Location_0);
    location_list.push_back(&Location_1);
    location_list.push_back(&Location_2);
    location_list.push_back(&Location_3);
    location_list.push_back(&Location_4);

    // testcases (registry)
    vector<int> location_dist_ = {};
    vector<int> location_dist_ = {};
    vector<int> location_dist_ = {};
    vector<int> location_dist_ = {};
    vector<int> location_dist_ = {};
    vector<int> location_dist_ = {};

    Registry Registry_(, &location_dist_);
    Registry Registry_(, &location_dist_);
    Registry Registry_(, &location_dist_);
    Registry Registry_(, &location_dist_);
    Registry Registry_(, &location_dist_);
    Registry Registry_(, &location_dist_);






    AllLocations all_locations(location_list);
    Assignment AssignRegistration(&all_locations);
    FibHeap<int> CentralQueue;
    // initialize an IO instance for later use
    CentralIO<int> central_IO = CentralIO<int>(&CentralQueue, path);
    
    while (/*file not empty*/) {
        date = timer / 2; 
        //  time counter 
        timer += 1; 
        
        // read file from file
        central_IO.Read2Heap();

        // the wrapper function above 
        
        // start processing

        // first assign nodes in the heap
        if (AssignRegistration.checkAvailability()) {
            while (AssignRegistration.Assign((CentralQueue.Minimum())) && CentralQueue.GetNum()) {
                // keep assign until no further registrations can be assigned
                CentralQueue.ExtractMin();
                // TODO table management
            }
        }
        if (AssignRegistration.checkAvailability()) {
            while (AssignRegistration.Assign((CentralQueue.highrisk_queue.Minimum())) && CentralQueue.highrisk_queue.GetNum()) {
                // keep assign until no further registrations can be assigned
                CentralQueue.highrisk_queue.ExtractMin();
                // TODO table management
            }
        }


        // if counter % 7 == 0, generate reports
        if (timer % 14 == 0){
            CentralIO.ReportWeekly(timer / 14, order);
        }
        if (timer % 60 == 0){
            CentralIO.ReportMonthly(timer / 60, order);
        }

        // if counter % 30 == 0, generate weekly reports


    }
    

}

#endif