//!{==========================================================================================
//! @file    CBinaryTree.h
//! @date    2015-09-18
//! @author  Dubovitskiy Kirill <kirill2003de@gmail.com>
//!
//! Declaration of the template CBinaryTree class.
//! 
//!}==========================================================================================
template <typename Key_t, typename Data_t>
class CBinaryTree {
//!---------------------< tydefs, structs, consts, error handling >---------------------------
    typedef void (* print_ptr_t)(const Key_t&, const Data_t&);

    struct Node {
        Key_t  key;
        Data_t value;

        Node*  right;
        Node*  left;
    };

    enum err_t {
        NO_ERR,  NOT_FOUND, PRINT_ERR,
        PTR_ERR, UNKNOWN_ERR
    };
//!---------------------< class members >-----------------------------------------------------
    Node*       root_;
    Node*       active_branch_;
    int*        error_;

    print_ptr_t print_ptr_;
//!---------------------< class methods >-----------------------------------------------------
public:
//!---------------------< constructers && destructer >----------------------------------------
    CBinaryTree ();
    CBinaryTree (std::vector<std::pair<Key_t, Data_t>>);
    CBinaryTree (const CBinaryTree& other);
    CBinaryTree (CBinaryTree& other, Key_t key);
    ~CBinaryTree();
//!---------------------< additional setup >--------------------------------------------------
    void set_print   (print_ptr_t print_ptr);
    void load_vector (std::vector<std::pair<Key_t, Data_t>>);
//!---------------------< #0 depth methods >--------------------------------------------------
    bool insert (Key_t key, Data_t value);
    void erase  ();
    bool find  (Key_t key);
    void begin ();
    Data_t current_value() const;
    Data_t get   (Key_t key) const;
    //bool delete_el    (Key_t key);
    bool delete_branch(Key_t key);
    //void merge   (const CBinaryTree& ohter);
    //void balance ();
    int   depth() const;

    void  print        () const;
    void  print_branch (Key_t key) const;

    void  graph (size_t a, size_t b) const;
private:
//!---------------------< #1 depth methods >--------------------------------------------------
    bool  m_insert        (Node* branch, Key_t key, Data_t value);
    Node* m_create_node   (Key_t key, Data_t value) const;
    Node* m_clone_branch  (Node* sample_branch) const;
    void  m_delete_branch (Node* branch) const;
    bool  m_find  (Node* branch, Key_t key);
    int   m_depth (Node* branch, int depth) const;
    void  m_print (Node* branch) const;
    void  m_graph (Node* branch, CMatrix<char>& image, std::stringstream& stream_buf,
                   int line, int column, int a, int b) const;
    int   m_get_width (Node* branch) const;
};
//!===========================================================================================

