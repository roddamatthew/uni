#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"
#include <string>

class Circle : public Shape
{
private:
	double Diameter;
	double Radius;
	double pi;
public:
	Circle(int diameter, std::string name);
	double get_area();
	double get_perimeter();
};
#endif //CIRCLE_H