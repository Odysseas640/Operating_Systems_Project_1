#include "list_of_lists.h"

PrimaryList::PrimaryList(int current_year = 2020) {
	this->primary_list = NULL;
	this->current_year = current_year;
}

int PrimaryList::insert(studentRecord* student_to_insert) {
	if (this->primary_list == NULL) {
		this->primary_list = new PrimaryListNode;
		this->primary_list->year = this->current_year;
		this->primary_list->Next = NULL;
		this->primary_list->students_list = NULL;
	}
	PrimaryListNode* current_node = this->primary_list;
	for (int i = this->current_year; i > student_to_insert->get_year() + 0; --i) { // Traverse through every Primary Node until we get to the desired year. If nodes don't exist along the way, make them.
		if (current_node->Next == NULL) {
			current_node->Next = new PrimaryListNode;
			current_node->Next->year = i-1;
			current_node->Next->Next = NULL;
			current_node->Next->students_list = NULL;
		}
		current_node = current_node->Next;
	}
	if (current_node->students_list == NULL) {
		current_node->students_list = new SecondaryListHeadNode;
		current_node->students_list->First = new SecondaryListNode;
		current_node->students_list->Last = current_node->students_list->First;
		current_node->students_list->First->stoodent = student_to_insert;
		current_node->students_list->First->Next = NULL;
		return 0;
	}
	if (current_node->students_list->First->stoodent->get_GPA() < student_to_insert->get_GPA()) {
		SecondaryListNode* new_node = new SecondaryListNode;
		new_node->stoodent = student_to_insert;
		new_node->Next = current_node->students_list->First;
		current_node->students_list->First = new_node;
		return 0;
	}
	SecondaryListNode* current_node_2 = current_node->students_list->First;
	while (current_node_2->Next != NULL && current_node_2->Next->stoodent->get_GPA() >= student_to_insert->get_GPA()) {
		current_node_2 = current_node_2->Next;
	}
	SecondaryListNode* new_node = new SecondaryListNode;
	new_node->stoodent = student_to_insert;
	new_node->Next = current_node_2->Next;
	current_node_2->Next = new_node;
	if (new_node->Next == NULL) // Update last node
		current_node->students_list->Last = new_node;
	return 0;
}
int PrimaryList::remove(string student_id_to_remove, int year) {
	PrimaryListNode* current_node = this->primary_list;
	for (int i = this->current_year; i > year; --i) {
		current_node = current_node->Next;
	}
	SecondaryListNode* current_node_2 = current_node->students_list->First;

	if (current_node_2->stoodent->get_studentID() == student_id_to_remove) { // At least one element, check if it's the first one
		current_node->students_list->First = current_node->students_list->First->Next;
		if (current_node->students_list->Last == current_node_2) { // If we're deleting the only node
			delete current_node->students_list;
			current_node->students_list = NULL;
		}
		delete current_node_2;
		return 0;
	}
	while (current_node_2->Next != NULL) {
		if (current_node_2->Next->stoodent->get_studentID() == student_id_to_remove) {
			SecondaryListNode* to_delete = current_node_2->Next;
			current_node_2->Next = current_node_2->Next->Next;
			if (current_node->students_list->Last == to_delete) // If we're deleting the last node
				current_node->students_list->Last = current_node_2;
			delete to_delete;
			return 0;
		}
		current_node_2 = current_node_2->Next;
	}
	return 1;
}
void PrimaryList::print() {
	cout << "PrimaryList print" << endl;
	PrimaryListNode* current_node = this->primary_list;
	while (current_node != NULL) {
		cout << "PrimaryList year: " << current_node->year << endl;
		if (current_node->students_list == NULL) {
			cout << "(empty)" << endl;
			current_node = current_node->Next;
			continue;
		}
		SecondaryListNode* current_node_2 = current_node->students_list->First;
		int student_this_year = 0;
		while (current_node_2 != NULL) {
			cout << "Student " << student_this_year << endl;
			current_node_2->stoodent->print();
			cout << endl;
			current_node_2 = current_node_2->Next;
			student_this_year++;
		}
		current_node = current_node->Next;
	}
	cout << "PrimaryList print end" << endl;
}
int PrimaryList::count_in_year(string year_to_count) {
	for (int i = 0; i < (int)year_to_count.length(); ++i) {
		if (year_to_count.at(i) < '0' || year_to_count.at(i) > '9') {
			cout << "=" << year_to_count.at(i) << "=" << endl;
			return -1;
		}
	}
	PrimaryListNode* current_node = this->primary_list;
	int year_to_count_int = stoi(year_to_count);
	// cout << "year_to_count_int: " << year_to_count_int << endl;
	while (current_node != NULL) {
		if (current_node->year == year_to_count_int) {
			SecondaryListNode* current_node_2 = current_node->students_list->First;
			int student_count = 0;
			while (current_node_2 != NULL) {
				current_node_2 = current_node_2->Next;
				student_count++;
			}
			return student_count;
		}
		current_node = current_node->Next;
	}
	return 0;
}
float PrimaryList::average_in_year(string year_to_count) {
	for (int i = 0; i < (int)year_to_count.length(); ++i) {
		if (year_to_count.at(i) < '0' || year_to_count.at(i) > '9') {
			cout << "=" << year_to_count.at(i) << "=" << endl;
			return -1;
		}
	}
	PrimaryListNode* current_node = this->primary_list;
	int year_to_count_int = stoi(year_to_count);
	while (current_node != NULL) {
		if (current_node->year == year_to_count_int) {
			SecondaryListNode* current_node_2 = current_node->students_list->First;
			int student_count = 0;
			float grade_sum = 0.0;
			while (current_node_2 != NULL) {
				grade_sum += current_node_2->stoodent->get_GPA();
				student_count++;
				current_node_2 = current_node_2->Next;
			}
			return grade_sum / (float)student_count;
		}
		current_node = current_node->Next;
	}
	return 0;
}
int PrimaryList::top(string num, string year) {
	for (int i = 0; i < (int)year.length(); ++i) {
		if (year.at(i) < '0' || year.at(i) > '9') {
			cout << "=" << year.at(i) << "=" << endl;
			return 1; // Not a number
		}
	}
	int year_int = stoi(year);
	for (int i = 0; i < (int)num.length(); ++i) {
		if (num.at(i) < '0' || num.at(i) > '9') {
			cout << "=" << num.at(i) << "=" << endl;
			return 1; // Not a number
		}
	}
	int num_int = stoi(num);
	PrimaryListNode* current_node = this->primary_list;
	while (current_node != NULL) {
		if (current_node->year == year_int) {
			SecondaryListNode* current_node_2 = current_node->students_list->First;
			for (int i = 0; i < num_int; ++i) {
				if (current_node_2 == NULL)
					break;
				cout << current_node_2->stoodent->get_studentID() << " " << current_node_2->stoodent->get_GPA() << endl;
				if (i == num_int - 1 && current_node_2->Next != NULL && fabs(current_node_2->stoodent->get_GPA() - current_node_2->Next->stoodent->get_GPA()) < 0.0001)
					i--; // If multiple students have the same grade in the last iteration, print them all
				current_node_2 = current_node_2->Next;
			}
			return 0;
		}
		current_node = current_node->Next;
	}
	return 2; // No students enrolled this year
}
int PrimaryList::minimum(string year) { // 7
	for (int i = 0; i < (int)year.length(); ++i) {
		if (year.at(i) < '0' || year.at(i) > '9') {
			cout << "=" << year.at(i) << "=" << endl;
			return 1; // Not a number
		}
	} // IF MANY STUDENTS HAVE THE SAME AVERAGE, RETURN ALL OF THEM
	int year_int = stoi(year);
	PrimaryListNode* current_node = this->primary_list;
	int student_count = 0;
	while (current_node != NULL) {
		if (current_node->year == year_int) {
			SecondaryListNode* current_node_2 = current_node->students_list->First;
			float minimum_GPA = current_node->students_list->Last->stoodent->get_GPA();
			if (current_node_2 == NULL)
				return 2;
			while (current_node_2 != NULL) {
				if (fabs(minimum_GPA - current_node_2->stoodent->get_GPA()) < 0.0001) {
					student_count++;
					current_node_2->stoodent->print();
					cout << endl;
				}
				current_node_2 = current_node_2->Next;
			}
		}
		current_node = current_node->Next;
	}
	if (student_count == 0)
		return 2; // No students found
	else
		return 0;
}
int PrimaryList::count_in_all_years() {
	PrimaryListNode* current_node = this->primary_list;
	int count_all_years = 0;
	while (current_node != NULL) {
		if (current_node->students_list == NULL) {
			current_node = current_node->Next;
			continue;
		}
		SecondaryListNode* current_node_2 = current_node->students_list->First;
		string this_year;
		int count_in_year = 0;
		if (current_node_2 != NULL) {
			while (current_node_2 != NULL) {
				count_in_year++;
				count_all_years++;
				current_node_2 = current_node_2->Next;
			}
		}
		cout << current_node->year << ": " << count_in_year << " students" << endl;
		current_node = current_node->Next;
	}
	return count_all_years;
}
PrimaryList::~PrimaryList() {
	PrimaryListNode* current_node = this->primary_list;
	while (current_node != NULL) {
		if (current_node->students_list == NULL) {
			PrimaryListNode* to_delete = current_node;
			current_node = current_node->Next;
			delete to_delete;
			continue;
		}
		SecondaryListNode* current_node_2 = current_node->students_list->First;
		while (current_node_2 != NULL) {
			SecondaryListNode* to_delete_2 = current_node_2;
			current_node_2 = current_node_2->Next;
			delete to_delete_2;
		}
		delete current_node->students_list;
		PrimaryListNode* to_delete = current_node;
		current_node = current_node->Next;
		delete to_delete;
	}
}