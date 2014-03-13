#include "include/bencode2json.h"
#include "include/bencodeparser.h"

namespace link {

    std::string bencode2json(std::string bencodestr) {
        return bencode2json(bencodestr.c_str(), bencodestr.size());
    }

    std::string bencode2json(const char *bencodestr, int length) {
        bencode2json_parser parser(bencodestr, length);
        return parser.parse();
    }

}
