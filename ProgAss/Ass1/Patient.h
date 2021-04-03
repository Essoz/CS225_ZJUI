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

// Structure of info which is not used in the priority issue:
typedef struct
{
    char name[10];
    char email[10];
    int phone;
    int birthday;
} Information;

enum Risk {
    no, low, medium, high
};

enum Profession {
    children, adolescent, youngadult, adult, senior, elderly, old
};

class Patient
{
private:
    int identificaiton;
    Risk risk;
    Profession profession;
    Information information;
    //char name[10];
    //char email[10];
    //int  phone[10];
    int date; // The registeration date /*the format is YearMonthDate, Eg.20001204*/
    int time; // The precise registeration time /*the format is HourMinSec, Eg.184059*/
public:
    Patient();  // default constructor
    Patient(int id, Risk risk, Profession prof, Information info, int date, int time);
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
    void setinfo(Information info) {
        name = info.name;

    }
    void setdate(int D) {
        date = D;
    }
    void settime(int T) {
        time = T;
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
};

Patient::Patient(int id, Risk risk, Profession prof, Information info, int date, int time)
{
    setid(id);
    setrisk(risk);
    setprof(prof);
    setinfo(info);
    setdate(date);
    settime(time);
};

#endif /* Patient_h */
