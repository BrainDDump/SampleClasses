#include <iostream>

#include "CMatrix.cpp"

void test_1() {
	CMatrix<int> A(5, 3, 2);
	CMatrix<int> B(5, 3, 10);
	A.dump();
	B.dump();

	(A += B).dump();

	CMatrix<int> C = A + B;
	C.dump();
}

void test_2() {
	CMatrix<int> A(5, 3, 1);
	CMatrix<int> B(3, 10, 2);
	A[2][1] = 0;
	B[0][0] = -1;
	A.dump();
	B.dump();

	(A * B).dump();
}

int main() {
	
	test_1();
	test_2();

	return 0;
}
