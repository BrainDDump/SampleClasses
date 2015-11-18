#include <iostream>
#include <fstream>
#include <time.h>

#include "CBinaryTree.cpp"

int * RANDOM_ARRAY (int min, int max, int N) {
	int i;
	int * a = new int[N];

	srand (time (NULL));

	for (i = 0; i < N; i++)
		a[i] = min + rand () % (max - min + 1);

	return (a);
}

void print(const int& key, const std::string& value) {
	std::cout  << key   << std::endl;
	std::cout  << value << std::endl;
}

void print2(const int& key, const int& value) {
	std::cout << key << std::endl;
	std::cout << value << std::endl;
}

std::vector<int> get_array_from_file(const char* file_name) {
	std::vector<int> vec;
	int buf;
	std::ifstream in(file_name, std::ifstream::in);
	while (!in.eof()) {
		in >> buf;
		vec.push_back(buf);
	}
	in.close();

	return vec;
}

std::vector<std::string> get_string_array_from_file(const char* file_name) {
	std::vector<std::string> vec;
	std::string buf;
	std::ifstream in(file_name, std::ifstream::in);
	while (!in.eof()) {
		in >> buf;
		vec.push_back(buf);
	}
	in.close();

	return vec;
}

void test1() {
	CBinaryTree<int, std::string> tree;
	tree.set_print(&print);
	const int SIZE = 20;

	int* array = RANDOM_ARRAY(-99, 500, SIZE);
	std::vector<int> vec;
	for (int i = 0; i < SIZE; ++i) {
		vec.push_back(array[i]);
	}
	delete [] array;
	std::vector<std::string> vec_1 = get_string_array_from_file("in_2.txt");
	int size   = vec_1.size();
	int size_2 = vec.size();

	size = (size < size_2)? size : size_2;

	for (int i = 0; i < size; ++i) {
		tree.insert(vec[i], vec_1[i]);
	}

	tree.graph(2, 3);
}

void test2() {
	std::vector<int> vec = get_array_from_file("in.txt");
	std::vector<std::pair<int, int>> vec_2;

	for (const int& el : vec) {
		vec_2.push_back(std::make_pair(el, el));
	}

	CBinaryTree<int, int> tree(vec_2);
	tree.set_print(&print2);
	tree.graph(7, 7);

	CBinaryTree<int, int> tree_2(tree, 900);
	tree_2.print();

	tree.begin();
	printf("current value: %d\n", tree.current_value());

	printf("\n");

	tree.delete_branch(900);
	tree.print();

	std::cout << std::endl;
	std::cout << tree.find(900) << "; " << tree.find(9000);
}

void test3 () {
	std::vector<int> vec = get_array_from_file("in.txt");

	std::vector<std::pair<int, int>> vec_2;
	for (const int& el : vec) {
		vec_2.push_back(std::make_pair(el, el));
	}

	CBinaryTree<int, int> tree_2(vec_2);
	tree_2.set_print(&print2);

	printf ("depth %d\n", tree_2.depth());
	tree_2.print();
	tree_2.graph(2, 2);

}


int main() {
	clock_t t1, t2;
	t1 = clock();
	test1();
	t2 = clock();

	std::cout << t2 - t1;

	test2();
	test3();

	return 0;
}