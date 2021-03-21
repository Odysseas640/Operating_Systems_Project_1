#include "hash_table.h"

HashTable::HashTable(int array_size) {
	this->array_size = array_size;
	this->bucket_size = 1;
	this->hash_table = new Bucket*[this->array_size]; // Array of pointers to Bucket
	for (int i = 0; i < this->array_size; ++i) {
		this->hash_table[i] = NULL;
	}
}

int HashTable::insert(studentRecord* student_ptr) {
	if (this->search(student_ptr->get_studentID()) != NULL) {
		return 2; // A record with the same ID exists
	}
	////////////////////////////////////////////////////////////////////////// Hash function
	unsigned int sum_of_letters = 0;
	string stoodent_id = student_ptr->get_studentID();
	unsigned int multiplier = 13;
	for (int i = 0; i < (int)stoodent_id.length(); ++i) {
		sum_of_letters += (unsigned int) multiplier * stoodent_id.at(i); // Multiply the ASCII codes with some random (always the same) numbers
		// cout << "sum of letters: " << sum_of_letters << endl;
		multiplier = multiplier * 91;
	}
	unsigned int array_position = sum_of_letters % this->array_size;
	/////////////////////////////////////////////////////////////////////////////
	// cout << "array position: " << array_position << endl;
	
	if (this->hash_table[array_position] == NULL) {
		this->hash_table[array_position] = new Bucket;
		this->hash_table[array_position]->stoodent = student_ptr;
		this->hash_table[array_position]->next = NULL;
		return 0;
	}
	Bucket* current_bucket = this->hash_table[array_position];
	while (current_bucket->next != NULL) {
		current_bucket = current_bucket->next;
	}
	current_bucket->next = new Bucket;
	current_bucket->next->next = NULL;
	current_bucket->next->stoodent = student_ptr;
	return 0;
}

int HashTable::remove(string student_id_to_remove, PrimaryList& list_of_lists) {
	unsigned int sum_of_letters = 0;
	string stoodent_id = student_id_to_remove;
	unsigned int multiplier = 13;
	for (int i = 0; i < (int)student_id_to_remove.length(); ++i) {
		sum_of_letters += (unsigned int) multiplier * stoodent_id.at(i); // Multiply the ASCII codes with some random (always the same) numbers
		multiplier = multiplier * 91;
	}
	unsigned int array_position = sum_of_letters % this->array_size;

	Bucket* current_bucket = hash_table[array_position];

	if (current_bucket == NULL) // No elements in the list
		return -1;
	if (current_bucket->stoodent->get_studentID() == student_id_to_remove) { // At least one element, check if it's the first one
		int year_to_return = current_bucket->stoodent->get_year();
		list_of_lists.remove(hash_table[array_position]->stoodent->get_studentID(), hash_table[array_position]->stoodent->get_year());
		delete hash_table[array_position]->stoodent;
		hash_table[array_position] = hash_table[array_position]->next;
		delete current_bucket;
		return year_to_return;
	}
	while (current_bucket->next != NULL) {
		if (current_bucket->next->stoodent->get_studentID() == student_id_to_remove) {
			int year_to_return = current_bucket->next->stoodent->get_year();
			list_of_lists.remove(current_bucket->next->stoodent->get_studentID(), current_bucket->next->stoodent->get_year());
			Bucket* to_delete = current_bucket->next;
			current_bucket->next = current_bucket->next->next;
			delete to_delete->stoodent;
			delete to_delete;
			return year_to_return;
		}
		current_bucket = current_bucket->next;
	}
	return -1;
}

studentRecord* HashTable::search(string student_id) {
	unsigned int sum_of_letters = 0;
	unsigned int multiplier = 13;
	for (int i = 0; i < (int)student_id.length(); ++i) {
		sum_of_letters += (unsigned int) multiplier * student_id.at(i); // Multiply the ASCII codes with some random (always the same) numbers
		multiplier = multiplier * 91;
	}
	unsigned int array_position = sum_of_letters % this->array_size;

	Bucket* current_bucket = hash_table[array_position];
	while (current_bucket != NULL) {
		if (current_bucket->stoodent->get_studentID() == student_id) {
			return current_bucket->stoodent;
		}
		current_bucket = current_bucket->next;
	}
	return NULL;
}
void HashTable::print() {
	cout << "HASH TABLE PRINT" << endl;
	for (int i = 0; i < this->array_size; ++i) { // For every spot in the array
		cout << "Array spot " << i << endl;
		Bucket* current_bucket = this->hash_table[i];
		int bucket_n = 0;
		while (current_bucket != NULL) { // Print all the buckets / list nodes in said spot
			cout << "Bucket N: " << bucket_n << endl;
			current_bucket->stoodent->print();
			cout << endl;
			current_bucket = current_bucket->next;
			bucket_n++;
		}
	}
	cout << "HASH TABLE PRINT END" << endl;
}
int HashTable::postal_code_rank(string rank) {
	for (int i = 0; i < (int)rank.length(); ++i) {
		if (rank.at(i) < '0' || rank.at(i) > '9') {
			cout << "=" << rank.at(i) << "=" << endl;
			return 1; // Not a number
		}
	}
	int rank_int = stoi(rank);
	ZipTree ziptree1;
	// Make a binary tree of (ZIP, students_here) nodes
	int students_n = 0;
	for (int i = 0; i < this->array_size; ++i) { // For every spot in the array
		Bucket* current_bucket = this->hash_table[i];
		while (current_bucket != NULL) { // Print all the buckets / list nodes in said spot
			ziptree1.insert(current_bucket->stoodent->get_ZIP());
			current_bucket = current_bucket->next;
			students_n++;
		}
	}
	if (students_n == 0)
		return 2;
	else
		return ziptree1.postal_code_rank(rank_int); // The rest of the work is done in the tree
}
HashTable::~HashTable() {
	for (int i = 0; i < this->array_size; ++i) {
		Bucket* current_bucket = hash_table[i];
		while (current_bucket != NULL) {
			if (current_bucket->stoodent != NULL) {
				delete current_bucket->stoodent;
			}
			Bucket* to_delete = current_bucket;
			current_bucket = current_bucket->next;
			delete to_delete;
		} // Now all buckets in this array spot have been deleted
	}
	delete[] this->hash_table;
}