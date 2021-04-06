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
	update = fopen("update.csv", "w");
	// check if fopen successes:
	if (NULL == update)
	{
		std::cout << "The file to write cannot open!" << endl;
		exit(1);
	}
	// Write the header of the output file first:
	fprintf(update, "ID,Risk_Status,Profession,Age,Reg_Year,Reg_Date,Withdraw,Letter_DDL,Priority,");
	fprintf(update, "Name,Email,Phone,Birthday\n");

	// Loop all the patients in the local registry queue and write all the 
	// information into the update.csv:
	while (0 == queue->empty())
	{
		fprintf(update, "%d,%d,%d,",
			queue->front()->getid(), queue->front()->getrisk(), queue->front()->getpro());
		fprintf(update, "%d,%d,%d,",
			queue->front()->getage(), queue->front()->getyear(), queue->front()->getdate());
		fprintf(update, "%d,%d,%d,",
			queue->front()->getwithdraw(), queue->front()->getddl(),queue->front()->getpriority());
		fprintf(update, "%s,%s,%d,%d,", 
			queue->front()->getinfo()->name.c_str(), queue->front()->getinfo()->email.c_str(), 
			queue->front()->getinfo()->phone, queue->front()->getinfo()->birthday);
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
		info->phone = atoi(Trim(fields[6]).c_str());
		info->birthday = atoi(Trim(fields[7]).c_str());
		// Create a new patient:
		queue->new_patient(risk, prof, a, info, ddl);
	}
	return queue->getl_queue();
}

//ɾ���ַ����пո��Ʊ���tab����Ч�ַ�:
string IO::Trim(string& str)
{
	//str.find_first_not_of(" \t\r\n"),���ַ���str�д�����0��ʼ�������״β�ƥ��"-\t\r\n"��λ��
	str.erase(0, str.find_first_not_of("-\t\r\n"));
	str.erase(str.find_last_not_of("-\t\r\n") + 1);
	return str;
}
