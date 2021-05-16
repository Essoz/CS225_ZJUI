#ifndef ASSIGNMENT_F_H
#define ASSIGNMENT_F_H

//#include "assignment.h"
using namespace std;

/* Assignment::Assign
 * INPUT
 * 1. a registration to be assigned
 * 2. a date to assign the registration
 * OUTPUT
 * 1. true on assignment succeeded
 * 2. false on assignment failed
 * EFFECT & Implications
 * 1. Extension is handled here
 * 2. IF DDL has not passed, 
 *      a. remove the original appointment and
 *      b. give the registration a new assignment and 
 *      c. **TODO** remove the registration from the ddl
 *      d. **TODO** remove the registration from any table it is in 
 *        (**TODO** Note that in _assign function the registration should be added to location)
 *  return true  
 * 3. if the node is in highrisk heap, 
 *      a. assign the node
 *      b. remove the node from corresponding heap
 *      c. remove the node from corresponding heap hash table
 */


Assignment::Assignment(AllLocations* all_locations, AllRegistries* all_registries) {
    Assignment::all_locations = all_locations;  
    Assignment::all_registries = all_registries;
}

AllLocations::AllLocations(vector<Location*>&location_list) {
    AllLocations::location_list = location_list;
    num_locations = int(location_list.size());
    for (int i = 0; i < num_locations; i++) {
        max_capacity += location_list[i]->getCapacity();
    }
    cured_list.resize(52);

}
Location::Location(int id, vector<string>&time_slot, FibHeap* n_vacc_heap, FibHeap* n_surg_heap, FibHeap* n_regi_heap) {
    Location::id = id;
    Location::time_slot = time_slot;
    heaps[0] = n_vacc_heap;
    heaps[1] = n_surg_heap;
    heaps[2] = n_regi_heap;

    daily_capacity = int(time_slot.size());

    assigned_queue[0].resize(360);
    assigned_queue[1].resize(360);
    assigned_queue[2].resize(360);
    cured_queue.resize(52);
}

AllRegistries::AllRegistries(vector<Registry*>&registry_list) {
    AllRegistries::registry_list = registry_list;
}


Registry::Registry(int id, vector<int>&location_dist) {
    Registry::id = id;
    Registry::location_dist = location_dist;
}

bool Assignment::Assign(FibNode* reg, int date) {

    // no extension rules here lol
    
    // if no ddl or extension
    registration* Reg = --Registration_Relation.Retrieve(reg->getRegID());
    int8_t type = Reg->getTreatmentType();
    if (checkAvailability(date, type) == false){
        return false;
    }
    // this leaves the case where the node can be assigned

    _assign(reg, date, type);

    
    return true;
}

/* Assignment::_assign
 * INPUT
 * 1. a given registration
 * 2. a given date to assign the registration
 * OUTPUT
 * 1. NONE
 * EFFECT
 * 1. reg - ss
 * 
 */

void Assignment::_assign(FibNode* reg, int date, int8_t type) {
    registration Reg = --Registration_Relation.Retreieve(reg->getRegID());
    Registry* registry = all_registries->getRegistry(Reg.getRegID());  
    Location* temp_location;
    for (int i = 0; i < int(registry->getLocationDist().size()); i++) {
        temp_location = all_locations->getLocation(registry->getLocationDist()[i]);
        if (temp_location->checkAvailability(date, type)) {
            int temp_time_assigned = temp_location->assignedInsert(date, reg, type); 
            registration n_Reg = Reg;
            n_Reg.setAssignStatus(true);
            n_Reg.setAssignedLoc(i);
            n_Reg.setAssignedDate(to_string(date));
            n_Reg.setAssignedTime(temp_time_assigned);
            --Registration_Relation.Delete(Reg.getID());
            --Registration_Relation.Insert(n_Reg);
            break;
        }
    }
}

bool Assignment::checkAvailability(int date, int8_t type) {
    if (all_locations->calcCapacity(date, type)) return true;
    return false;
}

int AllLocations::getNumLocs(){
    return num_locations;
}
Location* AllLocations::getLocation(int id) {
    return location_list.at(id);
}

int AllLocations::calcCapacity(int date, int8_t type){
    current_occupied = 0;
    for (int i = 0; i < int(location_list.size()); i++) {
        current_occupied += location_list[i]->assigned_queue[type].at(date).size();
    }
    current_capacity = max_capacity - current_occupied;
    return current_capacity;
}   

void AllLocations::maintainCuredList(int date){
    int week = date / 7 - 1;
    
        // vector<FibNode*> temp;
    for (int i = 0; i < int(location_list.size()); i++) {
        cured_list.at(week).insert(cured_list.at(week).end(), 
        location_list[i]->cured_queue.at(week).begin(),
        location_list[i]->cured_queue.at(week).begin() + location_list[i]->cured_queue.at(week).size()
        );
        // for (int j = 0; j < int(location_list[i]->cured_queue.at(week).size()); j++) {
        //     cured_list.at(week).push_back(location_list[i]->cured_queue.at(week)[j]);
        // }
    }
    // cout << "\nYOU ARE FUCKED UP at AllLocations::maintainCuredList\n";
}

/*
 * OUTPUT
 * 1. the time_slot assigned
 */
int Location::assignedInsert(int date, FibNode* new_node, int8_t type) {
    if (checkAvailability(date, type)) {
        assigned_queue[type].at(date).push_back(new_node);
        // return true;
    } else {exit(3);} 
    return (assigned_queue[type].at(date).size() - 1);
}

int Location::getID() {
    return id;
}

int Location::getCapacity() {
    return daily_capacity;
}

/* Location::assignedRemove
 * INPUT
 * 1. date
 * OUTPUT
 * 1. none
 * EFFECT
 * 1. when a day has passed, move all nodes into the cured list
 * 2. Create Treatment Tuples and and insert into 
 */ 
void Location::assignedClear(int date) {
    int week = date / 7;    // week is equal to the actual week - 1
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < int(assigned_queue[j].at(date).size()); i++) {
            cured_queue.at(week).push_back(assigned_queue[j].at(date)[i]);
            registration Reg = --Registration_Relation.Retrieval(assigned_queue[j].at(date)[i]->getRegID());
            
            treatment Tre = treatment(tre_id_counter++, Reg.getAssignedLoc(), Reg.getTreatmentType(), 
                Reg.getAssignedDate(), Reg.getAssignedDate());
            --Treatment_Relation.Insert(Tre); 
        }
    assigned_queue[j].at(date).clear();
    }
    // clear the assignment queue for that specific date
}

/* Location::checkAvailability
 * INPUT
 * 1. date
 * OUTPUT 
 * 1. number of remained capacity (how many appointments left can be made) 
 */
int Location::checkAvailability(int date, int8_t type) {
    return (daily_capacity - assigned_queue[type].at(date).size());
}

FibNode* Location::findAppointment(registration* Reg){
    int8_t type = Reg->getTreatmentType();
    return assigned_queue[type][stoi(Reg->getAssignedDate())][Reg->getAssignedTime()];
}

void Location::removeAppointment(registration* Reg){
    int8_t type = Reg->getTreatmentType();
    assigned_queue[type][stoi(Reg->getAssignedDate())].erase(assigned_queue[type][stoi(Reg->getAssignedDate())].begin() + Reg->getAssignedTime());
}

string Location::getTimeSlotAssigned(int time_slot_assigned) {
    return time_slot[time_slot_assigned];
}

vector<int>& Registry::getLocationDist() {
    return location_dist;
}

Registry* AllRegistries::getRegistry(int id) {
    return registry_list.at(id);
}
/* AllLocations::updateLocs(int date) 
 * **This Function Must Be Called On a Daily Basis** 
 * INPUT
 * 1. date
 * OUTPUT
 * 1. NONE
 * EFFECT
 * 1. it calls assignedClear() on every location to move each day's cured assignments from assigned queue to cured queue
 * 2. it gathers all cured assignments (in last week) from locations to AllLocations on the beginning of each weel
 */ 
void AllLocations::updateLocs(int date) {
    for (int i = 0; i < int(location_list.size()); i++) {
        if (date >= 1)
        location_list.at(i)->assignedClear(date - 1);
    }
    if (date && date % 7 == 0)   // because t
    maintainCuredList(date);
}
#endif