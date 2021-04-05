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

#include "../fibheap.h"
#include "central_io_f.h"
// #include ""
// #include ""
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <vector>
using namespace std;


// TODO: ADD this class as a friend class of FibHeap
template<T> class CentralIO{
    public:
        CentralIO(FibHeap<T>* heap);
        bool Read2Heap();   // This function reads registration information from files generated by local registries, the return value implies whether the operation succeeds
        bool ReportWeekly(int key);
        bool ReportMonthly(int key);


    private:
        FibHeap<T>* heap;   // This variable set the heap on which this IO instance operates.
        vector<vector<int>> register_arr;
        bool _WeeklyCured();
        bool _WeeklyAssigned();
        bool _WeeklyQueueing();
        bool _Monthly();

}

template<class T> CentralIO<T>::CentralIO(FibHeap<T>* heap){
    CentralIO::heap = heap;
}


int main(){
    vector<vector<int>> user_arr;
    ifstream fp("xxx/user_data.csv"); //定义声明一个ifstream对象，指定文件路径
    string line;
    getline(fp,line); //跳过列名，第一行不做处理
    while (getline(fp,line)){ //循环读取每行数据
        vector<int> data_line;
        string number;
        istringstream readstr(line); //string数据流化
        //将一行数据按'，'分割
        for(int j = 0;j < 11;j++){ //可根据数据的实际情况取循环获取
            getline(readstr,number,','); //循环读取数据
            data_line.push_back(atoi(number.c_str())); //字符串传int
        }
        user_arr.push_back(data_line); //插入到vector中
    }
    return 0;
}



#endif