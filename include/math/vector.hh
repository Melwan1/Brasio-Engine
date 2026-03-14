#pragma once

#include <initializer_list>
#include <ostream>

namespace brasio::math
{
    template <typename ElementType, unsigned size>
    class Vector
    {
    public:
        using container_type = ElementType[size];
        Vector(const container_type &elements);
        Vector(const Vector<ElementType, size - 1> &rhs)
            requires(size >= 2);
        Vector(const Vector<ElementType, size + 1> &rhs)
            requires(size <= 3);
        Vector(std::initializer_list<ElementType> elements);
        Vector();

        /**
         * Conversion to arrays.
         */
        const ElementType *to_array() const;

        ElementType &operator[](unsigned index);
        const ElementType &operator[](unsigned index) const;
        Vector<ElementType, size>
        operator-(const Vector<ElementType, size> &rhs) const;
        Vector<ElementType, size>
        operator+(const Vector<ElementType, size> &rhs) const;
        Vector<ElementType, size>
        operator+=(const Vector<ElementType, size> &rhs);

        ElementType operator*(const Vector<ElementType, size> &rhs) const;

        Vector<ElementType, size> operator-() const;
        Vector<ElementType, size> operator*(const ElementType &scalar) const;
        Vector<ElementType, size> operator*=(const ElementType &scalar);

        Vector<ElementType, size>
        cross_product(const Vector<ElementType, size> &rhs) const
            requires(size == 3);

        Vector<ElementType, size> normalize() const;
        double norm() const;
        ElementType squared_norm() const;

        bool operator==(const Vector<ElementType, size> &vector) const;

        static ElementType &get_element_base();

    private:
        container_type elements_;
    };

    using Vector2 = Vector<float, 2>;
    using Vector3 = Vector<float, 3>;
    using Vector4 = Vector<float, 4>;

    using IntVector2 = Vector<int, 2>;
    using IntVector3 = Vector<int, 3>;
    using IntVector4 = Vector<int, 4>;

    template <typename ElementType, unsigned size>
    std::ostream &operator<<(std::ostream &ostr,
                             const Vector<ElementType, size> &vector);
} // namespace brasio::math

#include <math/vector.hxx>
