#include "Helix.h"

Helix::Helix(double R, double C){
	if (R <= 0.0) {
		throw std::invalid_argument("Helix radius must be positive.");
	}
	r = R;
	c = C;
}

Vec3 Helix::point(double t) const {
	return { r * cos(t), r * sin(t), c * t };
}
Vec3 Helix::derivative(double t) const {
	return { -r * sin(t), r * cos(t), c };
}
double Helix::getR() const { return r; }
double Helix::getC() const { return c; }