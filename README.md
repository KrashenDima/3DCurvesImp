# 3DCurvesImp

A C++ project that implements 3D curves: **circle, ellipse, and helix**.  
It consists of a dynamic library (`curveslib`) and a console application (`curvesapp`) that demonstrates its usage.

---

## ⚙️ Build Instructions

### Requirements
- **CMake 3.15+**
- C++17 compatible compiler (Visual Studio, GCC, Clang)

### Steps
1. Clone the repository
```bash
git clone https://github.com/KrashenDima/3DCurvesImp.git
cd 3DCurvesImp
```

2. Generate build system
```bash
cmake -S . -B build
```

3. Build
```bash
cmake --build build --config Release
```

After building, you will get:
`build/Release/curveslib.dll (Windows)` or `libcurveslib.so (Linux)`
`build/Release/curvesapp.exe` — console application

## ▶️ Run
Example of running the application:
```bash
cd build\app\Release
curvesapp.exe
```

The program:
1. Generates `10` random curves (circles, ellipses, helices).
2. Prints coordinates of points and derivatives at a given parameter `t=PI/4`.
3. Extracts all circles and sorts them by radius.
4. Computes the total sum of circle radii in parallel using OpenMP.

## 📚 Example Code (main.cpp)
```cpp
#include "Curve3D.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Helix.h"
#include "CurveParams.h"

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

int main() {

	std::random_device rd;
	std::mt19937 gen(rd());

	CurveParams params;
	auto curves = generateCurves(10, gen, params);

	return 0;
}
```
