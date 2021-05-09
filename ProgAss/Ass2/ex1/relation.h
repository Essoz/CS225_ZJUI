/*for excise 1, this is the pridef for information in the data set*/
#ifndef BTREE_H
#define BTREE_H
#include <stdlib.h>
#include <string>

#define BLOCK_SIZE 4096 //Block size in bytes
using namespace std;



template<class T> class<T> Block{
    public:
    Block* 
    private:

};


/* <=== relational schema for PARENT ===> */
class person{
    public:
        int64_t     getID()             {return ID;}
        int64_t     getAddress()        {return address;}
        int64_t     getMedicalStatusID(){return med_id;}
        string      getName()           {return name;}
        string      getContact()        {return email;}
        string      getDateOfBirth()    {return dayborn;}
        int8_t      getProfession()     {return profession;}


    private:
        int64_t     ID;      // the primary key
        int64_t     address; // find the actual info in ADDRESS relation
        int64_t     med_id;
	    string      name;
        string      email;
        string      dayborn; // YY-MM-DD
        int8_t      profession;
};

/* <=== relational schema for MEDICAL STATUS ===> */
class medical_status{
    public:
        int64_t     getID()             {return ID;}
        int8_t      getStatus()         {return status;}
    private:
        int64_t     ID;
        int8_t      status; // 0 - no risk | 1 - low risk | 2 - medium risk | 3 - high risk
};

/* <=== relational schema for REGISTRATION ===> */
class registration{
    public:
        int64_t     getID()             {return ID;}
        int64_t     getPersonID()       {return person_id;}
        int64_t     getTreatmentID()    {return treatment_id;}
        int8_t      getTreatType()      {return treatment_type;}
        string      getDeadline()       {return deadline;}      // YY-MM-DD
        string      getDateOfReg()      {return date;}          // YY-MM-DD
        bool        getWithdraw()       {return withdrawn;}
        bool        getAssignStatus()   {return assigned;}
        int64_t     getAssignedLoc()    {return assigned_loc;}  // TODO: How can I modify those info later?? This is hard
        string      getAssignedTime()   {return assigned_date;}

    private:
        int64_t     ID;
        int64_t     person_id;
        int64_t     treatment_id;
        int8_t      treatment_type;
        string      deadline;
        string      date;
        bool        withdrawn;
        bool        assigned;
        int64_t     assigned_loc;
        string      assigned_date;
}

/* <=== relational schema for TREATMENT ===> */
class treatment{
    public:
        int64_t     getID()             {return ID;}
        int64_t     getAssignedLoc()    {return assigned_loc;}
        string      getAssignedTime()   {return assigned_date;}
        string      getFinishedTime()   {return end_date;}
    private:
        int64_t     ID;
        int64_t     assigned_loc;
        string      assigned_date;
        string      end_date;
}






#endif
