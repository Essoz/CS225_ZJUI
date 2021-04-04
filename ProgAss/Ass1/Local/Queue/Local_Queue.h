#ifndef Local_Queue_h
#define Local_Queue_h
#include "Patient.h"
#include "Local_IO.h"
#include "hash.h"
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
 *	The permanent storage of info of patients is listed in the heap, which is pointed by 
 *	the vector described above. After some time, the info in the heap will be written into
 *	a separated csv file called "local_data.csv".
 * 
 *	The procedure of the local registry looks like this:
 *	1. In the main function, several new patients register in the local registry and some
 *		patients update their personal info. Any operation on the information will be 
 *		recorded in the local queue.
 *	2. If the patient is newly registered, create a new structure and store it into both the heap
 *		and the local queue.
 *		If the patient has already registered, use the hash table and id to change the info 
 *		in the heap and copy one to the local queue (just pointer).
 *	3. When it is ready to upload the updated info to the centralised treatment queue, use the 
 *		local queue to output a csv file, then send this to the center.
 */

class Queue
{
public:
	Queue();
	//~Queue();

private:
	std::queue<Patient*> l_queue;		// The local queue
	std::vector<Patient*> Hashtable;	// The hash table
};

// Default constructor:
Queue::Queue()
{
	l_queue = new queue<Patient*>;
	Hashtable = new vector<Patient*>;
}

#endif /* Local_Queue_h */
