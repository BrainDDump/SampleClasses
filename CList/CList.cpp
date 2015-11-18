#include <iostream>

#include "CList.h"

template <typename Key_t, typename Data_t>
CList<Key_t, Data_t>::CList () {
	head_ = nullptr;
}

template <typename Key_t, typename Data_t>
CList<Key_t, Data_t>::~CList () {
	Node* buf;
	while (head_ != nullptr) {
		buf   = head_->next;
		delete head_;
		head_ = buf;
	}
}

template <typename Key_t, typename Data_t>
bool CList<Key_t, Data_t>::insert (Key_t key, Data_t data) {
	if (containes(key)) return false;

	Node* new_node = new Node;
	new_node->key  = key;
	new_node->data = data;
	new_node->next = head_;

	head_ = new_node;

	return true;
}

template <typename Key_t, typename Data_t>
bool CList<Key_t, Data_t>::remove (Key_t key) {
	Node* prev = nullptr;
	Node* buf  = head_;
	while (buf != nullptr && buf->key != key) { // try to change to for !
		prev = buf;
		buf  = buf->next;
	}
	if (buf == nullptr) return false;

	if (buf == head_) {
		buf = head_->next;
		delete head_;
		head_ = buf;
	} else {
		prev->next = buf->next;
		delete buf;
	}

	return true;
}

template <typename Key_t, typename Data_t>
void CList<Key_t, Data_t>::clear () {
	Node* buf;
	while (head_ != nullptr) {
		buf = head_->next;
		delete head_;
		head_ = buf;
	}
	head_ = nullptr;
}

template <typename Key_t, typename Data_t>
Data_t CList<Key_t, Data_t>::operator [] (Key_t key) const {
	Node* buf = head_;
	while (buf != nullptr && buf->key != key) {
		buf = buf->next;
	}
	if (buf == nullptr) {
		printf("the element with this key is not in the list!\n");
		Data_t empty;
		return empty;
	}

	return buf->data;
}


template <typename Key_t, typename Data_t>
bool CList<Key_t, Data_t>::set (Key_t key, Data_t data) {
	Node* buf = head_;
	while (buf != nullptr && buf->key != key) {
		buf = buf->next;
	}
	if (buf == nullptr) return false;

	buf->data = data;

	return true;
}

template <typename Key_t, typename Data_t>
bool CList<Key_t, Data_t>::containes (Key_t key) const {
	Node* buf = head_;
	while (buf != nullptr && buf->key != key) {
		buf = buf->next;
	}
	if (buf == nullptr) return false;
	
	return true;
}

template <typename Key_t, typename Data_t>
void CList<Key_t, Data_t>::print () const {
	Node* buf = head_;
	std::cout << std::endl;
	while (buf != nullptr) {
		std::cout << "key:" << buf->key
		          << ", data:" << buf->data << "   ";
		buf = buf->next;
	}
	std::cout << std::endl;
}
