# 3DCurvesImp

A C++ project that implements 3D curves: **circle, ellipse, and helix**.  
It consists of a dynamic library (`curveslib`) and a console application (`curves_app`) that demonstrates its usage.

---

## ⚙️ Build Instructions

### Requirements
- **CMake 3.15+**
- C++17 compatible compiler (Visual Studio, GCC, Clang)

### Steps
# 1. Clone the repository
```bash
git clone https://github.com/username/3DCurvesImp.git
cd 3DCurvesImp
```

# 2. Generate build system
```bash
cmake -S . -B build
```

# 3. Build
```bash
cmake --build build --config Release
```

After building, you will get:
`build/Release/curveslib.dll (Windows)` or `libcurveslib.so (Linux)`
`build/Release/curves_app.exe` — console application

## ▶️ Run
Example of running the application:
```bash
./build/Release/curves_app
```

The program:
1. Generates random curves (circles, ellipses, helices).
2. Prints coordinates of points and derivatives at a given parameter `t`.
3. Extracts all circles and sorts them by radius.
4. Computes the total sum of circle radii in parallel using OpenMP.

## 📚 Example Code (main.cpp)
```cpp
#include "Curve3D.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Helix.h"
#include "CurveParams.h"

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
```
