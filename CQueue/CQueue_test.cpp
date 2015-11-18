#include <iostream>
#include "CQueue.cpp"

void test1 ()
{
	CArrayQueue<int> q(4);

	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);

	q.push(5);
	q.push(6);
	q.push(6);
	q.push(7);
	q.push(8);
	q.push(9);
	q.push(10);
	q.push(11);

	printf("%d\n", q.pop());
	printf("%d\n", q.pop());
	printf("%d\n", q.pop());
	printf("%d\n", q.pop());
	q.push(8);
	printf("%d\n", q.pop());
	printf("%d\n", q.pop());
	printf("%d\n", q.pop());
	printf("%d\n", q.pop());
	printf("%d\n", q.pop());
	printf("%d\n", q.pop());
	printf("%d\n", q.pop());
	printf("%d\n", q.pop());
	printf("%d\n", q.pop());

	printf("%d\n", q.pop());
	printf("%d\n", q.pop());
}

void test2 ()
{
	CListQueue<int> q;

	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);

	q.push(5);
	q.push(6);
	q.push(6);
	q.push(7);
	q.push(8);
	q.push(9);
	q.push(10);
	q.push(11);

	printf("%d\n", q.pop());
	printf("%d\n", q.pop());
	printf("%d\n", q.pop());
	printf("%d\n", q.pop());
	q.push(8);
	printf("%d\n", q.pop());
	printf("%d\n", q.pop());
	printf("%d\n", q.pop());
	printf("%d\n", q.pop());
	printf("%d\n", q.pop());
	printf("%d\n", q.pop());
	printf("%d\n", q.pop());
	printf("%d\n", q.pop());
	printf("%d\n", q.pop());

	printf("%d\n", q.pop());
	printf("%d\n", q.pop());
}

int main ()
{
	test1();
	test2();
	
	return 0;
}