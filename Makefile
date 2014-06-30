BUILD = build

bencode2json.o: bencode2json.cpp bencodeparser.o
	g++ -std=c++11 -g -c bencode2json.cpp -o ${BUILD}/bencode2json.o

bencodeparser.o: bencodeparser.cpp
	g++ -std=c++11 -g -c bencodeparser.cpp -o ${BUILD}/bencodeparser.o

libb2j.a: bencode2json.o bencodeparser.o
	ar crv libb2j.a ${BUILD}/bencode2json.o ${BUILD}/bencodeparser.o
	ranlib libb2j.a

test: test.cpp libb2j.a
	g++ -std=c++11 test.cpp libb2j.a -o test

clean:
	rm -f build/*
	rm -f libb2j.a test

