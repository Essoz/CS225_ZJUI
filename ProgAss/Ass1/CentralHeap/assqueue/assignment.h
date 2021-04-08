#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H
#include "../fibheap_f.h"

class AllLocations;
class Location;

class Assignment{
    public: 
        Assignment(AllLocations* all_locations, FibHeap* heap);
        bool Assign(FibNode* reg, int date); // on false goes to the next day
        bool checkAvailability(int date);
    private:
        void _assign(FibNode* reg, int date);
        AllLocations* all_locations;
        FibHeap* heap;
        // maxnum; // number of locations 
        // currentnum; // current number of available locations //TODO I don't have to 
        // Assignment(int )

};
Assignment::Assignment(AllLocations* all_locations, FibHeap* heap) {
    Assignment::all_locations = all_locations;  
    Assignment::heap = heap;
}


/* Locations for medical treatment */
class AllLocations{
    public:
        friend class Assignment;
        AllLocations(vector<Location*>&location_list);
        int getNumLocs();
        int calcCapacity(int date);
        void maintainCuredList(int week);
    private:
        int max_capacity;
        int current_occupied;
        int current_capacity;
        int num_locations;
        vector<Location*> location_list;
        vector<vector<FibNode*>> cured_list;

};

AllLocations::AllLocations(vector<Location*>&location_list) {
    AllLocations::location_list = location_list;
}

class Location{
    public:
        friend class AllLocations;
        Location(int id, vector<string>&time_slot);
        int id;
        int daily_capacity;
        int checkAvailability(int date);
        int assignedInsert(int date, FibNode* new_node);
        void assignedClear(int date); // TODO
        FibNode* findAppointment(Appointment* app);
        void removeAppointment(Appointment* app);
        vector<string> time_slot;
    private:
        vector<vector<FibNode*>> assigned_queue;  // the first dimension is day
        vector<vector<FibNode*>> cured_queue;  // the first dimension is week
};


Location::Location(int id, vector<string>&time_slot) {
    Location::id = id;
    Location::time_slot = time_slot;
    daily_capacity = int(time_slot.size());
};




/* Local registries */
class Registry{
    public:
        Registry(int id, vector* location_dist);
        int id;
        vector* location_dist;
    private:
};

Registry::Registry(int id, vector* location_dist) {
    Registry::id = id;
    Registry::location_dist = location_dist;
};

#endif