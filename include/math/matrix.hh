#pragma once

#include <initializer_list>
#include <math/vector.hh>
#include <ostream>

template <typename ElementType, unsigned lines, unsigned columns>
class Matrix
{
public:
    using container_type = ElementType[lines][columns];
    Matrix(const container_type &elements);
    Matrix(std::initializer_list<std::initializer_list<ElementType>> elements);
    Matrix();

    /**
     * Conversion to arrays.
     */
    const ElementType *to_array() const;

    /**
     * This operator allows operations like mat(2, 3) to return the element
     * at line 2, column 3.
     */
    ElementType &operator()(unsigned line, unsigned column);
    const ElementType &operator()(unsigned line, unsigned column) const;
    Matrix<ElementType, lines, columns>
    operator+(const Matrix<ElementType, lines, columns> &rhs) const;
    Matrix<ElementType, lines, columns>
    operator+=(const Matrix<ElementType, lines, columns> &rhs);

    template <unsigned rhs_columns>
    Matrix<ElementType, lines, rhs_columns>
    operator*(const Matrix<ElementType, columns, rhs_columns> &rhs) const;

    Matrix<ElementType, lines, columns> operator*(ElementType scalar) const;
    Matrix<ElementType, lines, columns> operator*=(ElementType scalar);

    Vector<ElementType, lines>
    operator*(const Vector<ElementType, columns> &rhs) const;

    static ElementType &get_element_base();
    static Matrix<ElementType, lines, columns> identity()
        requires(lines == columns);

    Matrix<ElementType, columns, lines> transpose() const;

private:
    container_type elements_;
};

template <typename ElementType, unsigned size>
using SquaredMatrix = Matrix<ElementType, size, size>;

using Matrix3 = SquaredMatrix<float, 3>;
using Matrix4 = SquaredMatrix<float, 4>;

template <typename ElementType, unsigned lines, unsigned columns>
std::ostream &operator<<(std::ostream &ostr,
                         const Matrix<ElementType, lines, columns> &matrix);

#include <math/matrix.hxx>
