#include "Shape.h"
#include "Circle.h"
#include <string>
#include <cmath>

Circle :: Circle(int diameter, std::string name){
	Diameter = diameter;
	Radius = Diameter/2;
	Name = name;
	pi = 3.1415926;
}

double Circle :: get_area(){
	return pi * pow(Radius, 2);
}

double Circle :: get_perimeter(){
	return pi*Diameter;
}