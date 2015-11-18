#include <iostream>
#include <string.h>
#include <stdio.h>
#include <iomanip>

template < typename T >
class CMatrix {
private:
	size_t dim1_;
	size_t dim2_;
	T**    data_;

	inline bool check () const {
		if (!dim1_ || !dim2_ || !data_) return false;
		else                            return true;
	}

	const char UNDERSCORE   = '_';
	const char VERTICAL_BAR = '|';

public:
	CMatrix():
	dim1_(0), dim2_(0) {
		data_ = NULL;
	}

	CMatrix(size_t dim1, size_t dim2, T value):
	dim1_(dim1), dim2_(dim2) {
		data_ = new T*[dim1_];

		for (int i = 0; i < dim1_; ++i) {
			data_[i] = new T[dim2_];
		}

		for (int i = 0; i < dim1_; ++i) {
			for (int j = 0; j < dim2_; ++j) {
				data_[i][j] = value;
			}
		}
	}

	~CMatrix() {
		for (int i = 0; i < dim1_; ++i) {
			delete [] data_[i];
		}

		delete [] data_;
	}

	T*& operator [] (int id) const {
		if (!check() || id >= dim1_) {
			fputs("Acsess error\n", stderr);
			exit(EXIT_FAILURE);
		}

		return data_[id];
	}

	void insert(std::string buffer, int line, int column, int dim1, int dim2) {
		if (typeid(T) != typeid(char)) {
			printf("Unable to draw!\n");
			return;
		}

		size_t prev_iterator = 0;
		size_t iterator      = 0;
		size_t len;
		std::vector<std::string> lines;
		std::string substr;

		while (true) {
			iterator = buffer.find("\n", iterator);
			if (iterator == std::string::npos) break;
			if (iterator < prev_iterator)      break;

			len = iterator - prev_iterator;
			if (len > dim2) {
				printf("%zu Print does not match size of the box!\n", len);
				return;
			}

			substr = buffer.substr(prev_iterator, len);
			lines.push_back(substr);

			prev_iterator = ++iterator;
		}

		if (lines.size() > dim2) {
				printf("%zu Print does not match size of the box!\n", len);
				return;
		}

		for (int i = 0; i < lines.size(); ++i) {
			for (int j = 0; j < lines[i].length(); ++j) {
				data_[line + i][column + j] = lines[i][j];
			}
		}
	}

	void draw_frame (int line, int column, int a, int b) {
		if (typeid(T) != typeid(char)) {
			printf("Unable to draw!\n");
			return;
		}

		for (int i = 0; i < b;  ++i) {
			data_[line][column + i + 1] = UNDERSCORE;
		}
		data_[line][column + 1 + b / 2] = VERTICAL_BAR;
		for (int i = 0; i < b;  ++i) {
			data_[line + a + 1][column + i + 1] = UNDERSCORE;
		}
		for (int i = 0; i <= a; ++i) {
			data_[line + i + 1][column] = VERTICAL_BAR;
		}
		for (int i = 0; i <= a; ++i) {
			data_[line + i + 1][column + b + 1] = VERTICAL_BAR;
		}
	}

	void draw_horizontal_line (int line, int column, int len) {
		if (typeid(T) != typeid(char)) {
			printf("Unable to draw!\n");
			return;
		}

		for (int i = 0; i < len; ++i) {
			data_[line][column + i] = UNDERSCORE;
		}
	}

	void print() const {
		std::cout << std::endl;
		std::cout << "Matrix print" << std::endl;
		for (int i = 0; i < dim1_; ++i) {
			for (int j = 0; j < dim2_; ++j) {
				std::cout << std::setw(4);
				std::cout << data_[i][j] << ' ';
			}
			std::cout << std::endl;
		}
		std::cout << "----< End of ptint >----" << std::endl;
	}

	void print_block() const {
		std::cout << std::endl;
		std::cout << "Matrix print" << std::endl;
		for (int i = 0; i < dim1_; ++i) {
			for (int j = 0; j < dim2_; ++j) {
				std::cout << data_[i][j];
			}
			std::cout << std::endl;
		}
		std::cout << "----< End of print >----" << std::endl;
	}
};
