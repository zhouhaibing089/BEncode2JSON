BUILD = build

bencode2json.o: bencode2json.cpp 
	g++ -std=c++11 -g -c bencode2json.cpp -o ${BUILD}/bencode2json.o

bencodeparser.o: bencodeparser.cpp
	g++ -std=c++11 -g -c bencodeparser.cpp -o ${BUILD}/bencodeparser.o

test: test.cpp bencode2json.o bencodeparser.o
	g++ -std=c++11 -g -c test.cpp -o ${BUILD}/test.o
	g++ -std=c++11 ${BUILD}/*.o -o ${BUILD}/test

clean:
	rm -f build/*