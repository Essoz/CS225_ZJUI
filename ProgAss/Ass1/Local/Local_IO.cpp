#include "Local_IO.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <vector>
#include <string>
using namespace std;
using std::cout;
using std::cin;

/*
 *	File: Local_IO.cpp
 * 
 *	Writter: Tianyu Zhang
 * 
 *	Description: This file contains all function definitions for Local_IO.h.
 */

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
queue<Patient*>* IO::write_all(queue<Patient*>* queue)
{
	// open the file you want to write:
	FILE* update;
	update = fopen("Submit.csv", "w");
	// check if fopen successes:
	if (NULL == update)
	{
		std::cout << "The file to write cannot open!" << endl;
		exit(1);
	}
	// Write the header of the output file first:
	fprintf(update, "ID,Risk_Status,Profession,Age,Reg_ID,Reg_Year,Reg_Date,Withdraw,Letter_DDL,Priority,");
	fprintf(update, "Name,Email,Phone,Birthday\n");

	// Loop all the patients in the local registry queue and write all the 
	// information into the update.csv:
	while (0 == queue->empty())
	{
		fprintf(update, "%d,%d,%d,",
			queue->front()->getid(), queue->front()->getrisk(), queue->front()->getpro());
		fprintf(update, "%d,%d,%d,%d,",
			queue->front()->getage(), queue->front()->getreg_id(),
			queue->front()->getyear(), queue->front()->getdate());
		// We need to deal with the withdraw status seperately:
		if (3 == queue->front()->getactivated() && 0 < queue->front()->getwithdraw() && 0 < queue->front()->getre_reg())
		{	// Need to pop three times:
			fprintf(update, "0,");
			queue->front()->setactivated(queue->front()->getactivated() - 1);
		}
		else if (2 == queue->front()->getactivated()) 
		{	// Need to pop two times:
			if (0 < queue->front()->getwithdraw() && 0 < queue->front()->getre_reg())
			{	// Withdraw + Re_reg:
				fprintf(update, "1,");
				queue->front()->setwithdraw(0);
			}
			else if (0 < queue->front()->getwithdraw() && 0 == queue->front()->getre_reg())
			{	// Reg + Withdraw:
				fprintf(update, "0,");
			}
			else
			{
				std::cout << "Invalid Logic!" << std::endl;
				exit(1);
			}
			queue->front()->setactivated(queue->front()->getactivated() - 1);
		}
		else if (1 == queue->front()->getactivated())
		{	// Need to pop one time:
			if (0 == queue->front()->getwithdraw() && 0 == queue->front()->getre_reg())
			{	// Only for Reg:
				fprintf(update, "0,");
			}
			else if (0 < queue->front()->getwithdraw() && 0 == queue->front()->getre_reg())
			{	// Only for Withdraw:
				fprintf(update, "1,");
			}
			else if (0 == queue->front()->getwithdraw() && 0 < queue->front()->getre_reg())
			{	// Only for Re_reg:
				fprintf(update, "2,");
			}
			else
			{
				std::cout << "Invalid Logic!" << std::endl;
				exit(1);
			}
			queue->front()->setactivated(queue->front()->getactivated() - 1);
		}
		else
		{	// We do not have updates w.r.t withdraw status:
			if (0 == queue->front()->getwithdraw() && 0 == queue->front()->getre_reg())
			{	// Reg:
				fprintf(update, "0,");
			}
			else if (0 < queue->front()->getwithdraw() && 0 == queue->front()->getre_reg())
			{	// Withdraw:
				fprintf(update, "1,");
			}
			else if (0 == queue->front()->getwithdraw() && 0 < queue->front()->getre_reg())
			{	// Re_reg:
				fprintf(update, "2,");
			}
			else
			{
				std::cout << "Invalid Logic!" << std::endl;
				exit(1);
			}
		}
		
		fprintf(update, "%d,%d,", queue->front()->getddl(),queue->front()->getpriority());
		fprintf(update, "%s,%s,%s,%s\n", 
			queue->front()->getinfo()->name.c_str(), queue->front()->getinfo()->email.c_str(), 
			queue->front()->getinfo()->phone.c_str(), queue->front()->getinfo()->birthday.c_str());
		// delete the first entry in the queue:
		queue->pop();
	}
	// In the end, we close the file to finish writting:
	int check = fclose(update);
	// Check if the file is successfully closed:
	if (0 == check)
	{
		//cout << "Failed to close the update.csv." << endl;
		//exit(1);
	}
	return queue;
}

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
queue<Patient*>* IO::read_all(string path, Queue* queue)
{
	ifstream fin(path);		// open the stream
	string line;
	getline(fin, line);		// Skip the header line
	while (getline(fin, line))		// ���ж�ȡ�����з���\n�����֣������ļ�β��־eof��ֹ��ȡ
	{
		istringstream sin(line);	// �������ַ���line���뵽�ַ�����istringstream��
		vector<string> fields;		// ����һ���ַ�������
		string field;
		while (getline(sin, field, ','))	// ���ַ�����sin�е��ַ����뵽field�ַ����У��Զ���Ϊ�ָ���
		{
			fields.push_back(field);		// ���ոն�ȡ���ַ������ӵ�����fields��
		}
		// Now we can declare several variables and create new patients:
		Risk risk = Risk(atoi(Trim(fields[0]).c_str()));
		Profession prof = Profession(atoi(Trim(fields[1]).c_str()));
		Age a = Age(atoi(Trim(fields[2]).c_str()));
		int ddl = atoi(Trim(fields[3]).c_str());
		Information* info = new Information;
		info->name = Trim(fields[4]);
		info->email = Trim(fields[5]);
		info->phone = Trim(fields[6]).c_str();
		info->birthday = Trim(fields[7]).c_str();
		// Create a new patient:
		queue->new_patient(risk, prof, a, info, ddl);
	}
	return queue->getl_queue();
}

// This new added function is used to read the updated info and update the queue:
queue<Patient*>* IO::read_update(string path, Queue* queue)
{
	ifstream fin(path);		// open the stream
	string line;
	getline(fin, line);		// Skip the header line
	while (getline(fin, line))		// ���ж�ȡ�����з���\n�����֣������ļ�β��־eof��ֹ��ȡ
	{
		istringstream sin(line);	// �������ַ���line���뵽�ַ�����istringstream��
		vector<string> fields;		// ����һ���ַ�������
		string field;
		while (getline(sin, field, ','))	// ���ַ�����sin�е��ַ����뵽field�ַ����У��Զ���Ϊ�ָ���
		{
			fields.push_back(field);		// ���ոն�ȡ���ַ������ӵ�����fields��
		}
		// Now we can declare several variables and update information:
		int id = atoi(Trim(fields[0]).c_str());
		int type = atoi(Trim(fields[1]).c_str());
		string up_info = Trim(fields[2]);

		// First check if the given patient is vaild:
		if (NULL == queue->getHashtable()->retrieval(id)) {
			//cout << "The patient with id " << id << " does not exist!" << endl;
			continue;
		}

		// Then check the type of info that is wanted to change:
		if (type >= 0 && type <= 6)
		{
			// Convert the updated info from string to int:
			int info = atoi(up_info.c_str());
			// Update the info:
			queue->update(id, type, info);
		}
		else if (type >= 7 && type <= 10)
		{
			// Update the info:
			queue->update_info(id, type, up_info);
		}
		else
		{
			cout << "Invalid type number!" << endl;
			exit(1);
		}
	}
	return queue->getl_queue();
}

//ɾ���ַ����пո��Ʊ���tab����Ч�ַ�:
string IO::Trim(string& str)
{
	//str.find_first_not_of(" \t\r\n"),���ַ���str�д�����0��ʼ�������״β�ƥ��"-\t\r\n"��λ��
	str.erase(0, str.find_first_not_of("\t\r\n"));
	str.erase(str.find_last_not_of("\t\r\n") + 1);
	return str;
}
