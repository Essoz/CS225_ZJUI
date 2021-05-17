#ifndef Local_IO_h
#define Local_IO_h
#include "Local_Queue.h"
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

/*
 *	File: Local_IO.h
 * 
 *	Writter: Tianyu Zhang
 * 
 *  Description:
 *	This header file declares all the functions related to I/O for local registry.
 *	Details are listed above each function.
 */
class Queue;

class IO
{
	friend class Queue;
public:
/*  Description:
 *      This function will write all the information of updated patients from the
 *      local registry queue into a csv file named update.csv. One person per line.
 *  Inputs:
 *      queue: The pointer of local registry queue
 *  Outputs:
 *      None
 *  Return value:
 *		The pointer of local registry queue (should be NULL after writting to the file)
 *  Side Effects:
 *      Write a csv file containing all the information of patients.
 */
	static queue<Patient*>* write_all(queue<Patient*>* queue);

/*  Description:
 *      This function will read all the information of new patients in a
 *      seperated csv file and store them in the MEM heap.
 *  Inputs:
 *      csv: The seperated csv file to read
 *		queue: The pointer of the class Queue
 *  Outputs:
 *		None
 *	Return value:
 *      The pointer of the new registry queue
 *  Side Effects:
 *      Read a csv file containing all the information of new patients.
 */
	static queue<Patient*>* read_all(string path, Queue* queue);

// This new added function is used to read the updated info and update the queue:
	static queue<Patient*>* read_update(string path, Queue* queue);

//ɾ���ַ����пո��Ʊ���tab����Ч�ַ�
	static string Trim(string& str);
};

#endif /* Local_IO_h */
