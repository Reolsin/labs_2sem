#include <iostream>
#include "Prog1.1.h"

namespace Prog1 {

	line* input_lines_v3(int& m, int& n)
	{
		const char* pr = "";
		line* str = nullptr;
		int* buf = nullptr;
		do {
			std::cout << pr << std::endl;
			std::cout << "Enter number of lines: --> ";
			pr = "You are wrong; repeat please!";
			if (getNum(m) < 0)
				return nullptr;
		} while (m < 1);

		pr = "";
		do {
			std::cout << pr << std::endl;
			std::cout << "Enter number of columns: --> ";
			pr = "You are wrong; repeat please!";
			if (getNum(n) < 0)
				return nullptr;
		} while (n < 1);

		try {
			str = new line[m];
			buf = new int[2*n];
		}
		catch (std::bad_alloc& ba) {
			std::cout << "------ Allocation Error #1: " << ba.what() << std::endl;
			return nullptr;
		}

		int i, j, k, c;

		for (i = 0; i < m; i++) {
			str[i].a = nullptr;
			str[i].i = nullptr;
			str[i].k = 0;
		}

		for (j = 0; j < n; j++)
			buf[2 * j] = 0;

		do {
			std::cout << "Enter line for values (inter index < 0 or >= " << m << " to end input): -->" << std::endl;
			if (getNum(i) < 0) {
				delete[] buf;
				return erase(str, m);
			}
			if ((i >= 0) && (i < m)) {
				k = 0;
		
				do {
					std::cout << "Enter column for values (inter index < 0 or >= " << n << " to end input): -->" << std::endl;
					if (getNum(j) < 0) {
						delete[] buf;
						return erase(str, m);
					}
					if ((j >= 0) && (j < n)) {
						std::cout << "Enter value (" << i << "," << j <<"): -->" << std::endl;
						if (getNum(buf[2 * j]) < 0) {
							delete[] buf;
							return erase(str, m);
						}
						if (buf[2 * j]) {
							buf[2 * j + 1] = j;
							k++;
						}
					}

				} while ((j >= 0) && (j < n));

				try {
					if (k) {
						delete[] str[i].a;
						delete[] str[i].i;
						str[i].a = new int[k];
						str[i].i = new int[k];
						str[i].k = k;
					}
				}
				catch (std::bad_alloc& ba) {
					std::cout << "------ Allocation Error #2: " << ba.what() << std::endl;
					delete[] buf;
					return erase(str, i);
				}

				for (j = 0, c = 0; j < n; j++)
					if (buf[2 * j]) {
						str[i].a[c] = buf[2 * j];
						str[i].i[c] = buf[2 * j + 1];
						buf[2 * j] = 0;
						c++;
					}
			}
		} while ((i >= 0) && (i < n));
		
		delete[] buf;

		return str;
	}

	void output(line* A, int m, int n)
	{
		int j, k;
		std::cout << "Matrix" << std::endl;
		for (int i = 0; i < m; ++i) {
			if (A[i].k)
				for (j = 0, k = 0; j < n; ++j) {
					if (j == A[i].i[k]) {
						std::cout << A[i].a[k] << "  ";
						k++;
					}
					else std::cout << '0' << "  ";
				}
			else
				for (j = 0; j < n; ++j)
					std::cout << '0' << "  ";
			std::cout << std::endl;
		}
	}

	line* erase(line* A, int m)
	{
		for (int i = 0; i < m; i++) {
			delete[] A[i].a;
			delete[] A[i].i;
		}
		delete[] A;
		return nullptr;
	}

	line* generate_Matrix(line* A, int m, int n, bool (*f)(line&, line&, int))
	{
		line* B = nullptr;
		try {
			B = new line[m];
		}
		catch (std::bad_alloc& ba) {
			std::cout << "------ Allocation Error #3: " << ba.what() << std::endl;
			return nullptr;
		}

		for (int i = 0; i < m; i++)
			if (f(B[i], A[i], n))
				return erase(B, m);

		return B;
	}

	bool reverse_order(line& str_new, line& str_old, int n)
	{
		int k = str_old.k;
		try {
			if (k) {
				str_new.a = new int[k];
				str_new.i = new int[k];
				str_new.k = k;
			}
			else {
				str_new.a = nullptr;
				str_new.i = nullptr;
				str_new.k = k;
			}
		}
		catch (std::bad_alloc& ba) {
			std::cout << "------ Allocation Error #4: " << ba.what() << std::endl;
			return true;
		}

		for (int j = 0; j < k; j++) {
			str_new.a[j] = str_old.a[k - j - 1];
			str_new.i[j] = n - 1 - str_old.i[k - j - 1];
		}

		return false;
	}
}
