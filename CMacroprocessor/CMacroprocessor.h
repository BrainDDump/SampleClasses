class CMacroprocessor {
//!---------------------< structs && constants >--------------------------
	struct Macro {
		std::string              name;
		std::vector<std::string> args;
		std::string              content;
	};

//!---------------------< spesial tokens >--------------------------------
	static const std::string DEFINE;
	static const std::string END_OF_FILE;

	static const std::string LEFT_BRACKET;
    static const std::string RIGHT_BRACKET;
	static const std::string COMMA;
	static const std::string ENDL;
	//static const std::string WHITESPACE;
//!---------------------< public methods >--------------------------------
public:
	CMacroprocessor  ();
	CMacroprocessor  (std::string input_file_name);
	~CMacroprocessor ();

	int load_file  (std::string input_file_name);
	int precompile (std::string output_file_name);
//!---------------------< private methods >-------------------------------
private:
//!---------------------< main methods >----------------------------------
	bool parse             ();
	bool preload_to_string ();
	bool write_to_file     (const char* file_name);

	bool  define_macro             (size_t& iterator);
	Macro create_macro_description (size_t& iterator);
	bool  insert_macro             (size_t& iterator);
	Macro get_from_macroList_      (std::string macro_name);
//!---------------------< help methods >----------------------------------
	int         get_file_size (const char* filename);
	std::string get_token     (size_t& iterator);
	std::string get_new_arg   (size_t& iterator, bool& args_end_flag);


	bool is_macro         (std::string token);
	bool is_special_token (std::string token);
//!---------------------< dump methods >----------------------------------
	void inputFileContent__dump ();
	void macroList__dump        ();
//!---------------------< private data >----------------------------------
private:
	std::string        inputFileContent_;
	std::string        outputFileContent_;
	std::vector<Macro> macroList_;
};
//!-----------------------------------------------------------------------