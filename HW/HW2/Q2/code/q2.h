/*
 * @ Author     : 
 * Group-10 Yuxuan Jiang
 * @ File       : 
 * q2.cpp
 * @ Purpose    : 
 * 
 * @ Usage      : 
 * 
 * @ Description: 
 * 
 * @ Input      : 
 * 
 * @ Output     : 
 * 
 */

#include <vector>
#include <iostream>
using namespace std;



class booking{
    public:
        booking(int a, int d){
            arrival = a;
            departure = d;
        };
        int arrival; 
        int departure; 
};


class Bookings{
    public:
        Bookings(vector<booking> bookings, int K){
            bks = bookings;
            k = K;
        };
        vector <booking> bks;
        int k;
        void bookings_print();
        void test();
        
        // Modify the following to solve the exercise
        // You may also add your own help function
        bool checkdemands();

        // the following two functions returns the maximal and minimal arrival/departure dates
        int* maxkeys();
        int* minkeys(); 


    private:

};



// You should right the following to finish the exercise
// You may also add your own help function
bool Bookings::checkdemands(){
    int C = 0;         //initialize the counter
    int* maxkey = maxkeys();
    int* minkey = minkeys();
    int n_bucket = maxkey[1] - minkey[0];
    int* arr = new int[n_bucket];
    int* dep = new int[n_bucket];
    
    //initialize the two arrays to zero
    for (int i = 0; i < n_bucket; i++){
        arr[i] = 0;
        dep[i] = 0;
    }
    
    for (int i = 0; i < (int)bks.size(); i++){
        arr[bks[i].arrival - minkey[0]]++;
        dep[bks[i].departure - minkey[0]]++; 
    }

    for (int i = 0; i < n_bucket; i++){
        C = C + arr[i] - dep[i];
        if (C > k){
            // cout <<"\nC is :"<< C << '\n';
            // cout <<"\ni is :"<< i << '\n';
            // cout <<"k is :"<< k << '\n';
        return false;
        }
    }
    

    return true;
    

};
void Bookings::test(){
    bookings_print();
    cout << "Check whether satisfy the demands: " << (checkdemands()? "Success":"Fail") << endl;
};

int* Bookings::maxkeys(){
    int* maxkey = new int[2]{0,0};
    int i;
    for (i = 0; i < (int)bks.size(); i++){ //note that we can only increment i here
        if (maxkey[0] < bks[i].arrival){
            maxkey[0] = bks[i].arrival;
        }
        if (maxkey[1] < bks[i].departure){
            maxkey[1] = bks[i].departure;
        }
    }
    return maxkey;
};

int* Bookings::minkeys(){
    int* minkey = new int[2]{0,0};
    int i;
    for (i = 0; i < (int)bks.size(); i++){ //note that we can only increment i here
        if (minkey[0] > bks[i].arrival){
            minkey[0] = bks[i].arrival;
        }
        if (minkey[1] > bks[i].departure){
            minkey[1] = bks[i].departure;
        }
    }
    return minkey;
};
// DO NOT modify the following 
void Bookings::bookings_print(){
    cout << "Bookings as follow:" << endl;
    for(booking i: this->bks){
        cout << "A: " << i.arrival << "  | D: " << i.departure << endl;
    }
    cout << "Max available room:" << this->k << endl;
    return ;
}


