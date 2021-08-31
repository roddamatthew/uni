all: compile test1

compile:
	g++ -std=c++11 -o main main.cpp

test1: compile
	./main < test1.txt > output1.txt
	cat output1.txt
	cat expected1.txt

test2: compile
	./main < test2.txt > output2.txt
	cat output2.txt
	cat expected2.txt

test3: compile
	./main < test3.txt > output3.txt
	cat output3.txt
	cat expected3.txt