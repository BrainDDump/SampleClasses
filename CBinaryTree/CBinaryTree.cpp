//!{=========================================================================================
//! @file    CBinaryTree.cpp
//! @date    2015-09-18
//! @author  Dubovitskiy Kirill <kirill2003de@gmail.com>
//!
//! Implementation of the CBinaryTree class.
//! 
//!}==========================================================================================

#ifndef BIN_TREE
#define BIN_TREE

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <sstream>

#include <assert.h>

#include "CPrintMatrix.cpp"
#include "CBinaryTree.h"

//!---------------------< MACROS >------------------------------------------------------------
#define ASSERT(condition, error_name, error_description, action) \
    if (!condition) {                                            \
        *error_ = error_name;                                    \
        printf(error_description);                               \
        action;                                                  \
    }

#define MAX2(x, y) (x > y)? x : y
#define MAX3(x, y, z) (MAX2(x, y) > z)? MAX2(x, y) : z

//!---------------------< consts >------------------------------------------------------------
const int  GAP        = 4; /* GAP between two bloks (including the frame) */
const char VERTICAL_BAR = '|';

//!---------------------< constructers && destructer >----------------------------------------
template <typename Key_t, typename Data_t>
CBinaryTree<Key_t, Data_t>::CBinaryTree() {
    root_       = nullptr;
    error_      = new int;
    *error_     = err_t::NO_ERR;
    print_ptr_  = nullptr;
}

template <typename Key_t, typename Data_t>
CBinaryTree<Key_t, Data_t>::CBinaryTree(std::vector<std::pair<Key_t, Data_t>> vec) {
    root_      = nullptr;
    error_     = new int;
    *error_    = err_t::NO_ERR;
    print_ptr_ = nullptr;
    load_vector(vec);
}

template <typename Key_t, typename Data_t>
CBinaryTree<Key_t, Data_t>::CBinaryTree(const CBinaryTree& other) {
    root_      = m_clone_branch(other->root_);
    error_     = new int;
    *error_    = err_t::NO_ERR;
    print_ptr_ = nullptr;
}

template <typename Key_t, typename Data_t>
CBinaryTree<Key_t, Data_t>::CBinaryTree(CBinaryTree& other, Key_t key) {
    other.find(key);
    root_       = m_clone_branch(other.active_branch_);
    error_      = new int;
    *error_     = err_t::NO_ERR;
    print_ptr_  = nullptr;
}


template <typename Key_t, typename Data_t>
CBinaryTree<Key_t, Data_t>::~CBinaryTree() {
    m_delete_branch(root_);
    delete error_;
}

//!---------------------< additional setup >--------------------------------------------------
template <typename Key_t, typename Data_t>
void CBinaryTree<Key_t, Data_t>::set_print (print_ptr_t print_ptr) {
    print_ptr_ = print_ptr;
}

//!---------------------< #0 depth methods >--------------------------------------------------
template <typename Key_t, typename Data_t>
bool CBinaryTree<Key_t, Data_t>::insert (Key_t key, Data_t value) {
    if (root_ == nullptr) {
        root_          = m_create_node (key, value);
        active_branch_ = root_;
        return true;
    }

    return m_insert(root_, key, value);
}

template <typename Key_t, typename Data_t>
void CBinaryTree<Key_t, Data_t>::load_vector (std::vector<std::pair<Key_t, Data_t>> vec) {
    for (const std::pair<Key_t, Data_t>& el : vec) {
        insert(el.first, el.second);
    }
}

template <typename Key_t, typename Data_t>
void CBinaryTree<Key_t, Data_t>::erase () {
    m_delete_branch(root_);
    root_ = nullptr;
}

template <typename Key_t, typename Data_t>
bool CBinaryTree<Key_t, Data_t>::find (Key_t key) {
    return m_find(root_, key);
}

template <typename Key_t, typename Data_t>
void CBinaryTree<Key_t, Data_t>::begin () {
    active_branch_ = root_;
}

template <typename Key_t, typename Data_t>
Data_t CBinaryTree<Key_t, Data_t>::current_value() const {
    ASSERT((active_branch_ != nullptr), err_t::PTR_ERR, "Bad ptr!", assert(0));

    return active_branch_->value;
}

template <typename Key_t, typename Data_t>
Data_t CBinaryTree<Key_t, Data_t>::get(Key_t key) const {
    ASSERT(find(key), err_t::NOT_FOUND, "Element with this key not found!", assert(0));

    return active_branch_->value;
}

template <typename Key_t, typename Data_t>
bool CBinaryTree<Key_t, Data_t>::delete_branch(Key_t key) {
    ASSERT(find(key), err_t::NOT_FOUND, "Warning, branch not found!", return false);
    Node* branch = active_branch_;
    m_delete_branch(branch);

    return true;
}

template <typename Key_t, typename Data_t>
int CBinaryTree<Key_t, Data_t>::depth() const {
    if (root_ == nullptr) return 0;
    return m_depth (root_, 0);
}

template <typename Key_t, typename Data_t>
void CBinaryTree<Key_t, Data_t>::print () const {
    if (root_ == nullptr) return;
    ASSERT((print_ptr_ != nullptr), err_t::PRINT_ERR, "Print function not set!", return);

    m_print(root_);
}

template <typename Key_t, typename Data_t>
void CBinaryTree<Key_t, Data_t>::print_branch (Key_t key) const {
    ASSERT((print_ptr_ != nullptr), err_t::PRINT_ERR, "Print function not set!", return);
    find(key);

    m_print(active_branch_);
}

template <typename Key_t, typename Data_t>
void CBinaryTree<Key_t, Data_t>::graph(size_t a, size_t b) const {
    if (root_ == nullptr) return;
    ASSERT((print_ptr_ != nullptr), err_t::PRINT_ERR, "Print function not set!", return);

    if (b % 2 == 0) b++;

    int dim_1 = (depth() + 1)      * (a + GAP);
    int dim_2 = m_get_width(root_) * (b + GAP);
    CMatrix<char> image(dim_1, dim_2, ' ');

    std::stringstream stream_buffer;
    std::streambuf* old = std::cout.rdbuf();
    std::cout.rdbuf(stream_buffer.rdbuf());

    m_graph(root_, image, stream_buffer, 0, 0, a, b);

    std::cout.rdbuf(old);

    image.print_block();
}

//!---------------------< #1 depth methods >--------------------------------------------------
template <typename Key_t, typename Data_t>
bool CBinaryTree<Key_t, Data_t>::m_insert (Node* branch, Key_t key, Data_t value) {
    if (branch == nullptr) return false;
    Key_t current_key = branch->key;

    if (key < current_key) {
        if (branch->left != nullptr) {
            m_insert (branch->left, key, value);
        } else {
            Node* new_node   = m_create_node (key, value);
            branch->left     = new_node;

            active_branch_   = new_node;
            return true;
        }
    } else if (key > current_key) {
        if (branch->right != nullptr) {
            m_insert (branch->right, key, value);
        } else {
            Node* new_node   = m_create_node (key, value);
            branch->right    = new_node;

            active_branch_   = new_node;
            return true;
        }
    }

    return false;
}

template <typename Key_t, typename Data_t>
typename CBinaryTree<Key_t, Data_t>::Node*
CBinaryTree<Key_t, Data_t>::m_create_node (Key_t key, Data_t value) const {
    Node* new_node = new Node;

    new_node->key   = key;
    new_node->value = value;
    new_node->left  = nullptr;
    new_node->right = nullptr;

    return new_node;
}

template <typename Key_t, typename Data_t>
typename CBinaryTree<Key_t, Data_t>::Node*
CBinaryTree<Key_t, Data_t>::m_clone_branch (Node* sample_branch) const {
    if (sample_branch == nullptr) return nullptr;

    Node* branch_cpy   = m_create_node(sample_branch->key, sample_branch->value);

    if (sample_branch->left != nullptr) {
        branch_cpy->left = m_clone_branch(sample_branch->left);
    } else {
        branch_cpy->left = nullptr;
    }
    if (sample_branch->right != nullptr) {
        branch_cpy->right = m_clone_branch(sample_branch->right);
    } else {
        branch_cpy->right = nullptr;
    }

    return branch_cpy;
}


template <typename Key_t, typename Data_t>
void CBinaryTree<Key_t, Data_t>::m_delete_branch(Node* branch) const {
    if (branch == nullptr) return;
    if (branch->left  != nullptr) m_delete_branch(branch->left);
    if (branch->right != nullptr) m_delete_branch(branch->right);

    delete branch;
}

template <typename Key_t, typename Data_t>
bool CBinaryTree<Key_t, Data_t>::m_find(Node* branch, Key_t key) {
    if (branch == nullptr) {
        active_branch_ = nullptr;
        return false;
    }

    Key_t current_key = branch->key;
    if (key < current_key) {
        return m_find (branch->left, key);
    } else if (current_key < key) {
        return m_find (branch->right, key);
    } else {
        active_branch_ = branch;
        return true;
    }
}

template <typename Key_t, typename Data_t>
int CBinaryTree<Key_t, Data_t>::m_depth(Node* branch, int depth) const {
    int buf_1 = 0, buf_2 = 0;
    if (branch->left  != nullptr) {
        buf_1 = m_depth (branch->left, depth + 1);
    }
    if (branch->right != nullptr) {
        buf_2 = m_depth (branch->right, depth + 1);
    }

    depth = MAX3(buf_1, buf_2 , depth);
    return depth;
}

template <typename Key_t, typename Data_t>
void CBinaryTree<Key_t, Data_t>::m_print(Node* branch) const {
    if (branch == nullptr) return;

    if (branch->left  != nullptr) m_print(branch->left);
    (*print_ptr_)(branch->key, branch->value);
    if (branch->right != nullptr) m_print(branch->right);
}

int iteration = 0;


template <typename Key_t, typename Data_t>
void CBinaryTree<Key_t, Data_t>::m_graph (Node* branch, CMatrix<char>& image, std::stringstream& stream_buf,
                                          int line, int column, int a, int b) const {
    std::pair<int, int> pos;
    int horizontal_step = b + GAP;
    int vertical_step   = a + GAP;
    int left_1  = 0, left_2  = 0, left_total  = horizontal_step;
    int right_1 = 0, right_2 = 0, right_total = horizontal_step;
    int len;

    if (branch->left != nullptr) {
        left_1 = m_get_width(branch->left->left)  * horizontal_step;
        left_2 = m_get_width(branch->left->right) * horizontal_step;
        left_total += left_1 + left_2;
    } else {
        left_total = left_1 = left_2 = 0;
    }

    if (branch->right != nullptr) {
        right_1 = m_get_width(branch->right->left)  * horizontal_step;
        right_2 = m_get_width(branch->right->right) * horizontal_step;
        right_total += right_1 + right_2;
    } else {
        right_total = right_1 = right_2 = 0;
    }

    image.draw_frame (line, column + left_total, a, b); // (* 1)
    
    (* print_ptr_)(branch->key, branch->value);

    std::string buffer = stream_buf.str();
    stream_buf.str(std::string());

    pos.first  = line + 1;
    pos.second = column + left_total + 1;
    image.insert(buffer, pos.first, pos.second, a, b);

    if (branch->left != nullptr) {
        pos.first  = line + a + 2;
        pos.second = column + left_1 + b / 2 + 2;
        len = left_2 + horizontal_step - 1;

        image.draw_horizontal_line(pos.first, pos.second, len); // (* 2)
        image[pos.first][pos.second + len]   = VERTICAL_BAR;    // (* 3)
        image[pos.first + 1][pos.second - 1] = VERTICAL_BAR;    // (* 4)

        m_graph (branch->left, image, stream_buf,
                 line + vertical_step, column, a, b);
    }

    if (branch->right != nullptr) {
        pos.first  = line + a + 2;
        pos.second = column + left_total + b / 2 + 2;
        len = right_1 + horizontal_step - 1;

        image.draw_horizontal_line(pos.first, pos.second, len); // (* 5)
        image[pos.first][pos.second - 1]       = VERTICAL_BAR;  // (* 6)
        image[pos.first + 1][pos.second + len] = VERTICAL_BAR;  // (* 7)

        m_graph (branch->right, image, stream_buf,
                 line + vertical_step, column + left_total + horizontal_step, a, b);
    }
}

template <typename Key_t, typename Data_t>
int CBinaryTree<Key_t, Data_t>::m_get_width (Node* branch) const {
    if (branch == nullptr) return 0;

    int total = 1;
    if (branch->left  != nullptr) total += m_get_width (branch->left);
    if (branch->right != nullptr) total += m_get_width (branch->right);

    return total;
}
//!===========================================================================================

#undef ASSERT
#undef MAX2
#undef MAX3

/* BIN_TREE */
#endif

/*
                _____|_____
               |           |
               |           |
               |           |
               |___________|      
  *2 ->______________|_____________________________<- *5
*4  ->|              ^                             |<- *7
 _____|_____         |*3 && *6                _____|_____
|           |                                |           |
|           |                                |           |
|           |                                |           |
|___________|                                |___________|
                                     ______________|
                                    |
                               _____|_____
                              |           |
                              |           |
                              |           |
                              |___________|

           _____|_____     
       ^  |<--------->|
      a|  |     b     |
       ^  |           |    <- (* 1)
          |___________|    <- frame (3 x 11)

*/
