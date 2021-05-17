#ifndef Patient_h
#define Patient_h
#include <stdio.h>
#include <string>
using namespace std;

/*
 *  File: Patient.h
 *
 *  Writter: Guo Moyang
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
typedef struct
{
    std::string location;
    int year;       // The appointment year
    int date;       // The appointment date, from 1-365
} Appointment;

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
    // The three variables pertain to the status of withdraw. Non-zero value means satisfication.
    int activated;   // Indicate that the patient has been in the queue for x times because of the change of withdraw status
    int withdraw;    // Indicate that the patient has withdrew before
    int re_reg;      // Indicate that the patient has registered after withdraw
    int letter_ddl; // The deadline of the priority letter, should be -1 if no letter is handed in
    int priority;   // The priority of treatment
    Appointment* appointment;

public:
    Patient();
    Patient(int id, Risk risk, Profession professionLevel, Age a, Information* info, int regis_id, int year, int date, int ddl);      // Constructor for new patient

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
    void setactivated(int A)
    {
        activated = A;
    }
    void setwithdraw(int W)
    {
        withdraw = W;
    }
    void setre_reg(int R)
    {
        re_reg = R;
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
    void setappoint(Appointment* appo)
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
    int getactivated()
    {
        return activated;
    }
    int getwithdraw()
    {
        return withdraw;
    }
    int getre_reg()
    {
        return re_reg;
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
    Appointment* getappoint()
    {
        return appointment;
    }
    string getlocation() {
        return appointment->location;
    }
    // Other helper functions:
    int calculate_prio();     // Calculate the priority
};

Patient::Patient(int id, Risk risk, Profession professionLevel, Age a, Information* info, int regis_id, int year, int date, int ddl)
{
    setid(id);
    setrisk(risk);
    setpro(professionLevel);
    setage(a);
    setinfo(info);
    setreg_id(regis_id);
    setyear(year);
    setdate(date);
    setactivated(1);
    setwithdraw(0);
    setre_reg(0);
    setddl(ddl);
    // The priority needs to be calculated first:
    int prio = calculate_prio();
    setpriority(prio);
    setappoint(NULL);   // No appoinment yet
};

// The priority is represented by a int number, different fields occupy different places (letter_ddl is not considered):
int Patient::calculate_prio()
{
    int prio = 0;
    // Start from the registration time, they occupy the last 5 digits:
    prio = prio + date + 1000 * (year - 2000);
    // Then for age group, it stands for the least 6 digit:
    prio = prio + 100000 * age;
    // Finally for profession, 7th digit:
    prio = prio + 1000000 * profession;
    return prio;
}

#endif /* Patient_h */
