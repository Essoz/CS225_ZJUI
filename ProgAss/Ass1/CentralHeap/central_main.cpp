#include "alist.cpp"
#include "central_io/central_io_f.h"
#include "assqueue/assignment_f.h"
#include "appointment/appointment_f.h"
#include "hashing/central_hash.cpp"

#include <unistd.h>
#include <string>
#include <vector>
using namespace std;

int timer = 0;
const int interval = 1; // unit in day
string path;
int date;
int main(){
    char order;
    cout << "Please Choose how do you want to order the report" << endl;
    cout << "0: Name\n1: Profession Category\n2: Age Group (Ascending Order)\n";
    cin >> order;
    if ((order != '0') && (order != '1') && (order != '2'))
        cout << "You must choose 0, 1 or 2\n\n";
    
    // cout << "Please Provide a path to the file" << endl;
    // cin >> path;
    path = "../Local/Submit.csv";
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

    vector<Location*> location_list;
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

    Registry* Registry_0 = new Registry(0, location_dist_0);
    Registry* Registry_1 = new Registry(1, location_dist_1);
    Registry* Registry_2 = new Registry(2, location_dist_2);
    Registry* Registry_3 = new Registry(3, location_dist_3);
    Registry* Registry_4 = new Registry(4, location_dist_4);
    Registry* Registry_5 = new Registry(5, location_dist_5);
    
    vector<Registry*> registry_list;
    registry_list.push_back(Registry_0);
    registry_list.push_back(Registry_1);
    registry_list.push_back(Registry_2);    
    registry_list.push_back(Registry_3);
    registry_list.push_back(Registry_4);
    registry_list.push_back(Registry_5);

    FibHeap* central_queue = new FibHeap;
    FibHeap* highrisk_queue = new FibHeap;
    central_queue->highrisk_queue = highrisk_queue;
    AllLocations* Locs = new AllLocations(location_list);
    AllRegistries* Regs = new AllRegistries(registry_list);
    Assignment AssignRegistration(Locs, central_queue);
    // initialize an IO instance for later use
    CentralIO central_IO = CentralIO(central_queue, path);
    
    cout << "Welcome to the Central Queueing System (beta version). " << endl;

    while (true) {
        
        
        cout << "The system time is now at Year 2021, Month " 
             << to_string((timer+1) / 30 + 1) << ", Date " << to_string((timer+1) % 30);
        if (timer / 2 * 2 == timer) cout << ", Afternoon\n";
        else cout << ", Morning\n";

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
        if (AssignRegistration.checkAvailability(date)) {
            while (AssignRegistration.Assign((central_queue->Minimum()), date) && central_queue->GetNum()) {
                // keep assign until no further registrations can be assigned
                central_queue->ExtractMin();
                // TODO table management
            }
        }
        if (AssignRegistration.checkAvailability(date)) {
            while (AssignRegistration.Assign((central_queue->highrisk_queue->Minimum()), date) && central_queue->highrisk_queue->GetNum()) {
                // keep assign until no further registrations can be assigned
                central_queue->highrisk_queue->ExtractMin();
                // TODO table management
            }
        }


        // if counter % 7 == 0, generate reports
        if (timer % 14 == 0){
            central_IO.ReportWeekly(timer / 14, order);
        }
        if (timer % 60 == 0){
            central_IO.ReportMonthly(timer / 60, order);
        }

        // if counter % 30 == 0, generate weekly reports


    }
    return 0;
}