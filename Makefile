CC=g++
CFLAGS=-Wall -std=c++11 -ggdb3

all: hash_table.o studentRecord.o list_of_lists.o main.o zip_code_tree.o mngstd

hash_table.o: hash_table.cpp hash_table.h
	$(CC) $(CFLAGS) -c hash_table.cpp

studentRecord.o: studentRecord.cpp studentRecord.h
	$(CC) $(CFLAGS) -c studentRecord.cpp

list_of_lists.o: list_of_lists.cpp list_of_lists.h
	$(CC) $(CFLAGS) -c list_of_lists.cpp

zip_code_tree.o: zip_code_tree.cpp zip_code_tree.h
	$(CC) $(CFLAGS) -c zip_code_tree.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

mngstd: main.cpp studentRecord.o hash_table.o list_of_lists.o zip_code_tree.o
	$(CC) $(CFLAGS) -o mngstd main.o hash_table.o studentRecord.o list_of_lists.o zip_code_tree.o

.PHONY: clean

clean:
	rm -f mngstd main.o hash_table.o studentRecord.o list_of_lists.o zip_code_tree.o