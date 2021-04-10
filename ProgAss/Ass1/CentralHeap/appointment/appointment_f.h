#ifndef APPOINTMENT_F_h
#define APPOINTMENT_F_H
//#include "appointment.h"

Appointment::Appointment(Location* loc, int date_assigned, int time_slot_assigned){
    Appointment::loc = loc;
    Appointment::date_assigned = date_assigned;
    Appointment::time_slot_assigned = time_slot_assigned;
    setCured();
}

/* Appointment::setCured
 * INPUT
 * 1. None
 * OUTPUT
 * 1. None
 * EFFECT
 * 1. date_cured set to the next date to the date assigned
 * 2. date_cured is converted into a string and stored in cured_date
 */
void Appointment::setCured(){
    date_cured = date_assigned + 1;
    cured_date = calcDate(time_slot_assigned, date_cured);
}
/* Appointment::calcDate
 * INPUT
 * 1. the assigned time slot of an appointment
 * 2. the assigned date of an appointment
 * OUTPUT
 * 1. a string generated using the given time slot, date and 
 * associated information from the assigned location
 */
string Appointment::calcDate(int time_slot_assigned, int date){
    // to be implemented  (convert a date (int) to string)
    string month = to_string(date/30);
    string day = to_string(date%30);
    string output= month + " - " + day;

    output += " at " + loc->getTimeSlotAssigned(time_slot_assigned);
    return output;
};

int Appointment::getDate(){
    return date_assigned;
}
int Appointment::getTime(){
    return time_slot_assigned;
}
string Appointment::getLocation(){
    string id_str = "0";
    id_str += loc->getID();
    return "Location-" + id_str;
}

#endif