#ifndef Local_IO_h
#define Local_IO_h
#include "Patient.h"
#include <queue>
#include <vector>
using namespace std;

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
std::queue<Patient*>* write_all(std::queue<Patient*>* queue);

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
std::queue<Patient*>* write_one(std::queue<Patient*>* queue);

/*  Description:
 *      This function will read all the information of updated patients in a
 *      seperated scv file and replace the updated information stored in the registry queue.
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
std::queue<Patient*>* read_all(FILE* csv, std::queue<Patient*>* queue);

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
std::queue<Patient*>* read_one(FILE* csv, std::queue<Patient*>* queue);

#endif /* Local_IO_h */
