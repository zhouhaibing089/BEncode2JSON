#include "include/bencodeparser.h"
#include <cstring>
#include <map>

namespace link {

	struct syntax_error {};

	// convert a c string to int
	int str2int(const char *cstr, int lenth) {
		int result = 0;
		int base = 1;
		while (--lenth >= 0) {
			result += (cstr[lenth] - '0') * base;
			base *= 10;
		}
		return result;
	}

	// helper method
	std::string bencode2json_parser::int_parse(int begin, int end) {
		return "1";
	}


	std::string bencode2json_parser::str_parse(int begin, int end) {
		for (int i = begin; i < end; ++i) {
			if (src[i] == ':') {
				int cnt = str2int(src + begin, i - begin);
				// TODO: some out of bounds exception check may be needed
				char *res = new char[cnt + 1];
				memcpy(res, src + i + 1, cnt);
				res[cnt] = 0;
				std::string s {res};
				delete [] res;
				pos = i + cnt + 1;
				return s;
			}
		}
		throw syntax_error{};
		
	}

	std::string bencode2json_parser::list_parse(int begin, int end) {
		std::string s = "[";
		for(int i = begin + 1; i < end; ++i) {
			// invoke the next action method
			if (src[i] == 'e') {

			}
		}
		return "1";
	}

	std::string bencode2json_parser::dict_parse(int begin, int end) {
		return "1";
	}

	bencode2json_parser::action bencode2json_parser::action_map(char c) const {
		switch(c) {
		case 'i':
			return &bencode2json_parser::int_parse;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return &bencode2json_parser::str_parse;
		case 'l':
			return &bencode2json_parser::list_parse;
		case 'd':
			return &bencode2json_parser::dict_parse;
		}
	}

	

	bencode2json_parser::bencode2json_parser(const char *str, int len) : len(len) {
		src = new char[len + 1];
		memcpy(src, str, len);
		src[len] = 0;
	}

	bencode2json_parser::~bencode2json_parser() {
		delete [] src;
	}

	std::string bencode2json_parser::parse() {
		int pos = 0;
		action act = action_map(src[0]);
		return (this->*act)(0, len);
	}
}