#include <string>

#include "CList.cpp"

void test1()
{
	CList<int, std::string> list;
	list.print();

	list.insert(5, "gggg");
	list.print();
	list.insert(7, "hhh");
	std::cout << list[5];
	std::cout << list[2];
	list.print();
	list.remove(5);
	list.print();
	list.remove(7);
	list.print();

	list.clear();
}

int main ()
{
	test1();

	return 0;
}