##Bencode2json

This library is going to serve as a ultility for the project [Link](https://github.com/zhouhaibing089/link)

###How to build

```bash
make libb2j.a
```

###How to use

Here is the code in the file `test.cpp`

```cpp
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

```

Just as you see, the interface is very simple. When you open the included file `include/bencode2json.h`, you see the interface there:

```cpp
namespace link {
	// exception
	struct syntax_error;

	// convert functions
	std::string bencode2json(std::string bencodestr);
	std::string bencode2json(const char *bencodestr, int length);
}
```

So you see, a really simple interface and a really simple project.
