/*for excise 1, this is the pridef for information in the data set*/
#ifndef BTREE_H
#define BTREE_H
#include <stdlib.h>
#include <string>

#define D_BLOCK_SIZE 4096 //Block size in bytes
using namespace std;


template <class T>
class Block_Header{
    public:
        friend class Block;

        Block_Header(bool if_is_overflow);
        int64_t     getSize()           {return size;}
        int64_t     getNum()            {return num_items;}
        int64_t     getNumDeleted()     {return num_deleted;}
        Block_Header<T>*
                    getOverflowBlock()  {return of_block_ptr;}
        void        setNum(int64_t new_num)            
                                        {num_items = new_num;}
        void        setNumDeleted(int64_t new_num)     
                                        {num_deleted = new_num;}
    private:
        int64_t     size;
        int64_t     num_items;
        int64_t     num_deleted;
        Block_Header<T>*
                    of_block_ptr;
        bool        is_overflow;

        // T*          reparrary;
};

template<class T>
Block_Header<T>::Block_Header(bool if_is_overflow){
    size = D_BLOCK_SIZE;
    num_items = 0;
    num_deleted = 0;    
    is_overflow = if_is_overflow;
}



template <class T> 
class Block{
    public:
        Block(bool if_is_overflow);
        Block_Header<T> header;
    private:
        T* reparray;
};

template <class T>
Block<T>::Block(bool if_is_overflow){
    header = Block_Header<T>(if_is_overflow);

    if (!if_is_overflow) {
        header.of_block_ptr = new Block<T>(true);
    } else {
        header.of_block_ptr->header.of_block_ptr = (Block<T>*) &header;
    }
}





/* <=== relational schema for PATIENT ===> */
class person{
    public:
        void        setID(int64_t id)               { ID = id; }
        void        setAddress(int64_t add)         { address = add; }
        void        setMedicalStatusID(int64_t id)  { med_id = id; }
        void        setProfession(int8_t pro)       { profession = pro; }
        void        setAge(int8_t a)                { age = a; }
        void        setName(string n)               { name = n; }
        void        setContact(string cont)         { email = cont; }
        void        setDateOfBirth(string birth)    { dayborn = birth; }

        int64_t     getID()                         { return ID; }
        int64_t     getAddress()                    { return address; }
        int64_t     getMedicalStatusID()            { return med_id; }
        int8_t      getProfession()                 { return profession; }
        int8_t      getAge()                        { return age; }
        string      getName()                       { return name; }
        string      getContact()                    { return email; }
        string      getDateOfBirth()                { return dayborn; }

    private:
        int64_t     ID;      // the primary key
        int64_t     address; // find the actual info in ADDRESS relation
        int64_t     med_id;
        int8_t      profession;
        int8_t      age;
        string      name;
        string      email;
        string      dayborn; // YY-MM-DD
};

/* <=== relational schema for MEDICAL STATUS ===> */
class medical_status{
    public:
        void        setID(int64_t id)           { ID = id; }
        void        setStatus(int8_t s)         { status = s; }
        int64_t     getID()                     { return ID; }
        int8_t      getStatus()                 { return status; }

    private:
        int64_t     ID;
        int8_t      status; // 0 - no risk | 1 - low risk | 2 - medium risk | 3 - high risk
};

/* <=== relational schema for REGISTRATION ===> */
class registration{
    public:
        void        setID(int64_t id)               { ID = id; }
        void        setPersonID(int64_t id)         { person_id = id; }
        void        setTreatmentID(int64_t id)      { treatment_id = id; }
        void        setDeadline(string ddl)         { deadline = ddl; }
        void        setDateOfReg(string time)       { date = time; }
        void        setWithdraw(int8_t status)      { withdrawn = status; }
        void        setAssignStatus(bool ass)       { assigned = ass; }
        void        setAssignedLoc(int64_t loc)     { assigned_loc = loc; }
        void        setAssignedTime(string time)    { assigned_date = time; }


        int64_t     getID()                         { return ID; }
        int64_t     getPersonID()                   { return person_id; }
        int64_t     getTreatmentID()                { return treatment_id; }
        string      getDeadline()                   { return deadline; }      // YY-MM-DD
        string      getDateOfReg()                  { return date; }          // YY-MM-DD
        int8_t      getWithdraw()                   { return withdrawn; }
        bool        getAssignStatus()               { return assigned; }
        int64_t     getAssignedLoc()                { return assigned_loc; }  // TODO: How can I modify those info later?? This is hard
        string      getAssignedTime()               { return assigned_date; }

    private:
        int64_t     ID;
        int64_t     person_id;
        int64_t     treatment_id;
        string      deadline;
        string      date;
        int8_t      withdrawn;
        bool        assigned;
        int64_t     assigned_loc;
        string      assigned_date;
};

/* <=== relational schema for TREATMENT ===> */
class treatment{
    public:
        void        setID(int64_t id)               { ID = id; }
        void        setAssignedLoc(int64_t loc)     { assigned_loc = loc; }
        void        setTreatType(int8_t type)       { treatment_type = type; }
        void        setAssignedTime(string time)    { assigned_date = time; }
        void        setFinishedTime(string time)    { end_date = time; }

        int64_t     getID()                         { return ID; }
        int64_t     getAssignedLoc()                { return assigned_loc; }
        int8_t      getTreatType()                  { return treatment_type; }
        string      getAssignedTime()               { return assigned_date; }
        string      getFinishedTime()               { return end_date; }

    private:
        int64_t     ID;
        int64_t     assigned_loc;
        int8_t      treatment_type;
        string      assigned_date;
        string      end_date;
};

#endif
