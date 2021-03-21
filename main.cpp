#include <iostream>
#include <cstring>
#include <fstream>
#include "studentRecord.h"
#include "hash_table.h"
#include "list_of_lists.h"
#include "zip_code_tree.h"
using namespace std;

int main(int argc, char const *argv[]) {
	string inputFile = "", configFile = "(none)";
	for (int i = 1; i < argc-1; i=i+2) {
		if (strcmp(argv[i],"-i") == 0)
			inputFile = argv[i+1];
		else if (strcmp(argv[i],"-c") == 0)
			configFile = argv[i+1];
		else
			cout << "MISTAKE" << endl;
	}
	if (inputFile == "") {
		cout << "Could not find expected parameters! Terminating." << endl;
		return 1;
	}
	cout << "Arguments: " << inputFile << " - " << configFile << endl;
	char input_file_delimiter[2];
	char command_delimiter[2];
	int hash_table_size = 1000;
	int current_year = 2020;
	ifstream config_file;
	if (configFile != "(none)") {
		config_file.open(configFile);
	}
	if (configFile != "(none)" && errno == 0) {
		cout << "CONFIG FILE" << endl;
		string line;
		// config_file.open(configFile);
		char char_line[50];
		char* saveptr;
		int kontinue;
		do {
			kontinue = 0;
			getline(config_file, line);
			if (line.at(0) == '-')
				break;
			// char char_line[line.length() + 1];        // Char array
			for (int i = 0; i < (int)line.length(); ++i) { // Copy string to char array
				char_line[i] = line[i];
			}
			char_line[line.length()] = '\0';          // Make sure it ends with a \0
			saveptr = char_line;
			string c1 = strtok_r(saveptr, " ", &saveptr);
			string c2 = strtok_r(saveptr, " ", &saveptr);
			// cout << "c1: " << c1 << endl;
			// cout << "c2: " << c2 << endl;
			if (c1 == "input_file_delimiter") {
				if (c2 == "comma")
					strcpy(input_file_delimiter, ",");
				else if (c2 == "space")
					strcpy(input_file_delimiter, " ");
				else {
					cout << "Could not resolve input_file_delimiter from input file, defaulting to comma." << endl;
					strcpy(input_file_delimiter, ",");
				}
			}
			else if (c1 == "command_delimiter") {
				if (c2 == "comma")
					strcpy(command_delimiter, ",");
				else if (c2 == "space")
					strcpy(command_delimiter, " ");
				else {
					cout << "Could not resolve command_delimiter from input file, defaulting to space." << endl;
					strcpy(command_delimiter, " ");
				}
			}
			else if (c1 == "hash_table_size") {
				if (c2 == "") {
					cout << "Could not resolve hash_table_size from input file, defaulting to 1000." << endl;
					hash_table_size = 1000;
				}
				for (int i = 0; i < (int)c2.length(); ++i) {
					if (c2.at(i) > '9' || c2.at(i) < '0') {
						cout << "Could not resolve hash_table_size from input file, defaulting to 1000." << endl;
						hash_table_size = 1000;
						kontinue = 1;
						break;
					}
				}
				if (kontinue == 1)
					continue;
				hash_table_size = stoi(c2);
			}
			else if (c1 == "current_year") {
				if (c2 == "") {
					cout << "Could not resolve current_year from input file, defaulting to 2020." << endl;
					current_year = 2020;
					continue;
				}
				for (int i = 0; i < (int)c2.length(); ++i) {
					if (c2.at(i) > '9' || c2.at(i) < '0') {
						cout << "Could not resolve current_year from input file, defaulting to 2020." << endl;
						current_year = 2020;
						kontinue = 1;
						break;
					}
				}
				if (kontinue == 1)
					continue;
				current_year = stoi(c2);
			}
		} while (line != "");
		config_file.close();
	}
	else {
		if (errno == 2)
			cout << "Config file not found, defaulting to default values." << endl;
		else
			cout << "No config file, defaulting to default values." << endl;
		strcpy(input_file_delimiter, " ");
		strcpy(command_delimiter, " ");
		// Look through file and count lines
		string line;
		ifstream input_file;
		hash_table_size = -1;
		input_file.open(inputFile);
		do {
			getline(input_file, line);
			hash_table_size++;
		} while (line != "");
		cout << "File has " << hash_table_size << " lines" << endl;
		input_file.close();
		// Done counting lines in file
	}
	cout << "hash_table_size: " << hash_table_size << endl;
	cout << "current_year: " << current_year << endl;
	cout << "input_file_delimiter: |" << input_file_delimiter << "|" << endl;
	cout << "command_delimiter: |" << command_delimiter << "|" << endl;
////////////////////////////////////////////////////////////////////////////////////////////////
	HashTable student_hash_table(hash_table_size); // LOOK THROUGH FILE AND COUNT LINES
	PrimaryList list_of_lists(current_year);
	studentRecord* temp = NULL;
	ifstream input_file;
	string line;
	input_file.open(inputFile);
	int retourn;
	int duplicates = 0;
	do {
		getline(input_file, line);
		if (line == "") {
			cout << "EOF\n";
			break;
		}
		retourn = 0;
		temp = new studentRecord(line, input_file_delimiter, current_year, retourn, 0); // retourn is passed as a reference, so the constructor can return an error code
		if (retourn == 1) {
			cout << "MAIN - Invalid record in file. Ignoring." << endl;
			delete temp;
			continue;
		}
		cout << "Student " << temp->get_studentID() << " inserted" << endl;
		retourn = student_hash_table.insert(temp);
		if (retourn == 2) {
			cout << "MAIN - Found record with existing ID. Ignoring." << endl;
			delete temp;
			duplicates++;
			continue;
		}
		list_of_lists.insert(temp);
	} while (line != ""); // This isn't actually used, this loop stops at the "break" a few lines above.
	input_file.close();

	cout << "Duplicate records discarded: " << duplicates << endl;
	int quitt = 0;
	string input;
	string input_tokens[7];
	while (quitt == 0) {
		cout << "Type a command: ";
		getline(cin, input);
		char char_line[input.length() + 1];        // Char array
		for (int i = 0; i < (int)input.length(); ++i) { // Copy string to char array
			char_line[i] = input[i];
		}
		char_line[input.length()] = '\0';          // Make sure it ends with a \0
		cout << "     You typed: " << char_line << endl;
		char* saveptr = char_line;
		for (int i = 0; i < 7; ++i) {
			if (strcmp(saveptr, "") != 0 && saveptr[0] != ' ') // Ignore any spaces ' ' in a row
				input_tokens[i] = strtok_r(saveptr, " ", &saveptr);
			else
				input_tokens[i] = ""; // Stop if there's no more arguments
		}
		if (input_tokens[0] == "i") { // 1
			int retourn = 0;
			if (input_tokens[1] == "" || input_tokens[2] == "" || input_tokens[3] == "" || input_tokens[4] == "" || input_tokens[5] == "" || input_tokens[6] == "") {
				cout << "The student record you're entering is incomplete, try again." << endl;
				continue;
			}
			temp = new studentRecord(input, command_delimiter, current_year, retourn, 1);
			if (retourn != 0) {
				cout << "Invalid input, try again." << endl;
				delete temp;
				continue;
			}
			// temp->print();
			retourn = student_hash_table.insert(temp);
			if (retourn == 2) {
				cout << "Student " << input_tokens[1] << " exists" << endl;
				delete temp;
				continue;
			}
			list_of_lists.insert(temp);
			cout << "Student " << input_tokens[1] << " inserted" << endl;
		}
		else if (input_tokens[0] == "l") { // 2
			if (input_tokens[1] == "") {
				cout << "Invalid command, try again." << endl;
				continue;
			}
			temp = student_hash_table.search(input_tokens[1]);
			if (temp == NULL)
				cout << "Student " << input_tokens[1] << " does not exist" << endl;
			else {
				temp->print();
				cout << endl;
			}
		}
		else if (input_tokens[0] == "d") { // 3
			if (input_tokens[1] == "") {
				cout << "Invalid command, try again." << endl;
				continue;
			}
			if (student_hash_table.remove(input_tokens[1], list_of_lists) < 0)
				cout << "Record not found!" << endl;
			else
				cout << "Record " << input_tokens[1] << " deleted" << endl;
		}
		else if (input_tokens[0] == "n") { // 4
			if (input_tokens[1] == "") {
				cout << "Invalid command, try again." << endl;
				continue;
			}
			int retourn = list_of_lists.count_in_year(input_tokens[1]);
			if (retourn < 0) {
				cout << "Invalid command, try again." << endl;
				continue;
			}
			else if (retourn == 0)
				cout << "No students enrolled in year " << input_tokens[1] << endl;
			else
				cout << retourn << " student(s) in " << input_tokens[1] << endl;
		}
		// SORTED SECONDARY LIST, RETURN TOP N
		else if (input_tokens[0] == "t") { // 5
			if (input_tokens[1] == "" || input_tokens[2] == "") {
				cout << "Invalid command, try again." << endl;
				continue;
			}
			int retourn = list_of_lists.top(input_tokens[1], input_tokens[2]);
			if (retourn == 1) {
				cout << "Invalid command, try again." << endl;
				continue;
			}
			else if (retourn == 2)
				cout << "No students enrolled in " << input_tokens[2] << endl;
		}
		else if (input_tokens[0] == "a") { // 6
			if (input_tokens[1] == "") {
				cout << "Invalid command, try again." << endl;
				continue;
			}
			float retourn = list_of_lists.average_in_year(input_tokens[1]);
			if (retourn < 0) {
				cout << "Invalid command, try again." << endl;
				continue;
			}
			else if (retourn == 0)
				cout << "No students enrolled in " << input_tokens[1] << endl;
			else
				cout << "Average grade in " << input_tokens[1] << ": " << retourn << endl;
		}
		// 7 IN SECONDARY LIST, WHEN NEXT==NULL, THAT'S THE ONE
		else if (input_tokens[0] == "m") { // 7
			if (input_tokens[1] == "") {
				cout << "Invalid command, try again." << endl;
				continue;
			}
			int retourn = list_of_lists.minimum(input_tokens[1]);
			if (retourn == 1) {
				cout << "Invalid command, try again." << endl;
				continue;
			}
			else if (retourn == 2)
				cout << "No students enrolled in " << input_tokens[1] << endl;
		}
		else if (input_tokens[0] == "c") { // 8
			int retourn = list_of_lists.count_in_all_years();
			if (retourn == 0)
				cout << "No students are enrolled" << endl;
		}
		// MAKE A TREE SORTED BY ZIP CODE, ONE NODE FOR EVERY ZIP CODE. IF ZIP CODE DOESN'T EXIST, CREATE A NODE FOR IT AND ZIP_CODE_COUNTER++.
		// IF IT DOES, STUDENTS_THERE ++. AFTER ALL THE STUDENTS, MAKE AN ARRAY SIZED(N_OF_ZIP_CODES), TRAVERSE THE TREE IN A PRINTING MANNER,
		// AND PUT THE ZIP CODE / N_OF_STUDENTS STRUCTS IN THE ARRAY. THEN FIND THE MAX ELEMENT N TIMES.
		else if (input_tokens[0] == "p") { // 9
			if (input_tokens[1] == "") {
				cout << "Invalid command, try again." << endl;
				continue;
			}
			int retourn = student_hash_table.postal_code_rank(input_tokens[1]);
			if (retourn == 1) {
				cout << "Invalid command, try again." << endl;
				continue;
			}
			else if (retourn == 2)
				cout << "No students enrolled " << endl;
		}
		else if (input_tokens[0] == "e") { // 10
			cout << "exit program" << endl;
			quitt = 1;
		}
		else
			cout << "Unrecognized command, try again." << endl;
	}
	return 0;
}