// #include "fibheap.h"
#include "fibheap_f.h"
#include "alist.h"
#include "hashing/central_hash.cpp"
#include "assqueue/assignment_f.h"
#include "central_io/central_io_f.h"
#include "appointment/appointment_f.h"
#include <bits/stdc++.h>
// #include <string>
// #include <vector>
using namespace std;
// using std::string;
// using std::vector;
// using std::string;
int timer = 0;
const int interval = 1; // unit in day
string path = "../Submit.csv";
int date;
int main(){
    char order;
    cout << "Please Choose how do you want to order the report" << endl;
        cout << "0: Name\n1: Profession Category\n2: Age Group (Ascending Order)\n";
        cin >> order;
        if ((order != '0') && (order != '1') && (order != '2'))
            cout << "You must choose 0, 1 or 2\n\n";
    
    /* <======= TEST CASES ======> */
    // testcases (location)
    vector<string> time_slot_0 = {"8:00", "9:00","10:00","14:00", "16:00"};
    vector<string> time_slot_1 = {"8:30", "10:00","12:30", "14:00"};
    vector<string> time_slot_2 = {"9:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "17:00"};
    vector<string> time_slot_3 = {"9:00", "13:00","17:00",};
    vector<string> time_slot_4 = {"1:00", "2:00", "2:30", "2:25", "liar CS225"};

    Location* Location_0 = new Location(0, time_slot_0);
    Location* Location_1 = new Location(1, time_slot_1);
    Location* Location_2 = new Location(2, time_slot_2);
    Location* Location_3 = new Location(3, time_slot_3);
    Location* Location_4 = new Location(4, time_slot_4);

    vector<(Location*)> location_list;
    location_list.push_back(Location_0);
    location_list.push_back(Location_1);
    location_list.push_back(Location_2);
    location_list.push_back(Location_3);
    location_list.push_back(Location_4);

    // testcases (registry)
    vector<int> location_dist_0 = {0,1,2,3,4};
    vector<int> location_dist_1 = {1,2,3,4,0};
    vector<int> location_dist_2 = {2,3,4,0,1};
    vector<int> location_dist_3 = {3,4,0,1,2};
    vector<int> location_dist_4 = {4,0,1,2,3};
    vector<int> location_dist_5 = {4,3,2,1,0};

    Registry Registry_0(0, &location_dist_0);
    Registry Registry_1(1, &location_dist_1);
    Registry Registry_2(2, &location_dist_2);
    Registry Registry_3(3, &location_dist_3);
    Registry Registry_4(4, &location_dist_4);
    Registry Registry_5(5, &location_dist_5);






    AllLocations all_locations(location_list);
    Assignment AssignRegistration(&all_locations);
    FibHeap CentralQueue;
    // initialize an IO instance for later use
    CentralIO central_IO = CentralIO(&CentralQueue, path);
    
    while (true) {
        date = timer / 2; 
        //  time counter 
        timer += 1; 
        
        // read file from file
        int failure = 0;    // number of failed attempts
        while (central_IO.Read2Heap() == false){
            failure++;
            sleep(1);       // wait for 1 second
            if (failure == 5) {
                cout << "no file found, aborting";
                exit(3);
            }
        }
        
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