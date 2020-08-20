#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
	Circle* C = new Circle(1, "Circle");
	Rectangle* R = new Rectangle(3,4);
	Triangle* T1 = new Triangle(1,2,2,1.5,"Valid");
	Triangle* T2 = new Triangle(1,4,8,5,"Invalid");
	vector <Shape*> shapes;

	shapes.push_back(C);
	shapes.push_back(R);
	shapes.push_back(T1);
	shapes.push_back(T2);

	for(int i = 0; i < shapes.size(); i++){
		std::cout << shapes.at(i) -> get_name() << " " << shapes.at(i) -> get_area() << " " << shapes.at(i) -> get_perimeter() << std::endl;
	}

	return 0;
}