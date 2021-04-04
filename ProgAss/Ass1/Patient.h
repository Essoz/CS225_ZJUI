#ifndef Patient_h
#define Patient_h

/*
 *  File: Patient.h
 *  
 *  Writter: Guo Moyang
 * 
 *  Description:
    This header file contains the class of "Patient", which has all the information:
    identification,risk,age,ddl,priority,withdraw,
    also with trivial Information : name,email,phone,birthday
    and appointment : date, time, locaiton
    All above have their get and set funcitons
    for Appointment, There are extra funciton : settime gettime; setdate getdate
    for quick search and change of time & date; 
 *  
 */

enum Risk {
    no, low, medium, high
};

enum Age {
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
    int date;       // The registeration date /*the format is YearMonthDate, Eg.20001204*/
    int time;       // The precise registeration time /*the format is HourMinSec, Eg.184059*/
} Appointment;

class Patient
{
private:
    int identificaiton;
    Risk risk;
    Age age;
    Information* information;
    //char name[10];
    //char email[10];
    //int  phone[10];
    bool withdraw;  // If the patient has withdrew before
    int letter_ddl; // The deadline of the priority letter, should be -1 if no letter is handed in
    int priority;   // The priority of treatment
    Appointment* appointment;
    //char location[10];
    //int date;       // The registeration date /*the format is YearMonthDate, Eg.20001204*/
    //int time;       // The precise registeration time /*the format is HourMinSec, Eg.184059*/
public:
    Patient(int id, Risk risk, Age a, Information *info, Appointment *appo, int ddl);      // Constructor for new patient
    //~Patient();

    /*set functions*/
    void setid(int id) {
        identificaiton = id;
    };
    void setrisk(Risk R) {
        risk = R;
    };
    void setage(Age a) {
        age = a;
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
    void setinfo(Information *info) {
        information->phone = info->phone;
        information->phone = info->phone;
        for (int i = 0; i < 10; i++)
        {
            information->name[i]=info->name[i];
            information->email[i]=info->email[i];
        }
    }
    void setappoint(Appointment *appo)
    {
       appointment->date = appo->date;
       appointment->time = appo->time;
        for (int i = 0; i < 10; i++)
        {
            appointment->location[i]=appo->location[i];
        }
    }
    void settime(int T){
        appointment->time=T;
    }
    void setdate(int D){
        appointment->date=D;
    }
    /*get functions*/
    int getid() {
        return identificaiton;
    };
    Risk getrisk() {
        return risk;
    };
    Age getage() {
        return age;
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

    Information* getinfo() {
        return information;
    }

    Appointment* getappoint()
    {
        return appointment;
    }
    int getdate() {
        return appointment->date;
    }
    int gettime() {
        return appointment->time;
    }
    char* getlocation(){
        return appointment->location;
    }
    // Other helper functions:
    int calculate_prio();     // Calculate the priority
};

Patient::Patient(int id, Risk risk, Age a, Information *info, Appointment *appo, int ddl)
{
    setid(id);
    setrisk(risk);
    setage(a);
    setinfo(info);
    //setdate(date);
    //settime(time);
    setwithdraw(false); // The new patient has no withdraw
    setddl(ddl);
    // The priority needs to be calculated first:
    int prio = calculate_prio();
    setpriority(prio);
    setappoint(appo);   // No appoinment yet
};

int Patient::calculate_prio()
{
    int prio = 0;
    return prio;
}

#endif /* Patient_h */
