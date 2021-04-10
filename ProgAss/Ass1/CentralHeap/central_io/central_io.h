/* CENTRAL_IO_H
 * 
 * author: Yuxuan Jiang | CS225 Group10
 * 
 * Description:
 * This file defines the IO haviour of the central heap 
 * 1. for receiving registrations from local registries.
 * 2. for report generating 
 * 
 */
#ifndef CENTRAL_IO_H
#define CENTRAL_IO_H
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include "../fibheap.h"
using namespace std;

// TODO: ADD this class as a friend class of FibHeap
class CentralIO{
    public:
        CentralIO(FibHeap* heap, string path);
        bool Read2Heap();   // This function reads registration information from files generated by local registries, the return value implies whether the operation succeeds
        bool ReportWeekly(int week,int key);
        bool ReportMonthly(int month, int key);
        bool compare(FibNode* a, FibNode* b, int key);
        void sortByKey(vector<FibNode*>&fiblist,int key);       //TODO sortbykey
        bool Write2File(string path);

    private:
        FibHeap* heap;   // This variable set the heap on which this IO instance operates.
        string path;
        // vector<vector> register_arr;
        bool _WeeklyCured(int week, int key);
        bool _WeeklyAssigned(int week, int key);
        bool _WeeklyQueueing(int week, int key);
        bool _Monthly(int month, int key);

};


#endif