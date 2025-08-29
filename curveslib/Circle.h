#pragma once
#include "Curve3D.h"
#include <cmath>
#include <stdexcept>

// Circle in XY plane
class CURVES_API Circle : public Curve3D {
private:
	double r;
public:
	Circle(double R);

	Vec3 point(double t) const override;
	Vec3 derivative(double t) const override;

	double getR() const;
};
