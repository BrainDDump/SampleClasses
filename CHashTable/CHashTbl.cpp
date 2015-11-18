#include <iostream>
#include <assert.h>

#include "../CList/CList.cpp"
#include "CHashTbl.h"

template <typename Key_t, typename Data_t>
size_t CHashTbl<Key_t, Data_t>::s_cell = 0;

template <typename Key_t, typename Data_t>
CHashTbl<Key_t, Data_t>::CHashTbl (size_t table_size, func_ptr hash_function):
TBL_SZ(table_size), hash_function_(hash_function) {
	if (hash_function_ == nullptr) {
		printf("Hash function set incorrect!\n");
		assert(false);
	}
	table_ = new CList<Key_t, Data_t>[TBL_SZ];
}

template <typename Key_t, typename Data_t>
CHashTbl<Key_t, Data_t>::~CHashTbl () {
	delete [] table_;
}

template <typename Key_t, typename Data_t>
bool CHashTbl<Key_t, Data_t>::insert (Key_t key, Data_t data) {
	s_cell  = (*hash_function_)(key);
	s_cell %= TBL_SZ;

	return table_[s_cell].insert(key, data);
}

template <typename Key_t, typename Data_t>
bool CHashTbl<Key_t, Data_t>::remove (Key_t key) {
	s_cell  = (*hash_function_)(key);
	s_cell %= TBL_SZ;

	return table_[s_cell].remove(key);
}

template <typename Key_t, typename Data_t>
void CHashTbl<Key_t, Data_t>::clear () {
	for (int i = 0; i < TBL_SZ; ++i) {
		table_[i].clear();
	}
}

template <typename Key_t, typename Data_t>
bool CHashTbl<Key_t, Data_t>::set (Key_t key, Data_t data) {
	s_cell  = (*hash_function_)(key);
	s_cell %= TBL_SZ;

	return table_[s_cell].set(key, data);
}

template <typename Key_t, typename Data_t>
Data_t CHashTbl<Key_t, Data_t>::operator [] (Key_t key) const {
	s_cell  = (*hash_function_)(key);
	s_cell %= TBL_SZ;

	return table_[s_cell][key];
}

template <typename Key_t, typename Data_t>
bool CHashTbl<Key_t, Data_t>::containes (Key_t key) const {
	s_cell  = (*hash_function_)(key);
	s_cell %= TBL_SZ;

	return table_[s_cell].containes(key);
}

template <typename Key_t, typename Data_t>
void CHashTbl<Key_t, Data_t>::print () const {
	std::cout << "Hash table printing...\n";
	for (int i = 0; i < TBL_SZ; ++i) {
		table_[i].print();
	}
	std::cout << "Hash table print end\n";
}

