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


Assignment::Assignment(AllLocations* all_locations, AllRegistries* all_registries, FibHeap* heap) {
    Assignment::all_locations = all_locations;  
    Assignment::all_registries = all_registries;
    Assignment::heap = heap;

}

AllLocations::AllLocations(vector<Location*>&location_list) {
    AllLocations::location_list = location_list;
    num_locations = int(location_list.size());
    for (int i = 0; i < num_locations; i++) {
        max_capacity += location_list[i]->getCapacity();
    }
    cured_list.resize(52);

}

Location::Location(int id, vector<string>&time_slot) {
    Location::id = id;
    Location::time_slot = time_slot;
    daily_capacity = int(time_slot.size());
    assigned_queue.resize(360);
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

    // medium risk overwrites withdrawn
    if (reg->getrisk() == 2) date += 30;
    else if (reg->getwithdraw() == 2) date += 14;

    
    // if no ddl or extension
    if (checkAvailability(date) == false){
        return false;
    }
    // this leaves the case where the node can be assigned

    if (heap->ddl_incheck(reg)){
        // if ddl has not passed, 
        if (date < (reg->getddl() - 1)){
            // remove the original appointment
            Location* old_loc = reg->getAppointment()->loc;
            old_loc->removeAppointment(reg->getAppointment());
            _assign(reg,date);
            if (heap->hash_intable_check(reg->getid())) {
                heap->hash_table_remove(reg->getid());
                heap->ExtractMin();
            }
            if (heap->highrisk_intable_check(reg->getid())) { 
                heap->highrisk_table_remove(reg->getid());
                //actual remove the node
                heap->highrisk_queue->ExtractMin();
            }
        }  
        // else do nothing because there is no need for re-assigning
        return true;
    }

    if (heap->highrisk_intable_check(reg->getid())){

        _assign(reg, date);
        heap->highrisk_table_remove(reg->getid());
        
    
    } else if (heap->hash_intable_check(reg->getid())){
        _assign(reg,date);
        heap->hash_table_remove(reg->getid());
    } 
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

void Assignment::_assign(FibNode* reg, int date) {
    Registry* registry = all_registries->getRegistry(reg->getreg_id());  //TODO, constructor here!!!!!!!!
    Location* temp_location;
    for (int i = 0; i < int(registry->getLocationDist().size()); i++) {
        temp_location = all_locations->getLocation(registry->getLocationDist()[i]);
        if (temp_location->checkAvailability(date)) {
            int temp_time_assigned = temp_location->assignedInsert(date, reg); 
            Appointment* reg_app = new Appointment(
            temp_location, date, temp_time_assigned);
            reg->setAppointment(reg_app);
            heap->assigned_table_insert(reg);
            break;
        }
    }
}

bool Assignment::checkAvailability(int date) {
    if (all_locations->calcCapacity(date)) return true;
    return false;
}

int AllLocations::getNumLocs(){
    return num_locations;
}
Location* AllLocations::getLocation(int id) {
    return location_list.at(id);
}

int AllLocations::calcCapacity(int date){
    current_occupied = 0;
    for (int i = 0; i < int(location_list.size()); i++) {
        current_occupied += location_list[i]->assigned_queue.at(date).size();
    }
    current_capacity = max_capacity - current_occupied;
    return current_capacity;
}   

void AllLocations::maintainCuredList(int date){
    int week = date / 7;
    
        // vector<FibNode*> temp;
    for (int i = 0; i < int(location_list.size()); i++) {
        for (int j = 0; j < int(location_list[i]->cured_queue.at(week).size()); j++) {
            cured_list.at(week).push_back(location_list[i]->cured_queue.at(week)[j]);
        }
    }
    // cout << "\nYOU ARE FUCKED UP at AllLocations::maintainCuredList\n";
    
}
/*
 * OUTPUT
 * 1. the time_slot assigned
 */
int Location::assignedInsert(int date, FibNode* new_node) {
    if (checkAvailability(date)) {
        assigned_queue.at(date).push_back(new_node);
        return true;
    } else {exit(3);} 
    return (assigned_queue.at(date).end() - assigned_queue.at(date).begin());
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
 */ 
void Location::assignedClear(int date) {
    int week = date / 7;    // week is equal to the actual week - 1
    for (int i = 0; i < int(assigned_queue.at(date).size()); i++) {
        cured_queue.at(week).push_back(assigned_queue.at(date)[i]);
    }
    // clear the assignment queue for that specific date
    assigned_queue.at(date).clear();
}

/* Location::checkAvailability
 * INPUT
 * 1. date
 * OUTPUT 
 * 1. number of remained capacity (how many appointments left can be made) 
 */
int Location::checkAvailability(int date) {
    return (daily_capacity - assigned_queue.at(date).size());
}

FibNode* Location::findAppointment(Appointment* app){
    return assigned_queue[app->getDate()][app->getTime()];
}

void Location::removeAppointment(Appointment* app){
    assigned_queue[app->getDate()].erase(assigned_queue[app->getDate()].begin() + app->getTime());

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

void AllLocations::updateLocs(int date) {
    for (int i = 0; i < int(location_list.size()); i++) {
        if(date >= 1)
        location_list.at(i)->assignedClear(date - 1);
    }
    if (date % 7 == 1)   // because t
    maintainCuredList(date);
}
#endif