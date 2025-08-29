#pragma once
#include "Curve3D.h"
#include <cmath>
#include <stdexcept>

// 3D Helix along Z axis
class CURVES_API Helix : public Curve3D {
private:
	double r;
	double c;
public:
	Helix(double R, double C);

	Vec3 point(double t) const override;
	Vec3 derivative(double t) const override;

	double getR() const;
	double getC() const;
};