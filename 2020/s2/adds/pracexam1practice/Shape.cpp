#include "Shape.h"
#include <string>

Shape :: Shape(){
	Name = "?";
}

Shape :: Shape(std::string name){
	Name = name;
}

double Shape :: get_area(){
	return 0.0;
}

double Shape :: get_perimeter(){
	return 0;
}

std::string Shape :: get_name(){
	return Name;
}