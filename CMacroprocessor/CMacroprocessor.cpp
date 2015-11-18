#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <fstream>
#include <assert.h>
#include <boost/algorithm/string.hpp>

#include "CMacroprocessor.h"

//!---------------------< initialization of constants >-------------------
const std::string CMacroprocessor::DEFINE        = "#define";
const std::string CMacroprocessor::END_OF_FILE   = "EOF";

const std::string CMacroprocessor::LEFT_BRACKET  = "(";
const std::string CMacroprocessor::RIGHT_BRACKET = ")";
const std::string CMacroprocessor::COMMA         = ",";
const std::string CMacroprocessor::ENDL          = "\n";

//!---------------------< public methods >--------------------------------
CMacroprocessor::CMacroprocessor() {
	/* --- // --- */
}

CMacroprocessor::CMacroprocessor(std::string input_file_name) {
	load_file(input_file_name);
}

CMacroprocessor::~CMacroprocessor() {
	/* --- // --- */
}

int CMacroprocessor::load_file(std::string input_file_name) {
	inputFileContent_.clear();
	int file_size = get_file_size(input_file_name.c_str());
	if (file_size < 0) {
		printf("file size error!\n");
		assert(false);
	}
	inputFileContent_.reserve(file_size);

	std::ifstream file (input_file_name, std::ios::binary);

	inputFileContent_.assign(std::istreambuf_iterator<char>(file),
						 std::istreambuf_iterator<char>());

	return 0;
}

int CMacroprocessor::precompile(std::string output_file_name) {
	parse();
	preload_to_string();
	write_to_file(output_file_name.c_str());

	return 0;
}

//!-----------------------------------------------------------------------
//!---------------------< private methods >-------------------------------
//!-----------------------------------------------------------------------
//!---------------------< main methods >----------------------------------

bool CMacroprocessor::parse() {
	const char to_replace[] = { 92, 10 }; // = { '\', '\n' };
	boost::replace_all(inputFileContent_, to_replace, "  ");

	size_t iterator = 0;
	bool   flag     = true;
	while (iterator != std::string::npos) {
		iterator = inputFileContent_.find(DEFINE, iterator);
		if (iterator == std::string::npos) {
			break;
		} else {
			define_macro(iterator);
		}
	}

	inputFileContent__dump();
	macroList__dump();

	return 0;
}

bool CMacroprocessor::preload_to_string() {
	size_t prev_iterator = 0;
	size_t curr_iterator = 0;
	size_t len           = 0;

	std::string token;

	while (true) {
		token = get_token(curr_iterator);

		if (token == DEFINE) {
			while (inputFileContent_[curr_iterator++] != '\n');
		} else if (is_macro(token)) {
			curr_iterator = prev_iterator;
			insert_macro(curr_iterator);
		} else if (token != END_OF_FILE) {
			len = curr_iterator - prev_iterator;
			outputFileContent_ += inputFileContent_.substr(prev_iterator, len);
		} else {
			break;
		}

		prev_iterator = curr_iterator;
	}

	return true;
}

bool CMacroprocessor::write_to_file(const char* file_name) {
	std::ofstream ofFile (file_name, std::ios::out);
	ofFile << outputFileContent_;

	ofFile.close();

	return true;
}

//!-----------------------------------------------------------------------

bool CMacroprocessor::define_macro(size_t& iterator) {
	size_t end_of_macro;
	size_t macro_len;

	iterator += DEFINE.length();

	Macro new_macro = create_macro_description(iterator);
	end_of_macro    = inputFileContent_.find("\n", iterator);
	macro_len       = end_of_macro - iterator;
	new_macro.content.assign(inputFileContent_, iterator, macro_len);

	macroList_.push_back(new_macro);

	return true;
}

CMacroprocessor::Macro CMacroprocessor::create_macro_description(size_t& iterator) {
	std::string new_arg;
	bool        args_end_flag = false;

	Macro macro;
	macro.name = get_token(iterator);

	if (inputFileContent_.substr(iterator, 1) == LEFT_BRACKET) {
		iterator++;

		do {
			new_arg = get_new_arg(iterator, args_end_flag);
			macro.args.push_back(new_arg);
		} while (args_end_flag != true);
	}

	return macro;
}

bool CMacroprocessor::insert_macro(size_t& iterator) {
	std::string buffer;
	Macro macro_in_code = create_macro_description(iterator);

	Macro macro_definition = get_from_macroList_(macro_in_code.name);

	if (macro_in_code.args.size() != macro_definition.args.size()) {
		std::cout << "macro_in_code.name: " << macro_in_code.name << "\n";
		printf("wrong quantity of macro arguments!\n");
		assert(false);
	} else {
		buffer = macro_definition.content;
	}

	for (int i = 0; i < macro_definition.args.size(); ++i) {
		boost::replace_all(buffer, macro_definition.args[i], macro_in_code.args[i]);
	}

	outputFileContent_ += buffer;

	return true;
}

CMacroprocessor::Macro CMacroprocessor::get_from_macroList_(std::string macro_name) {
	for (int i = 0; i < macroList_.size(); ++i) {
		if (macroList_[i].name == macro_name) return macroList_[i];
	}

	Macro empty_macro;
	return empty_macro;
}


//!---------------------< help methods >----------------------------------
int CMacroprocessor::get_file_size(const char* filename) {
	std::ifstream file;
	int size;

	file.open(filename, std::ios::ate | std::ios::in);
	if (file.is_open()) {
		size = file.tellg();
		file.close();
		return size;
	}

	assert(false);
	return -1;
}

std::string CMacroprocessor::get_token(size_t& iterator) {
	size_t token_begin = inputFileContent_.find_first_not_of(" \n", iterator);

	switch (inputFileContent_[token_begin]) {
	case ('('): { iterator = token_begin + 1; return LEFT_BRACKET;  }
	case (','): { iterator = token_begin + 1; return COMMA;         }
	case (')'): { iterator = token_begin + 1; return RIGHT_BRACKET; }
	}

	size_t token_ended = inputFileContent_.find_first_of(" (,)\n", token_begin);
	size_t token_len = token_ended - token_begin;

	if (token_ended == std::string::npos) {
		return END_OF_FILE;
	}

	std::string new_token = inputFileContent_.substr(token_begin, token_len);

	iterator  = token_ended;
	iterator  = inputFileContent_.find_first_not_of(' ', iterator);

	return new_token;
}

std::string CMacroprocessor::get_new_arg(size_t& iterator, bool& args_end_flag) {
	iterator = inputFileContent_.find_first_not_of(' ', iterator);

	std::string token_buf;
	std::string new_arg;
	size_t      arg_begin       = iterator;
	int         brackets_opened = 0;

	while (true) {
		token_buf = get_token(iterator);

		if (token_buf == LEFT_BRACKET) {
			brackets_opened++;
		} else if (token_buf == COMMA && brackets_opened == 0) {
			break;
		} else if (token_buf == RIGHT_BRACKET) {
			brackets_opened--;
			if (brackets_opened < 0) {
				args_end_flag = true;
				break;
			}
		}

		new_arg += token_buf;
	}

	return new_arg;
}

bool CMacroprocessor::is_macro(std::string token) {
	for (int i = 0; i < macroList_.size(); ++i) {
		if (macroList_[i].name == token) return true;
	}

	return false;
}

bool CMacroprocessor::is_special_token(std::string token) {
	if (token == LEFT_BRACKET || token == RIGHT_BRACKET ||
		token == COMMA        || token == ENDL) {
		return true;
	}

	return false;
}

//!-----------------------------------------------------------------------
//!---------------------< dump methods >----------------------------------

void CMacroprocessor::inputFileContent__dump() {
    std::cout << "## inputFileContent__dump        ##\n";
	std::cout << inputFileContent_;
	std::cout << "## end of inputFileContent__dump ##\n";
}

void CMacroprocessor::macroList__dump() {
	std::cout << "\n## macroList_ dump        ##\n";
	for (int i = 0; i < macroList_.size(); ++i) {
		std::cout << "Macro"   << i << " :";
		std::cout << std::endl << macroList_[i].name;
		std::cout << std::endl << "arguments: ";
		for (int j = 0; j < macroList_[i].args.size(); ++j) {
            std::cout << macroList_[i].args[j] << " ";
        }
        std::cout << std::endl << macroList_[i].content << std::endl;
	}
	std::cout << "\n## end of macroList_ dump ##\n\n";
}
