test: testA.cpp alist.o
	g++ testA.cpp -o alist.o -o test
listmgt: listmgt.cpp alist.o alist.h
	g++ listmgt.cpp alist.o -o listmgt
alist.o: alist.cpp alist.h
	g++ -c alist.cpp -o alist.o