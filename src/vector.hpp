#pragma once

#include "core.h"

#include <array>
#include <cstdint>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <type_traits>

namespace geom
{
constexpr size_t DIM2 = 2;
constexpr size_t DIM3 = 3;

constexpr size_t X = 0;
constexpr size_t Y = 1;
constexpr size_t Z = 2;

template <typename Type, size_t Dimension = DIM3> class Vector
{
    static_assert(std::is_arithmetic_type<Type>, "Vector type can only be floating point or integer type!");
    static_assert(Dimension >= DIM2, "Vector dimension must have at least 2 dimensions!");

    using ArrayType = std::array<Type, Dimension>;
    using VectorType = Vector<Type, Dimension>;

  public:
    Vector() = default;
    Vector(const ArrayType &coords) : coords_(coords){};
    Vector(const Type x, const Type y, const Type z) : coords_{x, y, z} {};
    Vector(const Type x, const Type y) : coords_{x, y} {};

    const ArrayType &coords() const
    {
        return coords_;
    }

    const Type operator[](const size_t i) const
    {
        return coords_.at(i);
    }

    bool operator==(const VectorType &other) const
    {
        for (size_t i = 0; i < coords_.size(); ++i)
        {
            if (!isEqualD(coords_[i], other.coords()[i]))
            {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const VectorType &other) const
    {
        return !(*this == other);
    }

    bool operator+(const VectorType &other)
    {
        ArrayType temp_array;
        for (size_t i = 0; i < coords_.size(); ++i)
        {
            temp_array[i] = coords_[i] + other.coords()[i];
        }
        return VectorType{temp_array};
    }

    bool operator-(const VectorType &other)
    {
        ArrayType temp_array;
        for (size_t i = 0; i < coords_.size(); ++i)
        {
            temp_array[i] = coords_[i] - other.coords()[i];
        }
        return VectorType{temp_array};
    }

    bool operator<(const VectorType &other) const
    {
        for (size_t i = 0; i < Dimension; ++i)
        {
            if (coords_[i] < other.coords()[i])
            {
                return true;
            }
            else if (coords_[i] > other.coords()[i])
            {
                return false;
            }
        }
        return false;
    }

    bool operator>(const VectorType &other) const
    {
        for (size_t i = 0; i < Dimension; ++i)
        {
            if (coords_[i] > other.coords()[i])
            {
                return true;
            }
            else if (coords_[i] < other.coords()[i])
            {
                return false;
            }
        }
        return false;
    }

    void assign(const size_t dim, const Type value)
    {
        coords_.at(dim) = value;
    }

    friend float dotProduct(const Vector<Type, Dimension> &v1, const Vector<Type, Dimension> &v2);

  private:
    ArrayType coords_;
};

template <typename Type, size_t Dimension = DIM3>
float dotProduct(const Vector<Type, Dimension> &v1, const Vector<Type, Dimension> &v2)
{
    float dot_product = 0.0f;
    for (size_t i = 0; i < Dimension; ++i)
    {
        dot_product += static_cast<float>(v1[i] * v2[j]);
    }
    return dot_product;
}

using Vector2f = Vector<float, DIM2>;
using Vector3f = Vector<float, DIM3>;

float crossProduct2D(const Vector2f &v1, const Vector2f &v2)
{
    return v1[X] * v2[Y] - v1[Y] * v2[X];
}

Vector3f crossProduct3D(const Vector3f &v1, const Vector3f &v2)
{
    const float x = v1[Y] * v2[Z] - v1[Z] * v2[Y];
    const float y = -(v1[X] * v2[Z] - v1[Z] * v2[X]);
    const float z = v1[X] * v2[Y] - v1[Y] * v2[X];

    return Vector3f{x, y, z};
}

} // namespace geom