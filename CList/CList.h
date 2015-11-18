template <typename Key_t, typename Data_t>
class CList
{
	struct Node {
		Key_t  key;
		Data_t data;

		Node*  next;
	};

	Node* head_;
public:
	CList ();
	~CList();

	bool insert (Key_t key, Data_t data);
	bool remove (Key_t key);
	void clear  ();

	Data_t operator[] (Key_t key) const;
	bool   set        (Key_t key, Data_t data);

	bool containes (Key_t key) const;
	void print     () const;
};
