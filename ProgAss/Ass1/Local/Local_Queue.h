#ifndef Local_Queue_h
#define Local_Queue_h
#include "Patient.h"
#include "Local_hash.h"
#include "Local_IO.h"
#include <queue>
#include <vector>
using namespace std;

/* 
 *	File: Local_Queue.h
 *
 *	Writter: Tianyu Zhang
 * 
 *	Description:
 *	This header file defines two things in the local registry:
 *	1. The local queue (each entry is a structure of patient) in the registry to 
 *		temporarily store the updated patients' information.
 *	2. Another class (hash table) to store the pointers to all the info of patients, 
 *		note that the key of each patient is the id number.
 * 
 *	The permenant storage of info of patients is listed in the heap, which is pointed by 
 *	the vector described above. After some time, the info in the heap will be written into
 *	a seperated csv file called "local_data.csv".
 * 
 *	The procedure of the local registry looks like this:
 *	1. In the main function, several new patients register in the local registry and some
 *		patients update their personal info. Any operation on the information will be 
 *		recorded in the local queue.
 *	2. If the patient is newly registered, create a new structure and store it into both the heap
 *		and the local queue.
 *		If the petient has already registered, use the hash table and id to change the info 
 *		in the heap and copy one to the local queue (just pointer).
 *	3. When it is ready to upload the updated info to the centralised treatment queue, use the 
 *		local queue to output a csv file, then send this to the center.
 */
class IO;
class Hash_Chaining;

class Queue
{
public:
	Queue();	// Default constructor for empty queue and empty IO stream class.
	// Create a new patient member:
	void new_patient(Risk risk, Profession prof, Age a, Information* info, int ddl);
	// Update the information of a patient with unique id number, up_type determines what info will be changed:
	void update(int id, int up_type, int info);
	void update_info(int id, int up_type, string info);		// Only for information
	// Report data to centralised treatment queue:
	queue<Patient*>* report(queue<Patient*>* l_queue);
	// Get io pointer:
	IO* getio(){
		return io;
	}
	// Get local queue pointer:
	queue<Patient*>* getl_queue(){
		return l_queue;
	}
	// Get hashtable:
	Hash_Chaining* getHashtable() {
		return Hashtable;
	}
	// Set local queue pointer:
	void setl_queue(queue<Patient*>* queue){
		l_queue = queue;
	}

private:
	IO* io;							// The IO class for this queue
	queue<Patient*>* l_queue;		// The local queue
	Hash_Chaining* Hashtable;		// The hash table
	// This file scope variable track the id number so that no two patients have the same id number.
	//static int id_num;
	int id_num;
	// This static variable represents the local registry id:
	int regis_id;
	// These two static variables are used to represent current date and year.
	//static int cur_year;
	//static int cur_date;
	//static int counter;				// Used to increase the date and year, even number means one day passed
	int cur_year;
	int cur_date;
	int counter;
};

#endif /* Local_Queue_h */
