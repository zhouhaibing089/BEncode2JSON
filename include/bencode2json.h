/*
 * This project is sereved as a utility for the link project.
 *
 * This file contains interfaces to convert a bencode string to
 * json string.
 */

#ifndef BENCODE_TO_JSON
#define BENCODE_TO_JSON
#include <string>

namespace link {

	// when we meet a syntax error
	struct syntax_error {};

	// These two methods may throw syntax_error exception
	std::string bencode2json(std::string bencodestr);
	std::string bencode2json(const char *bencodestr, int length);

}

#endif 