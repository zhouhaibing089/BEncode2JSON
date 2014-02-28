#include "include/bencode2json.h"
#include "include/bencodeparser.h"

namespace link {

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

	std::string bencode2json(std::string bencodestr) {
		return bencode2json(bencodestr.c_str(), bencodestr.size());
	}

	std::string bencode2json(const char *bencodestr, int length) {
		bencode2json_parser parser(bencodestr, length);
		return parser.parse();
	}

}
