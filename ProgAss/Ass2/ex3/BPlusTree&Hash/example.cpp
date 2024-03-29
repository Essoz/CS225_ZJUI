#include <iostream>
#include <cstring>

#include "BPlusTree.h"
#include "hashtable.hpp"
using namespace std;

//Example struct. Can use any type of
//struct or primitive as the data
//being stored
struct patient_t{
	int ID;
//	patient* pointer;//这里记着改成实际dataset里面pointer类型
};

typedef struct patient_t patient;
int main()
{
	//Creates a B+ Tree with the following parameters:
	//	The primary key is an integer
	//		Note: Currently, primary key must have
	//		comparison operators defined
	//	The B+ Tree stores student structs
	//	Each node is aligned to 4096 byte (4 KiB) blocks
	BP<int, patient*> patient_bptree(4096); 
	
	patient* cur_patient;
	/*initializing the B+ tree, the key is the ID of the student, and the information stored in the B+ tree
	* is the structure of student, which contain the name and GPA
	*/
	for(int i = 1000; i > 0; i--){
		cur_patient = new patient();
		cur_patient->ID=i;
		//cur_patient->pointer=;//这里让这个struct的pointer 和dataset里面的指向某个病人的pointer相等，就完成初始化了
		//Pass item to insert
		patient_bptree.insert(i, cur_patient);
	}
	if(patient_bptree.retrieve(1, cur_patient)){
		cout << "=======" << endl;
		cout << "ID: Min" << endl;
		cout << "=======" << endl;
		cout << "Patient ID: " << cur_patient->ID << endl;
		//cout << "Patient pointer in data set " << cur_patient->pointer->name << endl << endl;//想要什么就往里面加，这里是name
	}
	if(patient_bptree.retrieve(1000, cur_patient)){
		cout << "=======" << endl;
		cout << "ID: Max" << endl;
		cout << "=======" << endl;
		cout << "Patient ID: " << cur_patient->ID << endl;
		//cout << "Patient pointer in data set " << cur_patient->pointer << endl << endl;
	}
	if(patient_bptree.retrieve(42, cur_patient)){
		cout << "=======" << endl;
		cout << "ID: 42" << endl;
		cout << "=======" << endl;
		cout << "Patient ID: " << cur_patient->ID << endl;
		//cout << "Patient pointer in data set " << cur_patient->pointer << endl << endl;
	}
	//Remove the remaining entries
	//(Remove() calls free)
	/*for(int i = 0; i < 1001; i++){
		if(patient_bptree.remove(i, cur_patient))
			delete cur_patient;
	}
	*/
	hashtable<int, int> ht;
    ht.put(1,80);//这里这个第一项就是四种second key，你随便加，然后第二项是id，put是往hash里面填东西的函数
	ht.put(1,90);
	vector<int> result_id;
	vector<int> result_id1;
	ht.get(1,result_id);
	cout<<"vector capacity:"<<endl;
	cout<<result_id.capacity()<<endl;
	cout<<"vector element:"<<endl;
	cout<<result_id.at(0)<<endl;
	cout<<result_id.at(1)<<endl;
	ht.put(2,1);
	ht.get(2,result_id1);
	cout<<"vector capacity:"<<endl;
	cout<<result_id1.capacity()<<endl;
	ht.deleteID(1,90);
	ht.deleteID(1,80);
	vector<int> result_id2;
	ht.get(1,result_id2);
	cout<<result_id2.capacity()<<endl;
	return 0;
}
//这个hash存起来的都是id，所以返回的也是id，然后如果想从data set找东西，就用hash回来的id过一遍b加树去找pointer