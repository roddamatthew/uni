all: part1 part2

part1:
	g++ -std=c++11 -o DistanceVector DistanceVector.cpp routingFunctions.cpp

part2:
	g++ -std=c++11 -o PoisonedReverse PoisonedReverse.cpp poisoningFunctions.cpp

test: part1
	./DistanceVector < a.txt
