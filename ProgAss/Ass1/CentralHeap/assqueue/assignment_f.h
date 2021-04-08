#ifndef ASSIGNMENT_F_H
#define ASSIGNMENT_F_H
#include "assignment.h"

bool Assignment::Assign(FibNode<int>* reg, int date) {

    
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
            Location* old_loc = all_locations->location_list[reg->getappointment()->loc->id].
            old_loc->removeAppointment(reg->getappointment());
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
void Assignment::_assign(FibNode<int>* reg, int date) {
    Registry* registry = reg->getreg();
    for (int i = 0; i < Registry->location_dist->size(); i++) {
        
        
        if (all_locations->location_list[*(Registry->location_dist)[i]].checkAvailability(date)) {
            int temp_time_assigned = assignedInsert(date, reg);
            all_locations->location_list[*(Registry->location_dist)[i]][date]
            Appointment* reg_app = new Appointment(
            , date, temp_time_assigned);
            reg->setappointment(reg_app);
            assigned_table_insert(reg);
        }
    }
}

int AllLocations::getNumLocs(){
    return num_locations;
}

int AllLocations::calcCapacity(int date){
    current_occupied = 0;
    for (int i = 0; i < location_list.size(); i++) {
        current_occupied += location_list[i]->assigned_queue[date].size();
    }
    current_capacity = max_capacity - current_occupied;
    return current_capacity;
}   

void AllLocations::maintainCuredList(int week){
    if (week >= cured_list.size()){
        // vector<FibNode<int>*> temp;
        for (int i = 0; i < location_list.size(); i++) {
            for (int j = 0; j < location_list[i]->cured_queue[week].size(); j++) {
                cured_list[week].push_back(location_list[i]->cured_queue[week][j]);
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
int Location::assignedInsert(int date, FibNode<int>* new_node) {
    if (checkAvailability(date)) {
        assigned_queue[date].push_back(new_node);
        return true;
    } else {exit(3);} 
    return (assigned_queue[date].end() - assigned_queue[date].begin());
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
    for (int i = 0; i < assigned_queue[date].size(); i++) {
        cured_queue[week].push_back(assigned_queue[date][i]);
    }
    // clear the assignment queue for that specific date
    assigned_queue[date].clear();
}

/* Location::checkAvailability
 * INPUT
 * 1. date
 * OUTPUT 
 * 1. number of remained capacity (how many appointments left can be made) 
 */
int Location::checkAvailability(int date) {
    return (daily_capacity - assigned_queue[date].size());
}

FibNode<int>* Location::findAppointment(Appointment* app){
    return assigned_queue[app->getDate()][app->getTime()];
}

void Location::removeAppointment(Appointment* app){
    assigned_queue[app->getDate()].erase(assigned_queue[app->getDate].begin() + app->getTime());

}
#endif