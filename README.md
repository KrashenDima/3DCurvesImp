# 3DCurvesImp

Проект на C++, реализующий работу с 3D-кривыми: **окружность, эллипс и спираль (helix)**.  
Состоит из динамической библиотеки (`curveslib`) и консольного приложения (`curves_app`), которое демонстрирует её использование.

---

## ⚙️ Сборка

### Требования
- **CMake 3.15+**
- Компилятор C++17 (Visual Studio, GCC, Clang)

### Шаги
```yaml
# 1. Клонируем репозиторий
git clone https://github.com/username/3DCurvesImp.git
cd 3DCurvesImp

# 2. Генерация сборочной системы
cmake -S . -B build

# 3. Сборка
cmake --build build --config Release
```

После сборки будут получены:
build/Release/curveslib.dll (Windows) или libcurveslib.so (Linux)
build/Release/curves_app.exe — консольное приложение

## ▶️ Запуск
Пример запуска приложения:
```bash
./build/Release/curves_app
```

Программа:
1. Генерирует случайные кривые (окружности, эллипсы, спирали).
2. Выводит координаты точек и производных в заданной точке t.
3. Отбирает все окружности, сортирует их по радиусам.
4. Параллельно суммирует радиусы окружностей с помощью OpenMP.

## 📚 Пример кода (main.cpp)
```cpp
#include "Curve3D.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Helix.h"
#include "CurveParams.h"

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());

    CurveParams params;
    double t = M_PI / 4;

    auto curves = generateCurves(10, gen, params);
    printCurvesInfo(curves, t);

    auto circles = extractCircles(curves);
    std::sort(circles.begin(), circles.end(),
        [](auto& a, auto& b) { return a->getR() < b->getR(); });

    double totalRadius = sumRadii(circles);
    std::cout << "Total radii sum = " << totalRadius << std::endl;
}
```
