#include "assignment.h"

bool Assignment::Assign(FibNode* reg, int date) {

    
    // if no ddl or extension
    if (checkAvailability(date) == false){
        return false;
    }
    // this leaves the case where the node can be assigned

    // medium risk overwrites withdrawn
    if (reg->getrisk() == 2) date += 30;
    else if (reg->getwithdraw() == 2) date += 14;

    if (heap->ddl_incheck(reg)){
        // if ddl has not passed, 
        if (date < reg->getddl()){
            // remove the original appointment
            Location* old_loc = all_locations->location_list[reg->getappoint()->loc->id].
            old_loc->removeAppointment(reg->getappoint());
            _assign(reg,date);
        }  
        // else do nothing because there is no need for re-assigning
        return true;
    }

    if (highrisk_table_incheck(reg->getid())){

        _assign(reg, date);
        highrisk_table_remove(reg->getid());
        
    
    } else if (hash_table_incheck(reg->getid())){
        _assign(reg,date);
        hash_table_remove(reg->getid());
    } 
    return true;
}
/* insert in assigned_hash_table
 */
void Assignment::_assign(FibNode* reg, int date) {
    Registry* registry = reg->getreg();
    for (int i = 0; i < int(Registry->location_dist->size()); i++) {
        
        
        if (all_locations->location_list[*(Registry->location_dist)[i]].checkAvailability(date)) {
            int temp_time_assigned = assignedInsert(date, reg);
            Appointment* reg_app = new Appointment(
            all_locations->location_list[*(Registry->location_dist)[i]][date], date, temp_time_assigned);
            reg->setappoint(reg_app);
            assigned_table_insert(reg);
        }
    }
}

int AllLocations::getNumLocs(){
    return num_locations;
}

int AllLocations::calcCapacity(int date){
    current_occupied = 0;
    for (int i = 0; i < int(location_list.size()); i++) {
        current_occupied += location_list[i]->assigned_queue.at(date).size();
    }
    current_capacity = max_capacity - current_occupied;
    return current_capacity;
}   

void AllLocations::maintainCuredList(int week){
    if (week >= cured_list.size()){
        // vector<FibNode*> temp;
        for (int i = 0; i < int(location_list.size()); i++) {
            for (int j = 0; j < int(location_list[i]->cured_queue.at(week).size()); j++) {
                cured_list.at(week).push_back(location_list[i]->cured_queue.at(week)[j]);
            }
        }
    } else {
        cout << "\nYOU ARE FUCKED UP at AllLocations::maintainCuredList\n";
    }
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
    assigned_queue[app->getDate()].erase(assigned_queue[app->getDate].begin() + app->getTime());

}
