#include "Ellipse.h"

Ellipse::Ellipse(double A, double B) {
	if (A <= 0.0 || B <= 0.0) {
		throw std::invalid_argument("Ellipse axes must be positive.");
	}
	a = A;
	b = B;
}
Vec3 Ellipse::point(double t) const {
	return { a * cos(t), b * sin(t), 0.0 };
}
Vec3 Ellipse::derivative(double t) const {
	return { -a * sin(t), b * cos(t), 0.0 };
}
double Ellipse::getA() const { return a; }
double Ellipse::getB() const { return b; }