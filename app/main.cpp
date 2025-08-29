#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <memory>
#include <omp.h>


#include "Curve3D.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Helix.h"
#include "CurveParams.h"

#define M_PI 3.14159265358979323846


enum class CurveType { Circle, Ellipse, Helix };

// Secure parameter generator
double safeRandom(std::mt19937& gen, std::pair<double, double> range) {
	if (range.first <= 0.0 || range.second <= 0.0 || range.first > range.second) {
		throw std::invalid_argument("Invalid parameter range!");
	}
	std::uniform_real_distribution<double> dist(range.first, range.second);
	return dist(gen);
}

// Generating a random curve
std::shared_ptr<Curve3D> generateRandomCurve(std::mt19937& gen, const CurveParams& params)
{
	std::uniform_int_distribution<int> typeDist(0, 2);
	CurveType type = static_cast<CurveType>(typeDist(gen));

	switch (type) {
	case CurveType::Circle:
		return std::make_shared<Circle>(safeRandom(gen, params.rangeR));
	case CurveType::Ellipse:
		return std::make_shared<Ellipse>(safeRandom(gen, params.rangeA),
			safeRandom(gen, params.rangeB));
	case CurveType::Helix:
		return std::make_shared<Helix>(safeRandom(gen, params.rangeR),
			safeRandom(gen, params.rangeC));
	}
	return nullptr;
}

// Generate a curve container
std::vector<std::shared_ptr<Curve3D>> generateCurves(size_t N, std::mt19937& gen, const CurveParams& params)
{
	std::vector<std::shared_ptr<Curve3D>> curves;
	curves.reserve(N);

	while (curves.size() < N) {
		try {
			curves.push_back(generateRandomCurve(gen, params));
		}
		catch (const std::invalid_argument& e) {
			std::cerr << e.what() << "\n\n";
			break;
		}
	}

	return curves;
}

// Output of information at point t
void printCurvesInfo(const std::vector<std::shared_ptr<Curve3D>>& curves, double t) {
	for (size_t i = 0; i < curves.size(); i++) {
		Vec3 p = curves[i]->point(t);
		Vec3 d = curves[i]->derivative(t);
		std::cout << "Curve" << i + 1 << ": ("
			<< p.x << ", " << p.y << ", " << p.z << "), ("
			<< d.x << ", " << d.y << ", " << d.z << ")\n";
	}
	std::cout << std::endl;
}

// Extract only circles from a curve container
std::vector<std::shared_ptr<Circle>> extractCircles(const std::vector<std::shared_ptr<Curve3D>>& curves) {
	std::vector<std::shared_ptr<Circle>> circles;
	for (auto& c : curves) {
		if (auto circ = std::dynamic_pointer_cast<Circle>(c)) 
			circles.push_back(circ);
	}
	return circles;
}

// Parallel summation of circle radii
double sumRadii(const std::vector<std::shared_ptr<Circle>>& circles) {
	double total = 0.0;
	long long n = static_cast<long long>(circles.size());
	#pragma omp parallel for reduction(+:total)
	for (long long i = 0; i < n; ++i) {
		total += circles[i]->getR();
	}
	return total;
}


int main() {

	std::random_device rd;
	std::mt19937 gen(rd());

	CurveParams good_params;
	//CurveParams bad_params{ {-2.0, 2.0}, {-2.0, 2.0}, {-2.0, 2.0} };
	
	double t = M_PI / 4;

	auto curves = generateCurves(10, gen, good_params);
	printCurvesInfo(curves, t);

	/*auto curves2 = generateCurves(10, gen, bad_params);
	printCurvesInfo(curves2, t);*/

	auto circles = extractCircles(curves);

	std::sort(begin(circles), end(circles),
		[](const std::shared_ptr<Circle>& a, const std::shared_ptr<Circle>& b) {
			return a->getR() < b->getR(); });
	
	double totalRadius = sumRadii(circles);
	
	for (size_t i = 0; i < circles.size(); ++i) {
		std::cout << "Circle" << i + 1 << ": r = " <<
			circles[i]->getR() << std::endl;
	}

	std::cout << "Total sum of radii: " << totalRadius << std::endl;

	return 0;
}