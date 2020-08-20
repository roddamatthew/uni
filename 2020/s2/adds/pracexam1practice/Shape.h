#ifndef SHAPE_H
#define SHAPE_H

#include <string>

class Shape
{
protected:
std::string Name;

public:
	Shape();
	Shape(std::string name);
	virtual double get_area();
	virtual double get_perimeter();
	std::string get_name();
};
#endif //SHAPE_H
