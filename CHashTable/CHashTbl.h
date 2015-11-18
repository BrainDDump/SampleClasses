template <typename Key_t, typename Data_t>
class CHashTbl {
	typedef size_t (* func_ptr)(Key_t);

	const size_t           TBL_SZ;
	CList<Key_t, Data_t>*  table_;
	const func_ptr         hash_function_;

	static size_t          s_cell;
public:
	CHashTbl (size_t table_size, func_ptr hash_function);
	~CHashTbl();

	bool   insert      (Key_t key, Data_t data);
	bool   remove      (Key_t key);
	void   clear       ();

	bool   set         (Key_t key, Data_t data);
	Data_t operator [] (Key_t key) const;

	bool   containes   (Key_t key) const;
	void   print       () const;
};
