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
    and appointment : date, time, location
    All above have their get and set functions
    for Appointment, There are extra functions : settime gettime; setdate getdate
    for quick search and change of time & date;
 *
 */

enum Risk {
    high, medium, low, no
};
enum Profession {
    I, II, III, IV, V, VI, VII, VIII
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
    int year;       // The appointment year
    int date;       // The appointment date, from 1-365
} Appointment;

class Patient
{
private:
    int identificaiton;
    Risk risk;
    Profession profession;
    Age age;
    Information* information;
    int year;       // The registeration year
    int date;        // The date for registeration, the range is 1-365
    int withdraw;   // If the patient has withdrew before
    // 0 for never withdraw, 1 for withdraw, 2 for withdraw and re-regiseter
    int letter_ddl; // The deadline of the priority letter, should be -1 if no letter is handed in
    int priority;   // The priority of treatment
    Appointment* appointment;

public:
    Patient(int id, Risk risk, Profession professionLevel, Age a, Information* info, int year, int date, int withdraw, int ddl);      // Constructor for new patient

    /*set functions*/
    void setid(int id) {
        identificaiton = id;
    };
    void setrisk(Risk R) {
        risk = R;
        // The medium risk has one month extension:
        if (R == medium)
        {
            // Add the extension and increase the risk status:
            risk = low;
            date = date + 30;
            // Go to the next year
            if (date >= 365)
            {
                date = date % 365;
                year = year + 1;
            }
        }
    };
    void setpro(Profession professionLevel) {
        profession = professionLevel;
    };
    void setage(Age a) {
        age = a;
    }
    void setyear(int Y) {
        year = T;
    }
    void setdate(int D) {
        date = D;
    }
    void setwithdraw(int W)
    {
        withdraw = W;
        // If the patient has re-registered again, add an extension of two weeks:
        if (2 == W)
        {
            date = date + 14;
            // Go to the next year
            if (date >= 365)
            {
                date = date % 365;
                year = year + 1;
            }
        }
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
        information->phone = info->phone;
        information->phone = info->phone;
        for (int i = 0; i < 10; i++)
        {
            information->name[i] = info->name[i];
            information->email[i] = info->email[i];
        }
    }
    void setappoint(Appointment* appo)
    {
        appointment->year = appo->year;
        appointment->date = appo->date;
        for (int i = 0; i < 10; i++)
        {
            appointment->location[i] = appo->location[i];
        }
    }

    /*get functions*/
    int getid() {
        return identificaiton;
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
    Appointment* getappoint()
    {
        return appointment;
    }
    char* getlocation() {
        return appointment->location;
    }
    // Other helper functions:
    int calculate_prio();     // Calculate the priority
};

Patient::Patient(int id, Risk risk, Profession professionLevel, Age a, Information* info, int year, int date, int withdraw, int ddl)
{
    setid(id);
    setrisk(risk);
    setpro(professionLevel);
    setage(a);
    setinfo(info);
    setyear(year);
    setdate(date);
    setwithdraw(withdraw);
    setddl(ddl);
    // The priority needs to be calculated first:
    int prio = calculate_prio();
    setpriority(prio);
    setappoint(NULL);   // No appointment yet
};

// The priotiry is represented by a int number, different fields occupy different places (letter_ddl is not considered):
int Patient::calculate_prio()
{
    int prio = 0;
    // Start from the registration time, they occupy the last 5 digits:
    prio = prio + (1000 - date) + 1000 * (100 - (year - 2000));
    // Then for age group, it stands for the least 6 digit:
    prio = prio + 100000 * age;
    // Finally for profession, 7th digit:
    prio = prio + 1000000 * profession;
    return prio;
}

#endif /* Patient_h */
