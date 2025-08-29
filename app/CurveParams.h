#pragma once

// Curve parameters for generation
struct CurveParams {
    std::pair<double, double> rangeA {7.0, 10.0}; // semi-major axis range
    std::pair<double, double> rangeB {1.0, 5.0}; // semi-minor axis range
    std::pair<double, double> rangeR {0.5, 5.0}; // radius range
    std::pair<double, double> rangeC {1.0, 5.0}; // helix step range
};