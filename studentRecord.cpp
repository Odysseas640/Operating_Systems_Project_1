#include "studentRecord.h"

studentRecord::studentRecord(string line, char* delimiter, int current_year, int& retourn, int from_command) {
	char char_line[line.length() + 1];        // Char array
	for (int i = 0; i < (int)line.length(); ++i) { // Copy string to char array
		char_line[i] = line[i];
	}
	char_line[line.length()] = '\0';          // Make sure it ends with a \0
	char* saveptr = char_line;
	this->studentID = strtok_r(saveptr, delimiter, &saveptr);
	if (from_command == 1) // If this is an "i" command, the first token is "i", so skip it.
		this->studentID = strtok_r(saveptr, delimiter, &saveptr);
	this->lastName = strtok_r(saveptr, delimiter, &saveptr);
	this->firstName = strtok_r(saveptr, delimiter, &saveptr);
	for (int i = 0; i < (int)strlen(saveptr); ++i) {
		if (saveptr[i] != '0' && saveptr[i] != '1' && saveptr[i] != '2' && saveptr[i] != '3' &&
			saveptr[i] != '4' && saveptr[i] != '5' && saveptr[i] != '6' && saveptr[i] != '7' &&
			saveptr[i] != '8' && saveptr[i] != '9' && saveptr[i] != '.' &&
			saveptr[i] != delimiter[0] && saveptr[i] != '\n') {
			retourn = 1;
		}
	}
	if (retourn == 0) {
		this->zip = atoi(strtok_r(saveptr, delimiter, &saveptr));
		this->year = atoi(strtok_r(saveptr, delimiter, &saveptr));
		if (this->year > current_year)
			retourn = 1;
		this->GPA = atof(strtok_r(saveptr, delimiter, &saveptr));
	}
}
string studentRecord::get_studentID() {
	return this->studentID;
}
int studentRecord::get_year() {
	return this->year;
}
float studentRecord::get_GPA() {
	return this->GPA;
}
int studentRecord::get_ZIP() {
	return this->zip;
}
void studentRecord::print() {
	cout << this->studentID << " " << this->firstName << " " << this->lastName << " " << this->zip << " " << this->year << " " << this->GPA << " ";
}
studentRecord::~studentRecord() {
}