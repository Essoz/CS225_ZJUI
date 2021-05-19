#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H
#include <string>
#include <vector>
#include "../../ex1/relation.h"
using namespace std;

registration* Reg_Relation_Delete(int64_t ID);
void Reg_Relation_Insert(registration* Reg);
registration* Reg_Relation_Retrieve(int64_t ID);
vector<registration*>& Reg_Relation_Retrieve_2(int8_t withdraw);
vector<registration*>& Reg_Relation_Retrieve_3(bool assigned);
void Per_Relation_Insert(person* Per);
person* Per_Relation_Delete(int64_t ID);
person* Per_Relation_Retrieve(int64_t ID);
void Tre_Relation_Insert(treatment* Tre);
treatment* Tre_Relation_Delete(int64_t ID);
treatment* Tre_Relation_Retrieve(int64_t ID);
vector<treatment*>& Tre_Relation_Retrieve_2(int64_t week);


class FibNode;
class FibHeap;
class Appointment;
class AllLocations;
class AllRegistries;
class CentralIO;

int64_t tre_id_counter = 0;

class Assignment{
    public: 
    friend class CentralIO;
        Assignment(AllLocations* all_locations, AllRegistries* all_registries);
        bool Assign(FibNode* reg, int date); // on false goes to the next day
        bool checkAvailability(int date, int8_t type);
        void removeAppointment(registration* Reg);
    private:
        void _assign(FibNode* reg, int date, int8_t type);
        AllLocations* all_locations;
        AllRegistries* all_registries;
        // maxnum; // number of locations 
        // currentnum; // current number of available locations 
        // Assignment(int )

};

class Location{
    public:
        friend class AllLocations;
        Location(int id, vector<string>&time_slot, FibHeap* n_vacc_heap, FibHeap* n_surg_heap, FibHeap* n_regi_heap);
        int getID();
        int checkAvailability(int date, int8_t type);
        int getCapacity();
        int assignedInsert(int date, FibNode* new_node, int8_t type);
        void assignedClear(int date); 
        FibNode* findAppointment(registration* Reg);
        void removeAppointment(registration* Reg);
        string getTimeSlotAssigned(int time_slot_assigned);

    private:
        int id;
        int daily_capacity;
        FibHeap* heaps[3];
        vector<string> time_slot;
        vector<vector<FibNode*>> assigned_queue[3];  // the first dimension is type the first dimension is day
        vector<vector<FibNode*>> cured_queue;  // the first dimension is week
};

/* Locations for medical treatment */
class AllLocations{
    public:
        friend class Assignment;
        friend class CentralIO;
        AllLocations(vector<Location*>&location_list);
        int getNumLocs();
        Location* getLocation(int id);
        int calcCapacity(int date, int8_t type);
        void updateLocs(int date);
        void maintainCuredList(int week);

    private:
        int max_capacity;
        int current_occupied;
        int current_capacity;
        int num_locations;
        vector<Location*> location_list;
        vector<vector<FibNode*>> cured_list;        // This Cured List is for cured printing

};

/* Local registries */
class Registry{
    public:
        Registry(int id, vector<int>&location_dist);
        int id;
        vector<int>& getLocationDist();
    private:
        vector<int> location_dist;
};

class AllRegistries{
    public:
        friend class Assignment;
        AllRegistries(vector<Registry*>&registry_list);
        Registry* getRegistry(int id);
    private:
        vector<Registry*> registry_list;

};

#endif
