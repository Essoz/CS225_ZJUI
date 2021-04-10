#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H
// #include "../fibheap.h"
// #include "../appointment/appointment.h"

#include <string>
#include <vector>
using namespace std;

class FibHeap;
class FibNode;
class Appointment;

class AllLocations;
class Location;
class AllRegistries;
class Registry;

class Assignment{
    public: 
        Assignment(AllLocations* all_locations, FibHeap* heap);
        bool Assign(FibNode* reg, int date); // on false goes to the next day
        bool checkAvailability(int date);
    private:
        void _assign(FibNode* reg, int date);
        AllLocations* all_locations;
        AllRegistries* all_registries;
        FibHeap* heap;
        // maxnum; // number of locations 
        // currentnum; // current number of available locations //TODO I don't have to 
        // Assignment(int )

};



/* Locations for medical treatment */
class AllLocations{
    public:
        friend class Assignment;
        AllLocations(vector<Location*>&location_list);
        int getNumLocs();
        Location* getLocation(int id);
        int calcCapacity(int date);
        void maintainCuredList(int week);
    private:
        int max_capacity;
        int current_occupied;
        int current_capacity;
        int num_locations;
        vector<Location*> location_list;
        vector<vector<FibNode*>> cured_list;        // This Cured List is for cured printing

};



class Location{
    public:
        friend class AllLocations;
        Location(int id, vector<string>&time_slot);
        int getID();
        int checkAvailability(int date);
        int getCapacity();
        int assignedInsert(int date, FibNode* new_node);
        void assignedClear(int date); // TODO
        FibNode* findAppointment(Appointment* app);
        void removeAppointment(Appointment* app);
        string getTimeSlotAssigned(int time_slot_assigned);

    private:
        int id;
        int daily_capacity;
        vector<string> time_slot;
        vector<vector<FibNode*>> assigned_queue;  // the first dimension is day
        vector<vector<FibNode*>> cured_queue;  // the first dimension is week
};




class AllRegistries{
    public:
        friend class Assignment;
        AllRegistries(vector<Registry*>&registry_list);
        Registry* getRegistry(int id);
    private:
        vector<Registry*> registry_list;

};


/* Local registries */
class Registry{
    public:
        Registry(int id, vector<int>&location_dist);
        int id;
        vector<int>&getLocationDist();
    private:
        vector<int> location_dist;
};


#endif