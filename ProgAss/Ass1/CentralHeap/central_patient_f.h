#ifndef CENTRAL_PATIENT_F_H
#define CENTRAL_PATIENT_F_H
#include "central_patient.h"

Patient::Patient(){}

Patient::Patient(int id, Risk risk, Profession professionLevel, Age a, Information* info, int regis_id, int year, int date, int withdraw, int ddl)
{
    setid(id);
    setrisk(risk);
    setpro(professionLevel);
    setage(a);
    setinfo(info);
    setreg_id(regis_id);
    setyear(year);
    setdate(date);
    setwithdraw(withdraw);
    setddl(ddl);
    // The priority needs to be calculated first:
    int prio = calculate_prio();
    setpriority(prio);
    setAppointment(NULL);   // No appoinment yet
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
#endif