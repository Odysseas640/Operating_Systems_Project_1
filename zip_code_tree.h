#ifndef __ODYS_ZIP_CODE_TREE__
#define __ODYS_ZIP_CODE_TREE__
#include <iostream>
#include <string>
#include "hash_table.h"
#include "studentRecord.h"
using namespace std;

struct zip_structure {
	int ZIP;
	int students_here;
};

typedef struct zip_tree_node ZipTreeNode;
struct zip_tree_node {
	struct zip_structure zip_struct;
	ZipTreeNode* Left;
	ZipTreeNode* Right;
};

class ZipTree {
private:
	int unique_zips;
	ZipTreeNode* Root;
	ZipTreeNode** array;
	int insert(int new_zip, ZipTreeNode*& root);
	void print_recursive(ZipTreeNode* root);
	void tree_destructor_recursive(ZipTreeNode* root);
public:
	ZipTree();
	int insert(int new_zip);
	void print();
	int postal_code_rank(int rank);
	void postal_code_rank_recursion(ZipTreeNode* Root, int& index);
	int get_unique_zips();
	~ZipTree();
	ZipTreeNode* getRoot();
};
#endif