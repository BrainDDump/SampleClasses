#include <iostream>
#include <stdio.h>
#include <stdlib.h>

template<typename T>
class CMatrix {
//------------------<< Variables >>----------------------------------
	size_t dim1_;
	size_t dim2_;
	T**    data_;

public:
//------------------<< Setup >>--------------------------------------
	CMatrix():
	dim1_(0), dim2_(0) {
		data_ = NULL;
	}

	CMatrix(size_t dim1, size_t dim2, T value):
	dim1_(dim1), dim2_(dim2) {
		data_ = allocate_memory(dim1_, dim2_);

		for (int i = 0; i < dim1_; ++i) {
			for (int j = 0; j < dim2_; ++j) {
				data_[i][j] = value;
			}
		}
	}

	CMatrix(const CMatrix& other) {
		dim1_ = other.dim1_;
		dim2_ = other.dim2_;

		data_ = allocate_memory(dim1_, dim2_);

		for (int i = 0; i < dim1_; ++i) {
			std::memcpy(data_[i], other.data_[i], sizeof(T) * dim2_);
		}
	}

	~CMatrix() {
		deallocate_memory(data_, dim1_, dim2_);
	}

//------------------<< Main methods >>-------------------------------
	T*& operator [] (int id) {
		if (!check() || id >= dim1_) {
			std::cout << "Acsess error\n";
			exit(EXIT_FAILURE);
		}

		return data_[id];
	}

	CMatrix operator + (const CMatrix& other) const {
		if (dim1_ != other.dim1_ || dim2_ != other.dim2_) {
			std::cout << "Can not add matrixes!\n";
			exit(EXIT_FAILURE);
		}

		CMatrix buf(*this);
		return buf += other;
	}

	CMatrix operator - (const CMatrix& other) const {
		if (dim1_ != other.dim1_ || dim2_ != other.dim2_) {
			std::cout << "Can not add matrixes!\n";
			exit(EXIT_FAILURE);
		}

		CMatrix buf(*this);
		return buf -= other;
	}

	CMatrix operator += (const CMatrix& other) {
		if (dim1_ != other.dim1_ || dim2_ != other.dim2_) {
			std::cout << "Can not add matrixes! Check Dimentions!\n";
			exit(EXIT_FAILURE);
		}

		for (int i = 0; i < dim1_; ++i) {
			for (int j = 0; j < dim2_; ++j) {
				data_[i][j] += other.data_[i][j];
			}
		}

		return *this;
	}

	CMatrix operator -= (const CMatrix& other) {
		if (dim1_ != other.dim1_ || dim2_ != other.dim2_) {
			std::cout << "Can not add matrixes! Check Dimentions!\n";
			exit(EXIT_FAILURE);
		}

		for (int i = 0; i < dim1_; ++i) {
			for (int j = 0; j < dim2_; ++j) {
				data_[i][j] += other.data_[i][j];
			}
		}

		return *this;
	}

	CMatrix operator * (const CMatrix& other) const {
		if (dim2_ != other.dim1_) {
			std::cout << "Can not multiply matrixes! Check Dimentions!\n";
			exit(EXIT_FAILURE);
		}

		CMatrix result(dim1_, other.dim2_, 0);
		T buf;
		for (int i = 0; i < dim1_; ++i) {
			for (int j = 0; j < other.dim2_; ++j) {
				buf = T();
				for (int k = 0; k < dim2_; ++k) {
					buf += data_[i][k] * other.data_[k][j];
				}
				result.data_[i][j] = buf;
			}
		}

		return result;
	}
//------------------<< Main diagnostics >>---------------------------
	void dump() const {
		std::cout << std::endl;
		std::cout << "----< CMatrix dump >---" << std::endl;
		for (int i = 0; i < dim1_; ++i) {
			for (int j = 0; j < dim2_; ++j) {
				std::cout << data_[i][j] << ' ';
			}
			std::cout << std::endl;
		}
		std::cout << "----< End of dump >----" << std::endl;
	}

	inline bool check () {
		if (!dim1_ || !dim2_ || !data_) return false;
		else                            return true;
	}
private:
//------------------<< Private methods >>----------------------------
	T** allocate_memory(int dim1, int dim2) {
		T** buf = new T*[dim1];
		for (int i = 0; i < dim1; ++i) {
			buf[i] = new T[dim2];
		}

		return buf;
	}

	void deallocate_memory(T** buf, int dim1, int dim2) {
		for (int i = 0; i < dim1; ++i) {
			delete [] buf[i];
		}
		delete [] buf;
	}
};
