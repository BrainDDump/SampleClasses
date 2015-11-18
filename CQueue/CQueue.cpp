#include <assert.h>

template <typename Data_t>
class basic_queue {
public:
	virtual void   push (Data_t) = 0;
	virtual Data_t pop  () = 0;
	virtual void   clear() = 0;

	virtual bool   empty() = 0;
	virtual size_t size () = 0;
};

const int MIN_SZ = 2;

template <typename Data_t>
class CArrayQueue : public basic_queue<Data_t> {
	Data_t* data_;
	size_t  size_;
	size_t  count_;
	int     head_;
	int     tail_;
public:
	CArrayQueue() {
		data_  = new Data_t[MIN_SZ];
		size_  = MIN_SZ;
		count_ = 0;
		head_  = -1;
		tail_  = 0;
	}
	CArrayQueue(size_t size) {
		data_  = new Data_t[size];
		size_  = size;
		count_ = 0;
		head_  = -1;
		tail_  = 0;
	}
	~CArrayQueue() {
		delete [] data_;
	}
	void push (Data_t value) {
		if (size_ == count_) resize();

		data_[tail_] = value;
		++tail_ %= size_;
		count_++;
	}
	Data_t pop () {
		if (count_ == 0) {
			printf("Can not pop, queue is empty!\n");
			Data_t empty;
			return empty;
		}

		count_--;
		return data_[++head_ %= size_];
	}
	void clear() {
		count_ = 0;
		head_  = -1;
		tail_  = 0;
	}
	bool empty() {
		if (count_ == 0) return true;
		return false;
	}
	size_t size() {
		return count_;
	}
private:
	void resize() {
		Data_t* buf = new Data_t[size_ * 2];

		const size_t step = sizeof(Data_t);
		char*  dest;
		char*  src;
		size_t size;

		if (tail_ == 0) {
			// border case
			size = size_ * step;
			std::memcpy(buf, data_, size);
			delete [] data_;
			data_ = buf;

			head_ = -1;
			tail_ = size_;
			size_ *= 2;

			return;
		} else {
			// cpy first part
			dest = (char*)buf;
			src  = (char*)data_;
			size = tail_ * step;
			std::memcpy(dest, src, size);

			// cpy second part
			dest = (char*)buf + (size_ + tail_) * step;
			src  = (char*)data_ + tail_ * step;
			size = (size_ - tail_) * step;
			std::memcpy(dest, src, size);
			delete [] data_;
			data_ = buf;

			head_ += size_;
			size_ *= 2;

			return;
		}

		return;
	}
};

template <typename Data_t>
class CListQueue : public basic_queue<Data_t> {
	struct Node {
		Data_t value;

		Node* next;
		Node* prev;
	};

	Node*  head_;
	Node*  tail_;
	size_t count_;

	Node*  buf_;
public:
	CListQueue() {
		head_  = nullptr;
		tail_  = nullptr;
		count_ = 0;
	}
	~CListQueue() {
		clear();
	}
	void push (Data_t value) {
		buf_ = new Node;
		buf_->value = value;
		buf_->next  = tail_;
		buf_->prev  = nullptr;

		if (tail_ != nullptr) {
			tail_->prev = buf_;
			tail_       = buf_;
		} else {
			tail_ = buf_;
			head_ = buf_;
		}

		count_++;
	}
	Data_t pop () {
		if (count_ == 0) {
			printf("Can not pop, queue is empty!\n");
			Data_t empty;
			return empty;
		}
		Data_t value_buf = head_->value;

		if (count_ == 1) {
			tail_ = nullptr;
			head_ = nullptr;
		} else {
			head_ = head_->prev;
		}
		count_--;

		return value_buf;
	}

	void clear () {
		while (tail_ != nullptr) {
			buf_  = tail_;
			tail_ = tail_->next;

			delete buf_;
		}

		count_ = 0;
		head_  = nullptr;
	}

	bool empty () {
		if (count_ == 0) return true;
		else             return false;
	}

	size_t size () {
		return count_;
	}
};


