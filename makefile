final: main.o
	g++ -o plagiarismCatcher main.o
main: main.cpp HashTable.h
	g++ -c main.cpp

