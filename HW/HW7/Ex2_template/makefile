# Type:
#	make
#	./test
# to run the test

test: test.cpp trie.o
	g++ -g test.cpp -o test
trie.o: trie.cpp trie.h
	g++ -g -c trie.cpp -o trie.o

clean:
	rm trie.o
	rm test
