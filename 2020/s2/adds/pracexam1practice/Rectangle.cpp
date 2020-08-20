#include "Shape.h"
#include "Rectangle.h"

Rectangle :: Rectangle(double length, double height){
	Length = length;
	Height = height;
	Name = "Rectangle";
}

double Rectangle :: get_area(){
	return Length * Height;
}

double Rectangle :: get_perimeter(){
	return Length * 2 + Height * 2;
}