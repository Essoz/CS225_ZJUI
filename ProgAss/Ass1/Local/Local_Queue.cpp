#include "Local_Queue.h"
#include <iostream>	
#include <math.h>
#include <time.h>
#include <ctime>
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
	l_queue = new queue<Patient*>;			// New queue
	Hashtable = new Hash_Chaining(100);		// The default length of hashtable is 100
	io = new IO;							// Add a new IO class for this stream
	id_num = 0;								// ID starts from 0
	regis_id = 0;							// This registry has id 0
	// Now deal with the year and date when the program starts:
	time_t rawtime;
	struct tm *info;
	time(&rawtime);
	info = gmtime(&rawtime);
	cur_year = 1900 + info->tm_year;					// The current year
	cur_date = info->tm_mon * 30 + info->tm_mday;		// The current date
	//cur_year = 2021;	// The current year
	//cur_date = 96;		// The current date
	counter = 0;		// The counter starts with 0
}

// Create a new patient member:
void Queue::new_patient(Risk risk, Profession prof, Age a, Information* info, int ddl)
{
	id_num++;
	int id = id_num;		// Allocate a new id number to him
	int year = cur_year;	// Set the date and year from the system
	int date = cur_date;
	int reg_id = regis_id;	// set the registry id
	Patient* patient;	// Create a new patient instance in the MEM heap
	patient = new Patient(id, risk, prof, a, info, reg_id, year, date, 0, ddl);
	// Add the patient into the local queue:
	l_queue->push(patient);
	// Add the patient into the hash table:
	Hashtable->insertion(patient);
	return;
}

// Update the information of a patient with unique id number, up_type determines what info will be changed:
void Queue::update(int id, int up_type, int info)
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
		if (info > patient->getrisk())
		{
			patient->setrisk(Risk(info));
		}
		break;
	case 1:		// Profession
		if (info > patient->getpro())
		{
		patient->setpro(Profession(info));
		}
		break;
	case 2:		// Age
		if (info > patient->getage())
		{
			patient->setage(Age(info));
		}
		break;
	case 3:		// Registration year
		if (info < patient->getyear())
		{
			patient->setyear(info);
		}
		break;
	case 4:		// Ragistration date
		if (info < patient->getdate())
		{
			patient->setdate(info);
		}
		break;
	case 5:		// Withdraw
		if (info > patient->getwithdraw())
		{
			patient->setwithdraw(info);
		}
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
	// Remember, do not forget to add this updated patient into the queue,
	// even it already exists in the queue:
	l_queue->push(patient);
	return;
}

// Update the information of a patient with unique id number, up_type determines what info will be changed:
void Queue::update_info(int id, int up_type, string info)
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
	case 0:		// Name
		patient->setname(info);
		break;
	case 1:		// Email
		patient->setemail(info);
		break;
	case 2:		// Phone
		patient->setphone(info);
		break;
	case 3:		// Birthday
		patient->setbirthday(info);
		break;
	default:
		std::cout << "The type number is invaild!" << endl;
		exit(1);
		break;
	}
	// Remember, do not forget to add this updated patient into the queue,
	// even it already exists in the queue:
	l_queue->push(patient);
	return;
}

// Report data to centralised treatment queue:
queue<Patient*>* Queue::report(queue<Patient*>* l_queue)
{
	l_queue = io->write_all(l_queue);
	// After report, increase the time counter:
	counter++;
	if (0 == counter % 2)
	{
		cur_date++;
		// Increase year when date reaches 365:
		if (cur_date >= 365)
		{
			cur_year++;
			cur_date = cur_date % 365;
		}
	}
	return l_queue;
}
