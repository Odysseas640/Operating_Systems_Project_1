#ifndef __ODYS_STUDENT_RECORD__
#define __ODYS_STUDENT_RECORD__
#include <string>
#include <cstring>
#include <iostream>
#include "hash_table.h"
using namespace std;

class studentRecord {
private:
	string studentID;
	string firstName;
	string lastName;
	int zip;
	int year;
	float GPA;
public:
	studentRecord(string line, char* delimiter, int current_year, int& retourn, int from_command);
	string get_studentID();
	int get_year();
	float get_GPA();
	int get_ZIP();
	void print();
	~studentRecord();
};
#endif