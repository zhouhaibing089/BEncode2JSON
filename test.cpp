#include <iostream>
#include <string>
#include "include/bencode2json.h"

int main() {
	std::string s = "d4:spam4:eggse";
	std::cout << link::bencode2json(s) << std::endl;
	return 0;
}