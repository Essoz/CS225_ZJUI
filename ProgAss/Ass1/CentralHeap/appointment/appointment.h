#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include "../assqueue/assignment_f.h"
using namespace std;
class Appointment{
    public:
        friend class AllLocation;
        Appointment(Location* loc, int date_assigned, int time_slot_assigned);
        
        Location* loc;
        string assigned_date;
        string assigned_time;
        string cured_date;
        string calcDate(int time_slot_assigned ,int date);
        void setCured();
        int getDate();
        int getTime();
    private:
        int date_assigned;
        int date_cured;
        int time_slot_assigned;
};

Appointment::Appointment(Location* loc, int date_assigned, int time_slot_assigned){
    Appointment::loc = loc;
    Appointment::date_assigned = date_assigned;
    Appointment::time_slot_assigned = time_slot_assigned;
    setCured();
};

#endif