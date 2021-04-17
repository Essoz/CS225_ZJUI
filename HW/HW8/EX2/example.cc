#include <iostream>
#include <cstring>

#include "BPlusTree.h"

using namespace std;

//Example struct. Can use any type of
//struct or primitive as the data
//being stored
struct student_t{
	char name[50];
	float gpa;
};

typedef struct student_t student;

char names[10][50] = {
	"Bender Rodrigez",
	"Philip J. Fry",
	"Turanga Leela",
	"Hubert J. Farnsworth",
	"Amy Wong",
	"Hermes Conrad",
	"Scruffy",
	"Nibbler",
	"Slurms McKenzie",
	"Zoidberg"	
};


int main()
{
	//Creates a B+ Tree with the following parameters:
	//	The primary key is an integer
	//		Note: Currently, primary key must have
	//		comparison operators defined
	//	The B+ Tree stores student structs
	//	Each node is aligned to 4096 byte (4 KiB) blocks
	BTree<int, student*> student_tree(4096); 
	
	student *cur_student;
	/*initializing the B+ tree, the key is the ID of the student, and the information stored in the B+ tree
	* is the structure of student, which contain the name and GPA
	*/
	for(int i = 1000; i > 0; i--){
		
		cur_student = new student();
		strcpy(cur_student->name, names[i%10]);
		cur_student->gpa = (i % 3) + 1 + (i % 2 ? 1 : .5); 
		
		//Pass item to insert
		student_tree.insert(i, cur_student);
	}
	/*below is the test example for the B+ tree
	//Retrieve student with primary key of 42
	if(student_tree.retrieve(42, cur_student)){;
		cout << "=======" << endl;
		cout << "ID: 42" << endl;
		cout << "=======" << endl;
		cout << "Student Name: " << cur_student->name << endl;
		cout << "GPA: " << cur_student->gpa << endl << endl;
	}

	//Retrieve student with primary key of 200
	if(student_tree.retrieve(200, cur_student)){
		cout << "=======" << endl;	
		cout << "ID: 200" << endl;
		cout << "=======" << endl;
		cout << "Student Name: " << cur_student->name << endl;
		cout << "GPA: " << cur_student->gpa << endl;
	}

	//Remove entry with primary key of 2
	if(student_tree.remove(2, cur_student)){
		delete cur_student;
		cout << "Successfully removed student with ID 2" << endl;
	}
	*/
	
	/*below is the implement of EX2 Q2
	*in order to find the minmum and maximum in the B+ tree*/
	

	//Remove the remaining entries
	//(Remove() calls free)
	for(int i = 0; i < 1001; i++){
		if(student_tree.remove(i, cur_student))
			delete cur_student;
	}

	return 0;
}
