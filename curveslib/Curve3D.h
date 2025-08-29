#pragma once
#include "Vec3.h"

#ifdef CURVESLIB_EXPORTS 
#define CURVES_API __declspec(dllexport)
#else
#define CURVES_API __declspec(dllimport)
#endif

// Abstract base class for 3D curves
class CURVES_API Curve3D {
public:
	virtual ~Curve3D() = default;

	virtual Vec3 point(double t) const = 0;
	virtual Vec3 derivative(double t) const = 0;
};

