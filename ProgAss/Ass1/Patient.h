#ifndef Patient_h
#define Patient_h

/*
 *  File: Patient.h
 *  
 *  Writter: Guo Moyang
 * 
 *  Description:
    This header file contains the class of "Patient", which has all the info 
 *  like "id number", "risk status" of each patient. 
 *  The file also defines some "set" and "get" helper functions to prevent direct
 *  access to the class fields.
 */

enum Risk {
    no, low, medium, high
};

enum Profession {
    children, adolescent, youngadult, adult, senior, elderly, old
};

// Structure of info which is not used in the priority issue:
typedef struct
{
    char name[10];
    char email[10];
    int phone;
    int birthday;
} Information;

// Info about the appointment processing:
typedef struct
{
    char location[10];
    int date;       // The format is the same as the registration
    int time;
} Appointment;

class Patient
{
private:
    int identificaiton;
    Risk risk;
    Profession profession;
    Information* information;
    //char name[10];
    //char email[10];
    //int  phone[10];
    int date; // The registeration date /*the format is YearMonthDate, Eg.20001204*/
    int time; // The precise registeration time /*the format is HourMinSec, Eg.184059*/
    bool withdraw;  // If the patient has withdrew before
    int letter_ddl; // The deadline of the priority letter, should be -1 if no letter is handed in
    int priority;   // The priority of treatment
    Appointment* appoint;

public:
    Patient(int id, Risk risk, Profession prof, Information* info, int date, int time, int ddl);      // Constructor for new patient
    //~Patient();

    /*set functions*/
    void setid(int id) {
        identificaiton = id;
    };
    void setrisk(Risk R) {
        risk = R;
    };
    void setprof(Profession prof) {
        profession = prof;
    }
    void setinfo(Information* info) {
        name = info.name;

    }
    void setdate(int D) {
        date = D;
    }
    void settime(int T) {
        time = T;
    }
    void setwithdraw(bool W)
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
    void setappoint(Appointment* appo)
    {
        appoint = appo;
    }
    /*get functions*/
    int getid() {
        return identificaiton;
    };
    Risk getrisk() {
        return risk;
    };
    Profession getprof() {
        return profession;
    }
    Information* getinfo() {
        return information;
    };
    int getdate() {
        return date;
    }
    int gettime() {
        return time;
    }
    bool getwithdraw()
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
    Appointment* getappoint()
    {
        return appoint;
    }

    // Other helper functions:
    int calculate_prio();     // Calculate the priority
};

Patient::Patient(int id, Risk risk, Profession prof, Information* info, int date, int time, int ddl)
{
    setid(id);
    setrisk(risk);
    setprof(prof);
    setinfo(info);
    setdate(date);
    settime(time);
    setwithdraw(false); // The new patient has no withdraw
    setddl(ddl);
    // The priority needs to be calculated first:
    int prio = calculate_prio();
    setpriority(prio);
    setappoint(NULL);   // No appoinment yet
};

int Patient::calculate_prio()
{
    int prio = 0;
    return prio;
}

#endif /* Patient_h */
