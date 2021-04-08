#ifndef APPOINTMENT_F_H
#define APPOINTMENT_F_H

#include "appointment.h"
#include <string>

using namespace std;
/* setCured
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
};

string Appointment::calcDate(int time_slot_assigned, int date){
    // to be implemented  (convert a date (int) to string)
    string month = to_string(date/30);
    string day = to_string(date%30);
    string output= month + " - " + day;

    output += string(" at ") + loc->time_slot[time_slot_assigned];
    return output;
};

int Appointment::getDate(){
    return date_assigned;
}
int Appointment::getTime(){
    return time_slot_assigned;
}
#endif