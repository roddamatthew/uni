#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle : public Shape
{
private:
	double Length;
	double Height;
public:
	Rectangle(double length, double height);
	double get_area();
	double get_perimeter();
};
#endif //RECTANGLE_H