#ifndef APPOINTMENT_H
#define APPOINTMENT_H
#include <string>
#include "../assqueue/assignment.h"
using namespace std;

class Appointment{
    public:
        friend class AllLocation;
        Appointment();
        Appointment(Location* loc, int date_assigned, int time_slot_assigned);
        
        Location* loc;
        string assigned_date;
        string assigned_time;
        string cured_date;
        string calcDate(int time_slot_assigned ,int date);
        void setCured();
        int getDate();
        int getTime();
        string getLocation();
    private:
        string location_assigned;
        int date_assigned;
        int date_cured;
        int time_slot_assigned;
};



#endif
