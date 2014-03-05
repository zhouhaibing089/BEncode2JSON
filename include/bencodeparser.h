#ifndef BENCODE_PARSER
#define BENCODE_PARSER

#include <string>
#include <map>

namespace link {

	struct syntax_error;

	class bencode2json_parser {
	public:
		// copy the str to another place
		bencode2json_parser(const char *str, int len);
		// parse work, it will return the result string.
		// syntax_error will be throwed if there is any error
		std::string parse();

		~bencode2json_parser();

	private:
		// source string with bencode format
		char *src = nullptr;
		// length of source
		int len;
		// parse position
		int pos = 0;

	private:
		
		typedef std::string (bencode2json_parser::*action)(int, int);
		action action_map(char c) const;

		std::string int_parse(int begin, int end);
		std::string str_parse(int begin, int end);
		std::string list_parse(int begin, int end);
		std::string dict_parse(int begin, int end);
	};

}

#endif