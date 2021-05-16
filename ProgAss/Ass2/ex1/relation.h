/*for excise 1, this is the pridef for information in the data set*/
#ifndef DATABASE_H
#define DATABASE_H
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
//#define D_BLOCK_SIZE 4096       // Block size in bytes
using namespace std;
using std::cout;
using std::cin;

template<class T> class Block_Header;
class person;
class medical_status;
class registration;
class treatment;

template<class T>
struct content_t
{
    int64_t pri_id;
    T content;
};
template<class T>
using Content_t = content_t<T>;

/*
typedef content_t<person> person_t;
typedef content_t<medical_status> medical_status_t;
typedef content_t<registration> registration_t;
typedef content_t<treatment> treatment_t;
*/

template<class T>
class Block{
    friend class Block_Header<T>;

    public:
        Block(int64_t min, int64_t max);
        int64_t         getNum()        { return num_records; }
        //int64_t         getSize()       { return size; }
        int64_t         getmin_id()     { return min_id; }
        int64_t         getmax_id()     { return max_id; }
        void            setNum(int64_t num)     { num_records = num; }
        //void            setSize(int64_t s)      { size = s; }
        void            setmin_id(int64_t id)   { min_id = id; }
        void            setmax_id(int64_t id)   { max_id = id; }

        Content_t<T>    Retrieval(int64_t id);      // Find a record with primary key id
        int64_t         FindIndex(int64_t id);      // Find the index of one record in the block
        void            Insert(Content_t<T> record);// Insert a record
        void            Delete(int64_t id);         // Delete a record with primart key id

    private:
        int64_t             num_records;
        //int64_t             size;
        int64_t             min_id;     // The smallest id in this block
        int64_t             max_id;     // The largest id in this block
                                        // Note: The id in the current last block can be larger than the max_id!!!
        //Block_Header<T>*    header;
        vector<Content_t<T>>*          Overflow;   // The fixed length is 2
        vector<Content_t<T>>*          Reparray;   // The fixed length is 20
};

template<class T>
class Block_Header{
    public:
        friend class Block<T>;

        Block_Header();
        int64_t             getNum()                { return num_blks; }        // Number of blocks
        //int64_t             getNumDeleted()         { return num_deleted; }     // ???

        void                setNum(int64_t new_num)         { num_blks = new_num; }
        //void                setNumDeleted(int64_t new_num)  { num_deleted = new_num; }

        int64_t             find_block_id(int64_t id);      // Find the index of block where the primary key lies in
        Content_t<T>        Retrieval(int64_t id);          // Find a record with primary key id
        void                Insert(Content_t<T> record);    // Insert a record with primary key id
        void                Delete(int64_t id);             // Delete a record with primart key id
        //void                Merge(int64_t blk_id);          // Merge the given block with the next block
        void                Split(int64_t blk_id);          // Split the given block into two blocks
        void                Sort(int64_t blk_id);           // Sort the given block

    private:
        int64_t             num_blks;
        //int64_t             num_deleted;
        vector<Block<T>*>*  blk_reparray;
};

//
// Block_Header Methods:
template<class T> Block_Header<T>::Block_Header(){
    num_blks = 0;
    //num_deleted = 0;
    blk_reparray = new vector<Block<T>*>;
}

// Given a primary key, find the block where the primary key lies in with binary search method:
template<class T> int64_t Block_Header<T>::find_block_id(int64_t id) {
    int first = 0;                              // The former boundary
    int last = int(blk_reparray->size()) - 1;  // The latter boundary
    int middle;

    while (first != last)
    {
        middle = (last + first) / 2;
        // Now compare the id with the boundary values of the middle block:
        if (id < blk_reparray[middle]->getmin_id())
        {
            last = middle - 1;
        }
        else if (id > blk_reparray[middle]->getmax_id())
        {
            first = middle + 1;
        }
        else
        {
            return middle;
        }
    }
    return first;
}

// Find a record with primary key id:
template<class T> Content_t<T> Block_Header<T>::Retrieval(int64_t id) {
    int blk_id = find_block_id(id);
    return blk_reparray->at(blk_id)->Retrieval(id);
}

// Insert a record with some content:
template<class T> void Block_Header<T>::Insert(Content_t<T> record) {
    // First, check if there is no block:
    if (0 == num_blks)
    {
        // Create the first block
        Block<T>* blk = new Block<T>(0, 100);
        blk->Insert(record);
        blk->setNum(1);
        blk_reparray->push_back(blk);
        return;
    }

    int blk_id = find_block_id(record.pri_id);
    // Check if the overflow block is full:
    if (2 <= int(blk_reparray->at(blk_id)->Overflow->size()))
    {
        // Split into two blocks
        Split(blk_id);
        // Check which splitted block is the right one for insertion
        if (blk_reparray->at(blk_id)->getmax_id() < record.pri_id)
        {
            blk_reparray->at(blk_id + 1)->Insert(record);
        }
        else
        {
            blk_reparray->at(blk_id)->Insert(record);
        }
    }
    // If the overflow block is not full:
    blk_reparray->at(blk_id)->Insert(record);
}

// Delete a record with primart key id:
template<class T> void Block_Header<T>::Delete(int64_t id) {
    int blk_id = find_block_id(id);
    blk_reparray->at(blk_id)->Delete(id);

    // Check if the block needs merging:
    if (5 >= int(blk_reparray->at(blk_id)->Reparray->size()))
    {
        //Merge(blk_id);
    }
}

/*
// Merge the given block with the next block:
template <class T> void Block_Header<T>::Merge(int64_t blk_id) {
    Sort(blk_id);

}
*/

// Split the given block into two blocks:
template <class T> void Block_Header<T>::Split(int64_t blk_id) {
    Block<T>* blk = blk_reparray->at(blk_id);
    Sort(blk_id);
    // Calculate the id value at which we split:
    int64_t middle = blk->Reparray->at(9).pri_id;

    // Move the last half main block into the newly created block:
    Block<T>* new_blk = new Block<T>(middle, max(blk->Reparray->back().pri_id, blk->getmax_id()));
    blk->setmax_id(middle);
    for (int i = 10; i < 20; i++)
    {
        new_blk->Reparray->push_back(blk->Reparray->at(i));
        new_blk->setNum(new_blk->getNum() + 1);
        delete blk->Reparray->at(i);
        blk->setNum(blk->getNum() - 1);
    }

    // Then, we consider the overflow block, and insert them again:
    blk->setNum(blk->getNum() - 2);
    for (int i = 0; i < 2; i++)
    {
        if (blk->Overflow->at(i).pri_id > middle)
        {
            new_blk->Insert(blk->Overflow->at(i));
        }
        else
        {
            blk->Insert(blk->Overflow->at(i));
        }
        delete blk->Overflow->at(i);
    }

    // Finally, rearrange the pointers for block_Header:
    blk_reparray->insert(blk_reparray->begin() + blk_id, 1, new_blk);
    num_blks++;
}

// Sort the block by the indices (We do not sort overflow block):
template <class T> void Block_Header<T>::Sort(int64_t blk_id) {
    Block<T>* blk = blk_reparray->at(blk_id);
    // Bubble sort the main reparray:
    for (int i = 0; i < int(blk->Reparray->size()) - 2; i++)
    {
        for (int j = i + 1; j < int(blk->Reparray->size()) - 1; j++)
        {
            if (blk->Reparray->at(i).pri_id > blk->Reparray->at(j).pri_id)
            {
                Content_t<T> temp = blk->Reparray->at(i);
                blk->Reparray->at(i) = blk->Reparray->at(j);
                blk->Reparray->at(j) = temp;
            }
        }
    }
}

//
// Block methods:
template <class T> Block<T>::Block(int64_t min, int64_t max){
    num_records = 0;
    //size = D_BLOCK_SIZE;
    min_id = min;       // When first created, the range of id is determined by B+tree
    max_id = max;
    Overflow = new vector<Content_t<T>>(2);
    Reparray = new vector<Content_t<T>>(20);

    /*
    if (!if_is_overflow) {
        header.of_block_ptr = new Block<T>(true);
    } else {
        header.of_block_ptr->header.of_block_ptr = (Block<T>*) &header;
    }
    */
}

// Find the index of the given record in the block:
template <class T> int64_t Block<T>::FindIndex(int64_t id) {
    int64_t result = 0;
    // In main block:
    for (int i = 0; i < int(Reparray->size()) - 1; i++)
    {
        if (Reparray->at(i).pri_id == id) {
            return result;
        }
        result++;
    }
    // In overflow block:
    for (int i = 0; i < int(Overflow->size()) - 1; i++)
    {
        if (Overflow->at(i).pri_id == id) {
            return result;
        }
        result++;
    }
    // If the id is not in this block, return -1:
    return -1;
}

// Return a record with primary key id:
template <class T> Content_t<T> Block<T>::Retrieval(int64_t id) {
    // Find the index first:
    int64_t index = FindIndex(id);
    if (-1 == index)
    {
        cout << "Id not exist in this block!" << endl;
        return NULL;
    }
    // If it is in the overflow block:
    if (index >= 20)
    {
        return Overflow->at(index - 20);
    }
    // If it is in the main block:
    return Reparray->at(index);
}

// Insert a new record into the block:
template <class T> void Block<T>::Insert(Content_t<T> record) {
    // Check if the Reparray is full:
    if (20 <= int(Reparray->size()))
    {
        Overflow->push_back(record);        // Move to the overflow block directly
        num_records++;
        return;
    }
    // Insert into the main array:
    Reparray->push_back(record);
    num_records++;
    return;
}

// Delete a record in the block with id:
template <class T> void Block<T>::Delete(int64_t id) {
    // Find the index first:
    int64_t index = FindIndex(id);
    if (-1 == index)
    {
        cout << "Id not exist in this block!" << endl;
        return;
    }

    // If it is in the overflow block:
    if (index >= 20)
    {
        for (int i = index - 20; i < int(Overflow->size()) - 1; i++)
        {
            Overflow[i] = Overflow[i + 1];
        }
        Overflow->erase(Overflow->end() - 1);
        num_records--;
        return;
    }
    // If it is in the main block:
    for (int i = index; i < int(Reparray->size()) - 1; i++)
    {
        Reparray[i] = Reparray[i + 1];
    }
    Reparray->erase(Reparray->end() - 1);
    num_records--;
    return;
}

/*
template <class T>
class Relation{
    public:
        int64_t     Insert(T* n_tuple);
        void        Delete(int64_t  tuple_ID);
        T*          Retrieve(int64_t tuple_ID);
        void        Merging(int64_t b_id_1, int64_t b_id_2);
        void        Splitting(int64_t b_id);
        void        Sorting(int64_t b_id);

    private:
        
        vector<Block<T>>   blocks;

};
*/

/* <=== relational schema for PATIENT ===> */
class person{
    public:
        person(int64_t n_ID, int64_t n_address, int64_t n_med_id, 
                int8_t n_profession, int8_t n_age, string n_name, 
                string n_email, string n_dayborn);
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
        medical_status(int64_t n_ID, int8_t n_status);
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
        registration(int64_t n_ID, int64_t n_reg_id, int64_t n_person_id, int64_t n_treatment_id,
                    int8_t n_treatment_type, string n_deadline, string n_date, int8_t n_withdrawn, 
                    bool n_assigned, int64_t n_assigned_loc, string n_assigned_date, int8_t n_assigned_time);
        void        setID(int64_t id)               { ID = id; }
        void        setRegID(int64_t id)            { reg_id = id; }
        void        setPersonID(int64_t id)         { person_id = id; }
        void        setTreatmentID(int64_t id)      { treatment_id = id; }
        void        setDeadline(string ddl)         { deadline = ddl; }
        void        setDateOfReg(string time)       { date = time; }
        void        setWithdraw(int8_t status)      { withdrawn = status; }
        void        setAssignStatus(bool ass)       { assigned = ass; }
        void        setAssignedLoc(int64_t loc)     { assigned_loc = loc; }
        void        setAssignedTime(int8_t time)    { assigned_time = time; }
	void        setAssignedDate(string date)    { assigned_date = date; }


        int64_t     getID()                         { return ID; }
        int64_t     getRegID()                      { return reg_id; }
        int64_t     getPersonID()                   { return person_id; }
        int64_t     getTreatmentID()                { return treatment_id; }
        int8_t      getTreatmentType()              { return treatment_type; }
        string      getDeadline()                   { return deadline; }      // YY-MM-DD
        string      getDateOfReg()                  { return date; }          // YY-MM-DD
        int8_t      getWithdraw()                   { return withdrawn; }
        bool        getAssignStatus()               { return assigned; }
        int64_t     getAssignedLoc()                { return assigned_loc; }  // TODO: How can I modify those info later?? This is hard
        string      getAssignedDate()               { return assigned_date; }
        int8_t      getAssignedTime()               { return assigned_time; }
    private:
        int64_t     ID;
        int64_t     reg_id;
        int64_t     person_id;
        int64_t     treatment_id;
        int8_t      treatment_type;
        string      deadline;
        string      date;
        int8_t      withdrawn;
        bool        assigned;
        int64_t     assigned_loc;
	int8_t      assigned_time;
        string      assigned_date;
};

/* <=== relational schema for TREATMENT ===> */
class treatment{
    public:
        treatment(int64_t n_ID, int64_t n_assigned_loc, int8_t n_treatment_type, 
                string n_assigned_date, string n_end_date);
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

person::person(int64_t n_ID, int64_t n_address, int64_t n_med_id, 
                int8_t n_profession, int8_t n_age, string n_name, 
                string n_email, string n_dayborn)
                    : ID(n_ID)
                    , address(n_address)
                    , med_id(n_med_id)
                    , profession(n_profession)
                    , age(n_age)
                    , name(n_name)
                    , email(n_email)
                    , dayborn(n_dayborn)
{    
}

medical_status::medical_status(int64_t n_ID, int8_t n_status)
                    : ID(n_ID)
                    , status(n_status)
{    
}

registration::registration(int64_t n_ID, int64_t n_reg_id, int64_t n_person_id, int64_t n_treatment_id, 
                    int8_t n_treatment_type, string n_deadline, string n_date, int8_t n_withdrawn, 
                    bool n_assigned, int64_t n_assigned_loc, string n_assigned_date, int8_t n_assigned_time)
                    : ID(n_ID)
                    , reg_id(n_reg_id)
                    , person_id(n_person_id)
                    , treatment_id(n_treatment_id)
                    , deadline(n_deadline)
                    , date(n_date)
                    , withdrawn(n_withdrawn)
                    , assigned(n_assigned)
                    , assigned_loc(n_assigned_loc)
                    , assigned_date(n_assigned_date)
                    , treatment_type(n_treatment_type)
		    , assigned_time(n_assigned_time)
{
}

treatment::treatment(int64_t n_ID, int64_t n_assigned_loc, int8_t n_treatment_type, 
                    string n_assigned_date, string n_end_date)
                    : ID(n_ID)
                    , assigned_loc(n_assigned_loc)
                    , treatment_type(n_treatment_type)
                    , assigned_date(n_assigned_date)
                    , end_date(n_end_date)
{
}


#endif /* RELATION_H */
