Odysseas Stefas, sdi1700151

Commands to run:
make
./mngstd -i input300.txt -c config_file

My program starts by reading and saving the arguments. It doesn't matter which order they're in.
The configuration file has 4 options: hash table size, current year, and 2 delimiters for the student records input. One for records from the file and one for the "i" command. The options are "space" and "comma". The comma is because, at first, we were told that the input file would have commas, not spaces, and I decided to leave it as an option.
The configuration file is not necessary, and if any parameters in it are missing, the program uses default values.
The program reads the file line by line, and for every line, which would be a student, it creates a studentRecord object. That object is inserted in the hash table and the reverse index (list of lists).

The hash function multiplies the first ASCII code of the student's ID with a multiplier that is 13 at first, and then the multiplier is multiplied with 91. The result is added to the sum. In the next iteration, the second ASCII character is multiplied with the multiplier, which is now 13*91, that's added to the sum, and the multiplier gets multiplied with 91 again. And so on. I used unsigned ints so they don't become negative when they overflow. 13 and 91 are just 2 arbitrary numbers. After all of that, the array index is sum % array_size.

The hash table insert function uses the hash table's search function to see if there'a already a record with the same ID, and if there is, the new record is discarded. The hash table is an array of lists of buckets. Each bucket contains a pointer to a studentRecord and a pointer to the next bucket in the bucket list. The studentRecord is created in the main function, and the hash table just stores a pointer to that object.
After the hash table, the studentRecord object is inserted in the list of lists. The primary list has one node for each year, starting from the current year and going back. Each node of the primary list has a secondary list, and the secondary list stores pointers to studentRecords of that year. The students are inserted in the secondary list in a sorted by GPA manner.
The secondary list has a head node, that contains a pointer to the first and last element in the secondary list. The last element is useful for finding the lowest GPA in the year, in case there are multiple students with the same lowest score.
The list of lists saves a pointer to the studentRecord object created in main(), like the hash table does. It's my understanding that the point of a hash table AND a list of lists is to efficiently find the studentRecords we want in 2 different ways. For some commands the hash table is better, for others the list of lists is better.
When the list of lists is created, the primary list always starts with the current year and goes back. Some nodes may not contain any students at all. For example, if the list is empty, current year is 2020 and we're inserting a student in 2015, 6 PrimaryList nodes will be created. 2020, 2019, and so on until 2015. And the student is inserted in the SecondaryList under the PrimaryList's 2015 node.
In other words, there are always PrimaryList nodes for every year between the current year and the year of the oldest student. Some nodes may be empty.

1 - "i":
This command uses the same method for inserting students as the file reading loop. Its complexity should be O(1) for the hash table and O(students_in_that_year) for the list of lists.

2 - "l":
This command uses the hash table's search function to find the desired record and returns a pointer to it. If it doesn't exist, it returns NULL. Its complexity should be O(1).

3 - "d":
This is a hash table function that uses the hash function to find the array stop, and goes through the list. If the record with the desired ID is found, it deletes it, and then it calls the delete function of the list of lists, passes it the year of that student, and the list of lists deletes the SecondaryList node pointing to that student. If the student doesn't exist in the hash table, function returns -1. Its complexity should be O(1) for the hash table and O(students_in_that_year) for the list of lists.

4 - "n":
This is a list of lists function that just goes through the desired year's SecondaryList and counts its nodes. Complexity should be O(students_in_that_year).

5 - "t":
This is a list of lists function that prints the top "n" students in the desired year, since the students in every year are sorted by GPA. However, the last student may have the same grade as the one below them. If that's the case, those students that have the same grade at the end are printed as well. Complexity should be O(students_in_that_year).
We were told on Piazza that the functions can print the results by themselves, they don't have to return them.

6 - "a":
This list of lists function adds all the students' GPA in the desired year and divides the sum with however many they are. Complexity should be O(students_in_that_year).

7 - "m":
This list of lists function goes to the desired year and saves the GPA of the last student in that SecondaryList, using the pointer to the last node in the SecondaryHeadNode. Then it goes through the list and prints the students that have that GPA. Only the bottom few students may have the same GPA. This is only useful if more than one student has the lowest GPA, otherwise I could've just gone through the list and printed the current student when Next==NULL, without the need for a HeadNode and a pointer to the last node. Complexity should be O(students_in_that_year).

8 - "c":
This list of lists function goes through the SecondaryList of every PrimaryList node, and prints the year and the number of students there. Complexity should be O(all_students).

9 - "p":
This hash table function is the most tricky part. I decided to use a binary tree, the nodes of which contain a struct with a ZIP code and the students who live there. There are as many tree nodes as there are unique ZIP codes.
I go through every student in the hash table, without the hash function. I send his ZIP code into the tree. If the tree has a node with that ZIP code, the students_there are increased by 1. Otherwise a new ZIP code tree node is created.
After the tree is done, an array is created in the ZIPTree object. It has a spot for every unique ZIP code/Tree node. The ZIP tree has a recursive function that goes through it in a printing manner, and it sends every node in the tree into the array. After that is done, we have an unsorted array of [ZIP, students_there] structs.
After that, I go through the array <rank-1> times, and every time I zero out the most popular ZIP code. Then, the most popular ZIP code left is the rank'th, the one we want. I go through the array once to find the most popular ZIP code. I could print it right there, but there may be 2 ZIP codes with the same popularity. So, I go through the array one last time and print the ZIP codes that are as popular as the most popular one.
The complexity of all this should be O(all_students) + O(rank * unique_zips). The O(all_students part) is definitely bigger.
