#include <iostream>
#include <cstring>

#include "BPlusTree.h"

using namespace std;

//Example struct. Can use any type of
//struct or primitive as the data
//being stored
struct patient_t{
	int ID;
//  patient* pointer
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
	BTree<int, patient*> patient_bptree(4096); 
	
	patient *cur_patient;
	/*initializing the B+ tree, the key is the ID of the student, and the information stored in the B+ tree
	* is the structure of student, which contain the name and GPA
	*/
	for(int i = 1000; i > 0; i--){
		cur_patient = new patient();
		cur_patient->ID=i;
		//Pass item to insert
		patient_bptree.insert(i, cur_patient);
	}
	if(patient_bptree.retrieve(1, cur_patient)){;
		cout << "=======" << endl;
		cout << "ID: Min" << endl;
		cout << "=======" << endl;
		cout << "Patient ID: " << cur_patient->ID << endl;
		//cout << "Patient pointer in data set " << cur_patient->pointer << endl << endl;
	}
	if(patient_bptree.retrieve(1000, cur_patient)){;
		cout << "=======" << endl;
		cout << "ID: Min" << endl;
		cout << "=======" << endl;
		cout << "Patient ID: " << cur_patient->ID << endl;
		//cout << "Patient pointer in data set " << cur_patient->pointer << endl << endl;
	}
	if(patient_bptree.retrieve(42, cur_patient)){;
		cout << "=======" << endl;
		cout << "ID: Min" << endl;
		cout << "=======" << endl;
		cout << "Patient ID: " << cur_patient->ID << endl;
		//cout << "Patient pointer in data set " << cur_patient->pointer << endl << endl;
	}
	//Remove the remaining entries
	//(Remove() calls free)
	for(int i = 0; i < 1001; i++){
		if(patient_bptree.remove(i, cur_patient))
			delete cur_patient;
	}

	return 0;
}
