run: Book.o Library.o main.o
	g++ Book.o Library.o main.o  -Wall -o run

Book.o: Book.cpp
	g++ -c Book.cpp

Library.o: Library.cpp
	g++ -c Library.cpp

main.o: main.cpp
	g++ -c main.cpp