#ifndef __ODYS_HASH_TABLE__
#define __ODYS_HASH_TABLE__
#include <iostream>
#include <string>
#include "studentRecord.h"
#include "list_of_lists.h"
#include "zip_code_tree.h"
using namespace std;
class studentRecord;
class PrimaryList;

typedef struct bucket Bucket;
struct bucket {
	studentRecord* stoodent;
	Bucket* next; // Next bucket in the list
};

class HashTable {
private:
	int array_size, bucket_size;
	Bucket** hash_table; // Dynamic array of buckets. Each bucket is a list node and may point to another bucket.
public:
	HashTable(int array_size);
	int insert(studentRecord* stoodent_ptr); // Use hash function to insert disease.
	int remove(string student_id_to_remove, PrimaryList& list_of_lists);
	studentRecord* search(string student_id);
	int postal_code_rank(string rank);
	void print();
	~HashTable();
};

#endif