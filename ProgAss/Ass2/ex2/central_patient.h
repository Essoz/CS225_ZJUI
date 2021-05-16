#ifndef Patient_h
#define Patient_h
#include "appointment/appointment.h"
#include <stdio.h>
#include <string>
using namespace std;

/*
 *  File: Patient.h
 *
 *  Writter: Guo Moyang - Modified by Yuxuan Jiang
 *
 *
 *  Description:
    This header file contains the class of "Patient", which has all the information:
    identification,risk,age,ddl,priority,withdraw,
    also with trivial Information : name,email,phone,birthday
    and appointment : date, time, location
    All above have their get and set functions
    for Appointment, There are extra functions : settime gettime; setdate getdate
    for quick search and change of time & date;
 *
 *  --
 *  Modification -- Definition for Appointment is Removed
 */

enum Risk {
    no, low, medium, high
};
enum Profession {
    VIII, VII, VI, V, IV, III, II, I
};
enum Age {
    old, elderly, senior, adult, youngadult, adolescent, children,  
};

// Structure of info which is not used in the priority issue:
typedef struct
{
    std::string name;
    std::string email;
    std::string phone;
    std::string birthday;
} Information;

// Info about the appointment processing:
/*
typedef struct
{
    std::string location;
    int year;       // The appointment year
    int date;       // The appointment date, from 1-365
} Appointment;
*/

class Patient
{
private:
    int identification;
    Risk risk;
    Profession profession;
    Age age;
    Information* information;
    int registry_id;    // The id of the local registry
    int year;           // The registeration year
    int date;        // The date for registeration, the range is 1-365
    int withdraw;    // If the patient has withdrew before
    // 0 for never withdraw, 1 for withdraw, 2 for withdraw and re-regiseter
    int letter_ddl; // The deadline of the priority letter, should be -1 if no letter is handed in
    int priority;   // The priority of treatment
    Appointment* appointment;

public:
    Patient();
    Patient(int id, Risk risk, Profession professionLevel, Age a, Information* info, int regis_id, int year, int date, int withdraw, int ddl);      // Constructor for new patient

    /*set functions*/
    void setid(int id) {
        identification = id;
    };
    void setrisk(Risk R) {
        risk = R;
    };
    void setpro(Profession professionLevel) {
        profession = professionLevel;
    };
    void setage(Age a) {
        age = a;
    }
    void setreg_id(int id) {
        registry_id = id;
    }
    void setyear(int Y) {
        year = Y;
    }
    void setdate(int D) {
        date = D;
    }
    void setwithdraw(int W)
    {
        withdraw = W;
    }
    void setddl(int ddl)
    {
        letter_ddl = ddl;
    }
    void setpriority(int prio)
    {
        priority = prio;
    }
    void setinfo(Information* info) {
        information = info;
    }
    void setname(string name) {
        information->name = name;
    }
    void setemail(string email) {
        information->email = email;
    }
    void setphone(string phone) {
        information->phone =phone;
    }
    void setbirthday(string bir) {
        information->birthday = bir;
    }
    void setAppointment(Appointment* appo)
    {
        appointment = appo;
    }

    /*get functions*/
    int getid() {
        return identification;
    };
    Risk getrisk() {
        return risk;
    };
    Profession getpro() {
        return profession;
    };
    Age getage() {
        return age;
    }
    int getreg_id() {
        return registry_id;
    }
    int getyear() {
        return year;
    }
    int getdate() {
        return date;
    }
    int getwithdraw()
    {
        return withdraw;
    }
    int getddl()
    {
        return letter_ddl;
    }
    int getpriority()
    {
        return priority;
    }
    Information* getinfo() {
        return information;
    }
    string getname() {
        return information->name;
    }
    Appointment* getAppointment()
    {
        return appointment;
    }
    string getlocation() {
        return appointment->getLocation();
    }
    // Other helper functions:
    int calculate_prio();     // Calculate the priority
};

#endif /* Patient_h */
