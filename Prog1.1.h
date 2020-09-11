namespace Prog1 {

	struct line {
		int* i;
		int* a;
		int k;
	};

	template <class T>
	int getNum(T& a)
	{
		std::cin >> a;
		if (!std::cin.good())	// обнаружена ошибка ввода или конец файла
			return -1;
		return 1;
	}

	line* input_lines_v1(int& m, int& n);
	line* input_lines_v2(int& m, int& n);
	line* input_lines_v3(int& m, int& n);
	void output(line*, int m, int n);
	line* erase(line*, int m);
	line* generate_Matrix(line*, int m, int n, bool (*f)(line&, line&, int));
	bool reverse_order(line&, line&, int n);
}
