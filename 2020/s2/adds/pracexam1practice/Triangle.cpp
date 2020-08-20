#include "Shape.h"
#include "Triangle.h"

#include <iostream>

Triangle :: Triangle(int base, int side1, int side2, double height, std::string name){
	Name = name;
	Base = base;
	Side1 = side1;
	Side2 = side2;
	Height = height;

	if(Base + Side1 < Side2){
		Invalid = true;
		std::cout << "Invalid Sides for constructing triangle" << std::endl;
	}else if(Side1 + Side2 < Base){
		Invalid = true;
		std::cout << "Invalid Sides for constructing triangle" << std::endl;
	}else if(Base + Side2 < Side1){
		Invalid = true;
		std::cout << "Invalid Sides for constructing triangle" << std::endl;
	}else{
		Invalid = false;
	}
}

double Triangle :: get_perimeter(){
	if(Invalid == true){
		return 0.0;
	}else{
		return Base + Side1 + Side2;
	}
}

double Triangle :: get_area(){
	if(Invalid == true){
		return 0.0;
	}else{
		return Base * Height * 0.5;
	}
}