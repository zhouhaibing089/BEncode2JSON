#include <iostream>
#include <string>
#include "include/bencode2json.h"

int main() {
	std::string s = "4:spam";
	// Here I will expect it to output {"spam": "eggs"}
	std::cout << link::bencode2json(s) << std::endl;
	return 0;
}