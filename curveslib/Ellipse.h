#pragma once
#include "Curve3D.h"
#include <cmath>
#include <stdexcept>

// Ellipse in XY plane
class CURVES_API Ellipse : public Curve3D {
private:
	double a;
	double b;
public:
	Ellipse(double A, double B);

	Vec3 point(double t) const override;
	Vec3 derivative(double t) const override;

	double getA() const;
	double getB() const;
};