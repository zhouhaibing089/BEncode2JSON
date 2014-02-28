#ifndef BENCODE_PARSER
#define BENCODE_PARSER

#include <string>
#include <stack>

namespace link {

	struct syntax_error;

	enum class parse_status {
		INIT,		// initialization status
		LIST,		// meet list => l
		DICT,		// meet dict => d
		STR,		// meet str => number
		INT,		// meet integer => i
		CONT 		// continue seeking words
	};

	class bencode2json_parser {
	public:
		// copy the str to another place
		bencode2json_parser(const char *str, int len);
		// parse work, it will return the result string.
		// syntax_error will be throwed if there is any error
		std::string parse();

		~bencode2json_parser();

	private:
		// the status stack
		std::stack<parse_status> status_stk;
		// source string with bencode format
		char *src = nullptr;
		// length of source
		int srclen;
	};

}

#endif