#include "Local_Queue.h"
#include "Local_IO.h"
#include <iostream>	
#include <math.h>
#include <cstdlib>
#include <map>
#include <queue>
#include <vector>
using namespace std;
using std::cout;
using std::cin;

/*
 *	File: Local_Queue.cpp
 * 
 *	Writter: Tianyu Zhang
 * 
 *	Description: The function definition for Local_Queue.h
 */

// Default constructor:
Queue::Queue()
{
	l_queue = new queue<Patient*>;
	Hashtable = new Hash_Chaining(100);		// The default length of hashtable is 100
	id_num = 0;
}

// Create a new patient member:
void Queue::new_patient(Risk risk, Profession prof, Information info, int date, int time, int ddl)
{
	id_num++;
	int id = id_num;	// Allocate a new id number to him
	Patient* patient;	// Create a new patient instance in the MEM heap
	patient = new Patient(id, risk, prof, info, date, time, ddl);
	// Add the patient into the local queue:
	l_queue->push(patient);
	// Add the patient into the hash table:
	Hashtable->insertion(patient);
}

// Update the information of a patient with unique id number, up_type determines what info will be changed:
void Queue::update(int id, int up_type, auto info)
{
	Patient* patient;
	// First, find the pointer to the patient instance:
	patient = Hashtable->retrieval(id);
	if (NULL == patient)
	{
		std::cout << "Id number " << id << " is invaild!" << endl;
		exit(1);
	}
	// Next, determine what type of info you want to change:
	switch (up_type)
	{
	case 0:		// Risk
		patient->setrisk(info);
		break;
	case 1:		// Profession
		patient->setprof(info);
		break;
	case 2:		// Information
		patient->setinfo(info);
		break;
	case 3:		// Registration date
		patient->setdate(info);
		break;
	case 4:		// Ragistration time
		patient->settime(info);
		break;
	case 5:		// Withdraw
		patient->setwithdraw(info);
		break;
	case 6:		// Letter_ddl
		patient->setddl(info);
		break;
	default:
		std::cout << "The type number is invaild!" << endl;
		exit(1);
		break;
	}
	// Calculate the updated priority number:
	patient->calculate_prio();
	// Remember, do not forget to add this updated patient into the queue:
	l_queue->push(patient);
	return;
}

// Report data to centralised treatment queue:
queue<Patient*>* Queue::report(queue<Patient*>* l_queue)
{
	l_queue = IO::write_all(l_queue);
	return l_queue;
}
