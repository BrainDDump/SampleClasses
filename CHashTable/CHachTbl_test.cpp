#include <string>

#include "CHashTbl.cpp"

size_t hash_func (int key)
{
	return key;
}

void test1()
{
	CHashTbl<int, std::string> H(5, &hash_func);

	H.insert(66, "ttt");
	H.insert(1027, "tiit");
	H.insert(12345, "eee");

	H.insert(340, "pidorrrrrit");
	H.insert(103242, "giit");
	H.insert(1223123, "452e");

	H.print();

	H.remove(4223421);
	H.remove(66);
	H.remove(346);

	H.print();

	H.clear();

	H.print();
}


int main ()
{
	test1();

	return 0;
}