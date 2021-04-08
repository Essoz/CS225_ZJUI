#ifndef APPOINTMENT_H
#define APPOINTMENT_H
#include <string>
using namespace std;
class Appoint{
    public:
        friend class AllLocation;
        Appoint(Location* loc, int date_assigned, int time_slot_assigned);
        
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

Appoint::Appoint(Location* loc, int date_assigned, int time_slot_assigned){
    Appoint::loc = loc;
    Appoint::date_assigned = date_assigned;
    Appoint::time_slot_assigned = time_slot_assigned;
    setCured();
};

#endif