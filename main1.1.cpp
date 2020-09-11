#include <iostream>
#include "Prog1.1.h"

using namespace Prog1;

int main() {
	int n, m;
	line* A = input_lines_v3(m, n);
	if (!A) {
		std::cout << "incorrect data" << std::endl;
		return 1;
	}
	output(A, m, n);
	line* B = generate_Matrix(A, m, n, reverse_order);
	if (!B) {
		erase(A, m);
		return 1;
	}
	output(B, m, n);
	erase(A, m);
	erase(B, m);
	return 0;
}
