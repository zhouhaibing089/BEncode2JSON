#include "include/bencodeparser.h"
#include <cstring>

namespace link {

	// helper method

	bencode2json_parser::bencode2json_parser(const char *str, int len) : srclen(len) {
		src = new char[len + 1];
		memcpy(src, str, len);
		src[len] = 0;
		// INIT status
		status_stk.push(parse_status::INIT);
	}

	bencode2json_parser::~bencode2json_parser() {
		delete [] src;
	}

	// Here the action is complicated:
	// When the status is 
	//	INIT:
	// 		l: The whole bencode string is a list, add [ 	=> LIST
	//		i: It is only a number, read until reach 'e'	=> INT
	// 		number: It is a string, adjust pointer			=> STR
	//		etc.: Illegal									=> syntax_error
	// 	LIST:
	//		the same as INIT
	//	DICT:	
	//		the same as INIT
	//		: : We seek one part
	//		, : The separator
	//	
	std::string bencode2json_parser::parse() {
		return "HelloWorld";
	}
}