#include "Circle.h"

Circle::Circle(double R){
	if (R <= 0.0) {
		throw std::invalid_argument("Circle radius must be positive.");
	}
	r = R;
}
Vec3 Circle::point(double t) const {
	return { r * cos(t), r * sin(t), 0.0 };
}
Vec3 Circle::derivative(double t) const {
	return { -r * sin(t), r * cos(t), 0.0 };
}
double Circle::getR() const { return r; }