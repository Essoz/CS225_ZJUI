#ifndef CENTRAL_IO_F
#define CENTRAL_IO_F

#include "central_io.h"
// #include <string>
using namespace std;
/* READ2HEAP
 * INPUT == NULL
 * OUTPUT == NULL
 * EFFECT
 * 1. It reads registrations from files generated by local registries, convert them into fibnodes and then insert all nodes into the fibheap
 * Algorithm Description
 * While inserting, it does the following things:
 * 1. Before insert, check if the ID is in hash table of the central heap (Check *withdrawn*, *centralheap*, *assigned*), if the id is not in hashtable, directly insert this node into the heap
 * if the node is in any of the three hash table, execute helper functions corresponding to the three cases.
 * 2. 
 * 3. 




/* Modified for CA2
 * After reading a record, it first insert it into the database, then insert a node into
 * the corresponding heap 
 */
bool CentralIO::Read2Heap(){
    // read all informations that needs to be inserted into 
    ifstream infile;
    string temp_path = path + "Submit(";
    if (IO_timer < 10) {
        temp_path += to_string(IO_timer) + " ).csv";
    } else {
        temp_path += to_string(IO_timer) + ").csv";
    }
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>\n\n.... READING files from " + temp_path + "...\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    infile.open(temp_path, ifstream::in);

    // wait for information from local registries
    if (infile.eof()){
        infile.close();
        return false;
    }

    if (infile.fail()) { 
        cout << "File not found" <<endl; 
        return false;
    }
    vector<string> temp_list;
    string temp;
    string line;   
    getline(infile, line);  // remove the title of the CSV file
    while (true){
            getline(infile, line);
            
            // terminate the reading process on encountering an empty line
            if (int(line.size()) == 0) break; 
            
            // reading registrations from files generated from local registries
            for (int i = 0; i < int(line.size()); i++) {
                if (line.substr(i,1) == ",") {
                    // put this string into the vector
                    temp_list.push_back(temp);
                    // clear the temp string for the next argument
                    temp.clear();
                    continue;
                }
                if (line.substr(i,1) == "\r") {
                    break;
                }
                temp.append(line.substr(i,1));
            }
            temp_list.push_back(temp);
            temp.clear();
        // clear this list for next use

        //check hash set

        // since priority rules can be simplified, we left out the original buggy code and 
        // do far less check than before. We think being able to Insert, Delete and Retrieve 
        // shall sufficiently show our ability to manipulate index structures

        // 建好各自的relation
        // leave the assigned part empty.
        registration* Reg = new registration(stoi(temp_list.at(0)),      // ID
                                    stoi(temp_list.at(4)),          // Registry ID
                                    stoi(temp_list.at(0)), -1,      // Person ID
                                    stoi(temp_list.at(9)),          // Treatment Type
                                    temp_list.at(8),                // Deadline
                                    temp_list.at(6),                // Registration Date
                                    stoi(temp_list.at(7)),          // Withdraw state
                                    false, -1, "Not Assigned", -1);

        person* Per = new person(stoi(temp_list.at(0)), 0,               // ID
                                    stoi(temp_list.at(1)),          // Risk ID
                                    stoi(temp_list.at(2)),          // Profession
                                    stoi(temp_list.at(3)),          // Age
                                    temp_list.at(10),               // Name
                                    temp_list.at(11),               // Email
                                    temp_list.at(13));              // Date of brith
        // no need to create medical status since we only need four
        // no need to create treatment since it is what assignment does
        temp_list.clear();

        // 现在还是伪代码
        registration* node = Reg_Relation_Retrieve(Reg->getID());
        Reg->printReg();
        
        if (node && node->getID() == Reg->getID()) {
            if (node->getTreatmentID() != -1) { 
                cout << "Reg ID: " << node->getID() << " has been treated, nothing has to be done\n";
                continue; }  // has been treated, nothing has to be done
            
            
            // do an update
            // FUCK it up
            Reg_Relation_Delete(Reg->getID());
            Per_Relation_Delete(Reg->getPersonID());
            reg_withdraw.deleteID(node->getWithdraw(), node->getID());
            // TODO should add a deletion of reg_assign

            if (Reg->getWithdraw() == 1){
                if (node->getAssignStatus()){
                    assignment->removeAppointment(node);

                    cout << "Reg ID " << node->getID() << " has been withdrawn (already assigned) from type" << node->getTreatmentType() << "\n";
                } else {
                    int8_t type = Reg->getTreatmentType();
                    if (type == 0) {
                        vacc_heap->removeReg(node);
                        vacc_heap->withdrew_num++;
                    } else if (type == 1) {
                        surg_heap->removeReg(node);
                        surg_heap->withdrew_num++;
                    } else if (type == 2) {
                        regi_heap->removeReg(node);
                        regi_heap->withdrew_num++;
                    }
                    cout << "Reg ID: " << node->getID() << " has been withdrawn (Still Queueing) from type:" << type << "\n";
                    // TODO delete the node from heap, type check here!!!
                }
            } else {
                if (node->getAssignStatus()) {
                    Reg_Relation_Insert(node);
                    Per_Relation_Insert(Per);
                    cout << "Reg ID: " << node->getID() << " is already assigned, info update not supported\n";
                    continue;
                     
                }
                int8_t type = Reg->getTreatmentType();
                if (type == 0) {
                    vacc_heap->removeReg(node);
                } else if (type == 1) {
                    surg_heap->removeReg(node);
                } else if (type == 2) {
                    regi_heap->removeReg(node);
                }
                cout << "Reg ID: " << node->getID() << "'s information has been updated (type = " << (int64_t) type << ")\n";
            }
            // the node is not in out database, insert corresponding things
    }


    Reg_Relation_Insert(Reg);
    Per_Relation_Insert(Per);
    reg_assigned.put(Reg->getAssignStatus(), Reg->getID());
    
    FibNode* newnode = new FibNode(Reg);
    if (Reg->getTreatmentType() == 0){
        vacc_heap->Insert(newnode);
        if (Reg->getWithdraw() == 2) {vacc_heap->withdrew_num--;}
    } else if (Reg->getTreatmentType() == 1){
        surg_heap->Insert(newnode);
        if (Reg->getWithdraw() == 2) {surg_heap->withdrew_num--;}
    } else {
        regi_heap->Insert(newnode);
        if (Reg->getWithdraw() == 2) {regi_heap->withdrew_num--;}
    }

    }


    cout << ">>>> Read complete" << endl;
    return true;
}
/* CentralIO::Write2File
 * INPUT
 * 1. print_list -- a vector of registrations to be printed
 * 2. date       -- the date when a Write2File function is invoked (this affects the name of files)
 * 3. type       -- indicates the type of print (cured, assigned, waiting)
 * OUTPUT
 * 1. true/false -- whether the report generation has succeeded
 */

bool CentralIO::Write2File(vector<PrintInfo*> &print_list, int date, int type) {
    string filename; // = "Report_";
    // if (type == 3) {
    //     filename += "Month_" + to_string(date / 30 + 1);
    // } else {
    //     filename += "Week_" + to_string(date / 7 + 1);
    // }

    switch (type) {
        case 0:
        filename = "Report_Week_" + to_string(date / 7) + "_Cured.csv";
        break;

        case 1:
        filename = "Report_Week_" + to_string(date / 7) + "_Assigned.csv";
        break;

        case 2:
        filename = "Report_Week_" + to_string(date / 7) + "_Waiting.csv";
        break;

        case 3:
        filename = "Report_Month_" + to_string(date / 30) + ".csv";

        default:
        cout << "You are fucked at CentralIO::Write2File" << date << type << endl;
        exit(3);
    }   

    ofstream out(filename, fstream::out);
    if (!out) cout << "You are fucked" << endl;
    out << "RegistrationID,PersonID,TreatmentID,TreatmentType,Name,RiskStatus,DateOfRegistration,WaitingTime" << '\r';
    for (int i = 0; i < int(print_list.size()); i++) {
        print_list[i]->print(out);
        out << '\r';
    }
    out.close();
    return true;
}


/* TODO <=== Helper Function for Generating Reports ===> */
bool CentralIO::ReportWeekly(int week, int key){
    /* Generate Weekly Report for 
     * 1. People who have been treated including their profession, age category, risk status, and the waiting time from registration to treatment
     * 2. the registered people with a set appointment including their profession category, age category, risk status and their waiting time until now
     * 3. the queueing people without a set appointment including their profession category, age category, risk status and their waiting time until now
     */
    _WeeklyCured(week, key - '0');
    _WeeklyAssigned(week, key - '0');
    _WeeklyQueueing(week, key - '0');
    return true;
}




bool CentralIO::ReportMonthly(int month, int key){
    _Monthly(month, key - '0');
    return true;
}


/*
 * INPUT
 * OUTPUT
 * 1. Whether the report generation has succeed or not
 * EFFECT
 *      This function will take all information to be printed 
 *      from *assignment->all_locations->cured_list*. And call 
 *      CentralIO::sortByKey() to sort the vector w.r.t the order 
 *      given.
 */
bool CentralIO::_WeeklyCured(int week, int key){
    // copy the list to be printed 
    vector<treatment*> tre_list = Tre_Relation_Retrieve_2(week - 1);
    vector<PrintInfo*>* print_list = new vector<PrintInfo*>;
    PrintInfo* temp_ptr;
    int count = tre_list.size();
    for (int i = 0; i < count; i++)
    {
        temp_ptr = new PrintInfo(Reg_Relation_Retrieve(tre_list[i]->getRegID()), IO_timer);
        print_list->push_back(temp_ptr);
    }
    sortByKey(*print_list, key);
    // generate report using print_list (sorted)
    if (Write2File(*print_list, week * 7, 0) == false) exit(3);

    cout << "\nWeek " << week << "'s report (Cured patients ordered W.R.T key "<< key;
    cout << ") has been generated" << endl;
    return true;
}
bool CentralIO::_WeeklyAssigned(int week, int key){
    vector<PrintInfo*>* print_list;
    vector<registration*> reg_list = Reg_Relation_Retrieve_3(1);

    PrintInfo* temp_ptr;
    int count = reg_list.size();
    for (int i = 0; i < count; i++)
    {
        temp_ptr = new PrintInfo(reg_list[i], IO_timer);
        print_list->push_back(temp_ptr);
    }
    sortByKey(*print_list, key);
    if (Write2File(*print_list, week * 7, 1) == false) exit(3);

    
    cout << "\nWeek " << week << "'s report (Assigned patients ordered W.R.T key "<< key;
    cout << ") has been generated" << endl;
    return true;

    return true;
}


bool CentralIO::_WeeklyQueueing(int week, int key){
    vector<PrintInfo*>* print_list;
    vector<registration*> reg_list = Reg_Relation_Retrieve_2(0);
    vector<registration*> reg_list_2 = Reg_Relation_Retrieve_2(2);
    reg_list.insert(reg_list.end(), reg_list_2.begin(), reg_list_2.end());

    PrintInfo* temp_ptr;
    int count = reg_list.size();
    for (int i = 0; i < count; i++)
    {
        temp_ptr = new PrintInfo(reg_list[i], IO_timer);
        print_list->push_back(temp_ptr);
    }
    sortByKey(*print_list, key);

    if (Write2File(*print_list, week * 7, 2) == false) exit(3);

    cout << "\nWeek " << week << "'s report (Queueing patients ordered W.R.T key "<< key;
    cout << ") has been generated" << endl;
    return true;
}


bool CentralIO::_Monthly(int month, int key){
    
    string filename = "MonthlyStat_";
    filename += to_string(month) + ".md";

    ofstream out(filename, fstream::out);
    out << "# Central Queueing System Monthly Statistic Report | 2021, Month " << month << endl;
    
    out << "### Number of Waiting People" << endl;
    out << vacc_heap->GetNum() + surg_heap->GetNum() + regi_heap->GetNum() << "  "<< endl;

    

    out << "### Number of Treated People Per Month" << endl;
    // int num_treated = 0;
    // for (int i = 0; i < int(assignment->all_locations->cured_list.size()); i++) {
    //     num_treated += assignment->all_locations->cured_list;
    // }
    int cured_nums = assignment->all_locations->cured_list[month*4 - 4].size() 
                   + assignment->all_locations->cured_list[month*4 - 3].size()
                   + assignment->all_locations->cured_list[month*4 - 2].size() 
                   + assignment->all_locations->cured_list[month*4 - 1].size();
    out << cured_nums << "  " << endl;

    out << "### Average Waiting Time" << endl;
    int avg_time = 0;
    for (int k = 0; k < 4; k++){
        for (int i = 0; i < assignment->all_locations->cured_list[month*4 - k].size(); i++) {
            registration* Reg = Reg_Relation_Retrieve(assignment->all_locations->cured_list[month*4 - k][i]->getRegID());
            avg_time += stoi(Reg->getAssignedDate()) - stoi(Reg->getDateOfReg());
        }
    }
    avg_time /= cured_nums;

    out << avg_time << "days  " << endl;
    ;

    out << "### Number of People who withdrew their registration" << endl;
    out << vacc_heap->withdrew_num + surg_heap->withdrew_num + regi_heap->withdrew_num << "  " << endl;

    out.close();
    cout << "\nMonth " << month << "'s report has been generated." << endl;
    
    return true;
}

/*
 * OUTPUT
 * 1. 0 (a >= b)
 * 2. 1 (a <  b)
 */
bool CentralIO::compare(PrintInfo* a, PrintInfo* b, int key)
{
    person* Per1 = Per_Relation_Retrieve(a->per_id);
    person* Per2 = Per_Relation_Retrieve(b->per_id);

    if (key == 0) {
        return (Per1->getName() < Per2->getName());
    } 
    if (key == 1) {
        return (Per1->getProfession() < Per2->getProfession());
    }
    if (key == 2) {
        return (Per1->getAge() < Per2->getAge());
    }
    return false;
}

void CentralIO::sortByKey(vector<PrintInfo*>& info_list,int key)
{
    PrintInfo* temp;
    for (int i = 0; i < int(info_list.size())-1; i++)
    {
        for (int j = 0; j < int(info_list.size())-1-i; j++)
        {
            if (!this->compare(info_list[j], info_list[j+1], key))
            {
                temp = info_list[j];
                info_list[j] = info_list[j+1];
                info_list[j+1] = temp;
            }
        }
    }
}

#endif