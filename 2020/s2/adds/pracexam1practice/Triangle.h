#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle : public Shape
{
private:
	int Base;
	int Side1;
	int Side2;
	double Height;
	bool Invalid;
public:
	Triangle(int base, int side1, int side2, double height, std::string name);
	double get_perimeter();
	double get_area();
};
#endif //TRIANGLE_H