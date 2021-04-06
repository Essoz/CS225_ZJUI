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
		fprintf(update, "%d,%d,%d,%d,%d,%d,%d,%d,",
			queue->front()->getid(), queue->front()->getrisk(), queue->front()->getpro(),
			queue->front()->getage(), queue->front()->getyear(), queue->front()->getdate(),
			queue->front()->getwithdraw(), queue->front()->getddl(),queue->front()->getpriority());
		fprintf(update, "%s,%s,%d,%d,", 
			queue->front()->getinfo()->name, queue->front()->getinfo()->email, 
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
	while (getline(fin, line))		// 整行读取，换行符“\n”区分，遇到文件尾标志eof终止读取
	{
		istringstream sin(line);	// 将整行字符串line读入到字符串流istringstream中
		vector<string> fields;		// 声明一个字符串向量
		string field;
		while (getline(sin, field, ','))	// 将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
		{
			fields.push_back(field);		// 将刚刚读取的字符串添加到向量fields中
		}
		// Now we can declare several variables and create new patients:
		Risk risk = atoi(Trim(fields[0]));
		Profession prof = atoi(Trim(fields[1]));
		Age a = atoi(Trim(fields[2]));
		int year = atoi(Trim(fields[3]));
		int date = atoi(Trim(fields[4]));
		int ddl = atoi(Trim(fields[5]));
		Information* info = new Information;
		info->name = Trim(fields[6]);
		info->email = Trim(fields[7]);
		info->phone = atoi(Trim(fields[8]));
		info->birthday = atoi(Trim(fields[9]));
		// Create a new patient:
		queue->new_patient(risk, prof, a, info, year, date, ddl);
	}
	return queue;
}

//删除字符串中空格，制表符tab等无效字符:
string IO::Trim(string& str)
{
	//str.find_first_not_of(" \t\r\n"),在字符串str中从索引0开始，返回首次不匹配"\t\r\n"的位置
	str.erase(0, str.find_first_not_of(" \t\r\n"));
	str.erase(str.find_last_not_of(" \t\r\n") + 1);
	return str;
}
