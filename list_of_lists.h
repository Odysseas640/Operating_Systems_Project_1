#ifndef __ODYS_LIST_OF_LISTS__
#define __ODYS_LIST_OF_LISTS__
#include <iostream>
#include <string>
#include <cmath>
#include "studentRecord.h"
using namespace std;
class studentRecord;

typedef struct secondary_list_node SecondaryListNode;
struct secondary_list_node {
	studentRecord* stoodent;
	SecondaryListNode* Next;
};

typedef struct secondary_list_head_node SecondaryListHeadNode;
struct secondary_list_head_node {
	SecondaryListNode* Last;
	SecondaryListNode* First;
};

typedef struct primary_list_node PrimaryListNode;
struct primary_list_node {
	int year;
	SecondaryListHeadNode* students_list;
	PrimaryListNode* Next;
};

class PrimaryList {
private:
	PrimaryListNode* primary_list;
	int current_year;
public:
	PrimaryList(int current_year);
	int insert(studentRecord* student_to_insert);
	int remove(string student_id_to_remove, int year);
	void print();
	int count_in_year(string year_to_count);
	float average_in_year(string year_to_count);
	int top(string num, string year);
	int count_in_all_years();
	int minimum(string year);
	~PrimaryList();
};

#endif