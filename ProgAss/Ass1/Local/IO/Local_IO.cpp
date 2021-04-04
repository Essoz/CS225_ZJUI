#include "Local_IO.h"
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <queue>
using namespace std;
using std::cout;
using std::cin;

/*  Description:
 *      This function will write all the information of updated patients from the
 *      local registry queue into a csv file named update.csv. One person per line.
 *  Inputs:
 *      queue: The pointer of local registry queue
 *  Outputs:
 *      None
 *  Return value:
 *		The pointer of local registry queue
 *  Side Effects:
 *      Write a csv file containing all the information of patients.
 */
queue<Patient*>* IO::write_all(queue<Patient*>* queue)
{
	// open the file you want to write:
	FILE* update;
	update = fopen("update.csv", "w");
	// check if fopen successes:
	if (NULL == update)
	{
		std::cout << "The file to write cannot open!" << endl;
		exit(1);
	}
	// Loop all the patients in the local registry queue and write all the 
	// information into the update.csv:
	while (0 == queue->empty())
	{
		fprintf(update, "%d,%d,%d,%d,%d,",
			queue->front()->getid(), queue->front()->getrisk(), queue->front()->getprof(),
			queue->front()->getdate(), queue->front()->gettime());
		fprintf(update, "%s,%s,%d,%d,", queue->front()->getinfo()->name,
			queue->front()->getinfo()->email, queue->front()->getinfo()->phone,
			queue->front()->getinfo()->birthday);
		fprintf(update, "%d,%d,%d,", queue->front()->getwithdraw(), queue->front()->getddl(),
			queue->front()->getpriority());
		fprintf(update, "%s,%d,%d\n", queue->front()->getappoint()->location,
			queue->front()->getappoint()->date, queue->front()->getappoint()->time);

		// delete the first entry in the queue:
		queue->pop();
	}
	// In the end, we close the file to finish writting:
	int check = fclose(update);
	// Check if the file is successfully closed:
	if (0 == check)
	{
		cout << "Failed to close the update.csv." << endl;
		exit(1);
	}
	return queue;
}

/*  Description:
 *      This function will write information of one patient from the
 *      local registry queue into a csv file named update.csv.
 *  Inputs:
 *      queue: The pointer of local registry queue
 *  Outputs:
 *      None
 *  Return value:
 *		None
 *  Side Effects:
 *      Write a csv file containing the information of one patient.
 */
//std::queue<person_t*>* write_one(std::queue<person_t*>* queue)

/*  Description:
 *      This function will read all the information of updated patients in a
 *      seperated scv file and store them into the registry queue.
 *  Inputs:
 *      csv: The seperated scv file to read
 *		queue: The pointer of the current registry queue
 *  Outputs:
 *		None
 *	Return value:
 *      The pointer of the new registry queue
 *  Side Effects:
 *      Read a csv file containing all the information of patients.
 */
//std::queue<person_t*>* read_all(FILE* csv, std::queue<person_t*>* queue)

/*  Description:
 *      This function will write information of one patient in the
 *      local registry queue into a csv file named local.csv.
 *  Inputs:
 *      queue: The local registry queue
 *  Outputs:
 *		None
 *	Return value:
 *      The pointer of the new registry queue
 *  Side Effects:
 *      Write a csv file containing the information of one patient.
 */
//std::queue<person_t*>* read_one(FILE* csv, std::queue<person_t*>* queue)
