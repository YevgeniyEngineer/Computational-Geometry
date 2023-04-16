#pragma once

#include <cmath>

constexpr double TOLERANCE = 1e-6;

static bool isEqualD(const double x, const double y)
{
    return std::fabs(x - y) < TOLERANCE;
}