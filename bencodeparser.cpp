#include "include/bencodeparser.h"
#include <cstring>

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

    std::string bencode2json_parser::int_parse(int begin) {
        for(int i = begin + 1; i < len; ++i) {
            if (src[i] == 'e') {
                // str[begin] = 'i', so i - begin bytes is enough
                int size = i - begin;
                char *res = new char[size];
                memcpy(res, src + begin + 1, size - 1);
                res[size] = 0;
                std::string s {res};
                delete [] res;
                pos = i;
                return s;
            }
        }
        throw syntax_error{};
    }


    std::string bencode2json_parser::str_parse(int begin) {
        for (int i = begin; i < len; ++i) {
            if (src[i] == ':') {
                int cnt = str2int(src + begin, i - begin);
                // TODO: some out of bounds exception check may be needed
                char *res = new char[cnt + 1];
                memcpy(res, src + i + 1, cnt);
                res[cnt] = 0;
                std::string s {res};
                delete [] res;
                pos = i + cnt;
                return s;
            }
        }
        throw syntax_error{};
    }

    std::string bencode2json_parser::list_parse(int begin) {
        std::string s = "[";
        for(int i = begin + 1; i < len; ++i) {
            // The final end marker
            if (src[i] == 'e') {
                int length = s.size();
                // if we get an empty list
                if (length == 1) {
                    s += "]";
                } else {
                    s[length - 1] = ']';
                }
                pos = i;
                return s;
            }
            action_t act = get_action(src[i]);
            // so we get an element of a list
            std::string tmp = (this->*act)(i);
            if(tmp[0] == '{' || tmp[0] == '[') {
                s += (tmp + ",");
            } else {
                s += ("\"" + tmp + "\"" + ",");
            }
            i = pos;
        }
        throw syntax_error{};
    }

    std::string bencode2json_parser::dict_parse(int begin) {
        std::string s = "{";
        ele_type_t type = ele_type_t::KEY;            
        for (int i = begin + 1; i < len; ++i) {
            if (src[i] == 'e') {
                int length = s.size();
                if (length == 1) {
                    s += "}";
                } else {
                    s[length - 1] = '}';
                }
                pos = i;
                return s;
            }
            action_t act = get_action(src[i]);
            std::string tmp = (this->*act)(i);
            if(tmp[0] == '{' || tmp[0] == '[') {
                s += tmp;
            } else {
                s += ("\"" + tmp + "\"");
            }
            // then colon or comma
            if (type == ele_type_t::KEY) {
                s += ":";
                type == ele_type_t::VALUE;
            } else {
                s += ",";
                type == ele_type_t::KEY;
            }
            i = pos;
        }
        throw syntax_error{};
    }

    bencode2json_parser::action_t bencode2json_parser::get_action(char c) const {
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
        action_t act = get_action(src[0]);
        return (this->*act)(0);
    }
}
