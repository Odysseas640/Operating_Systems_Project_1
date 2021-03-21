#include "zip_code_tree.h"

ZipTree::ZipTree() {
	this->Root = NULL;
	this->unique_zips = 0;
}
int ZipTree::insert(int new_zip) {
	return this->insert(new_zip, this->Root);
}
int ZipTree::insert(int new_zip, ZipTreeNode*& root) {
	if (root == NULL) {
		root = new ZipTreeNode;
		root->zip_struct.ZIP = new_zip;
		root->zip_struct.students_here = 1;
		root->Left = NULL;
		root->Right = NULL;
		this->unique_zips++;
	}
	else if (new_zip > root->zip_struct.ZIP) {
		this->insert(new_zip, root->Right);
	}
	else if (new_zip < root->zip_struct.ZIP) {
		this->insert(new_zip, root->Left);
	}
	else if (new_zip == root->zip_struct.ZIP) {
		root->zip_struct.students_here++;
	}
	else // DIAGNOSTIC
		cout << "MISTAKE IN DATE TREE" << endl;
	return 0;
}
void ZipTree::print() {
	this->print_recursive(this->Root);
}
void ZipTree::print_recursive(ZipTreeNode* root) {
	if (root == NULL) {
		return;
	}
	if (root->Left != NULL)
		this->print_recursive(root->Left);
	cout << "ZIP: " << root->zip_struct.ZIP << " - studentz: " << root->zip_struct.students_here << endl;
	if (root->Right != NULL)
		this->print_recursive(root->Right);
}
void ZipTree::postal_code_rank_recursion(ZipTreeNode* Root, int& index) {
	// Go through every node in the tree, and save every node in the array
	if (Root == NULL) {
		return;
	}
	if (Root->Left != NULL)
		this->postal_code_rank_recursion(Root->Left, index);
	this->array[index] = Root;
	index++;
	if (Root->Right != NULL)
		this->postal_code_rank_recursion(Root->Right, index);
}
int ZipTree::postal_code_rank(int rank) {
	// Find the max and make it 0, rank-1 times.
	// Find the max once more but don't delete it.
	// Go through the array one last time and print ZIPs that == max.
	// Array of pointers to the nodes in the tree.
	// When the process (of question 9) is over, only the array is deleted and the nodes are deleted with the tree.
	this->array = new ZipTreeNode*[this->unique_zips];
	for (int i = 0; i < this->unique_zips; ++i) {
		this->array[i] = NULL;
	}
	int index = 0;
	postal_code_rank_recursion(this->Root, index); // Go through the tree in a printing manner and fill the array with the tree's nodes.
	// Now find the max element in the array, <rank-1> times. The rank'th time is what we want.
	// In essence, we're shaving off the top zip codes to get the one we want, which is sort of in the middle.
	int max_n_of_students_in_one_zip = 0;
	int index_of_max_n_of_students_in_one_zip = 0;
	int outer_iterations = rank - 1;
	if (outer_iterations > this->unique_zips - 1) {
		cout << "Not enough ZIPs to get " << rank << "'th rank, returning lowest." << endl;
		outer_iterations = this->unique_zips - 1;
	}
	for (int i = 0; i < outer_iterations; ++i) {
		max_n_of_students_in_one_zip = 0;
		for (int j = 0; j < this->unique_zips; ++j) {
			if (array[j]->zip_struct.students_here > max_n_of_students_in_one_zip) {
				max_n_of_students_in_one_zip = array[j]->zip_struct.students_here;
				index_of_max_n_of_students_in_one_zip = j;
			}
		}
		array[index_of_max_n_of_students_in_one_zip]->zip_struct.students_here = 0;
	}
	// Now the highest number of students in one zip code is the one we want.
	// Go through the array once and find that number.
	max_n_of_students_in_one_zip = 0;
	for (int j = 0; j < this->unique_zips; ++j) {
		if (array[j]->zip_struct.students_here > max_n_of_students_in_one_zip) {
			max_n_of_students_in_one_zip = array[j]->zip_struct.students_here;
		}
	}
	// We know what that number is, so we go through the array one last time,
	// and print the zip codes with that many students, because if there's more than one we want them all.
	if (rank <= this->unique_zips)
		cout << "Rank " << rank << " ZIP(s) is:" << endl;
	else
		cout << "You typed a higher rank than there are unique zips. Least popular ZIP(s) is:" << endl;
	for (int i = 0; i < this->unique_zips; ++i) {
		if (array[i]->zip_struct.students_here == max_n_of_students_in_one_zip) {
			cout << array[i]->zip_struct.ZIP << endl;
		}
	}
	cout << "with " << max_n_of_students_in_one_zip << " students" << endl;
	return 0;
}
int ZipTree::get_unique_zips() {
	return this->unique_zips;
}
void ZipTree::tree_destructor_recursive(ZipTreeNode* root) {
	if (root == NULL)
		return;
	if (root->Left != NULL)
		tree_destructor_recursive(root->Left);
	if (root->Right != NULL)
		tree_destructor_recursive(root->Right);
	delete root;
}
ZipTree::~ZipTree() {
	delete[] this->array;
	this->tree_destructor_recursive((this->Root));
}