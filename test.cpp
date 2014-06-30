#include <iostream>
#include <string>
#include "include/bencode2json.h"

int main() {
    std::string s;
    std::cin >> s;
    try {
    	std::cout << link::bencode2json(s) << std::endl;
	} catch (link::syntax_error e) {
		std::cout << "Syntax Error" << std::endl;
	}
    return 0;
}
