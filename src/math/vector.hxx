#pragma once

#include <cmath>
#include <iostream>

#include <math/vector.hh>

namespace brasio::math {
    template<typename ElementType, unsigned size>
    Vector<ElementType, size>::Vector(const container_type &elements) {
        for (unsigned index = 0; index < size; index++) {
            elements_[index] = elements[index];
        }
    }

    template<typename ElementType, unsigned size>
    Vector<ElementType, size>::Vector() {
        for (unsigned index = 0; index < size; index++) {
            elements_[index] = get_element_base();
        }
    }

        template<typename ElementType, unsigned size>
        Vector<ElementType, size>::Vector(const Vector<ElementType, size - 1> &rhs)
    requires(size >= 2)
    {
        for (unsigned index = 0; index < size - 1; index++) {
            elements_[index] = rhs[index];
        }
        elements_[size - 1] = get_element_base() + 1;
    }

        template<typename ElementType, unsigned size>
        Vector<ElementType, size>::Vector(const Vector<ElementType, size + 1> &rhs)
    requires(size <= 3)
    {
        for (unsigned index = 0; index < size; index++) {
            elements_[index] = rhs[index];
        }
    }

    template<typename ElementType, unsigned size>
    const ElementType *Vector<ElementType, size>::to_array() const {
        return elements_;
    }

    template<typename ElementType, unsigned size>
    Vector<ElementType, size> Vector<ElementType, size>::operator-() const {
        Vector result = Vector();
        for (unsigned index = 0; index < size; index++) {
            result.elements_[index] = -elements_[index];
        }
        return result;
    }

    template<typename ElementType, unsigned size>
    Vector<ElementType, size>::Vector(std::initializer_list<ElementType> elements) {
        if (elements.size() != size) {
            std::cerr << "Vector: constructor with initializer_list has wrong "
                "number of elements. Expected: "
                << size << ", got: " << elements.size() << "\n";
            return;
        }
        for (unsigned index = 0; index < size; index++) {
            elements_[index] = elements.begin()[index];
        }
    }

    template<typename ElementType, unsigned size>
    ElementType &Vector<ElementType, size>::operator[](unsigned index) {
        if (index >= size) {
            std::cerr << "Vector element query out of bounds. Size: " << size << ", index queried: " << index << "\n";
            return get_element_base();
        }
        return elements_[index];
    }

    template<typename ElementType, unsigned size>
    const ElementType &Vector<ElementType, size>::operator[](unsigned index) const {
        if (index >= size) {
            std::cerr << "Vector element query out of bounds. Size: " << size << ", index queried: " << index << "\n";
            return get_element_base();
        }
        return elements_[index];
    }

    template<typename ElementType, unsigned size>
    Vector<ElementType, size> Vector<ElementType, size>::operator-(const Vector<ElementType, size> &rhs) const {
        Vector result;
        for (unsigned index = 0; index < size; index++) {
            result[index] = (*this)[index] - rhs[index];
        }
        return result;
    }

    template<typename ElementType, unsigned size>
    Vector<ElementType, size> Vector<ElementType, size>::operator+(const Vector<ElementType, size> &rhs) const {
        Vector result;
        for (unsigned index = 0; index < size; index++) {
            result[index] = (*this)[index] + rhs[index];
        }
        return result;
    }

    template<typename ElementType, unsigned size>
    Vector<ElementType, size> Vector<ElementType, size>::operator+=(const Vector<ElementType, size> &rhs) {
        for (unsigned index = 0; index < size; index++) {
            (*this)[index] += rhs[index];
        }
        return *this;
    }

    template<typename ElementType, unsigned size>
    ElementType Vector<ElementType, size>::operator*(const Vector<ElementType, size> &rhs) const {
        ElementType result = ElementType();
        for (unsigned index = 0; index < size; index++) {
            result += (*this)[index] * rhs[index];
        }
        return result;
    }

    template<typename ElementType, unsigned size>
    Vector<ElementType, size> Vector<ElementType, size>::operator*(const ElementType &scalar) const {
        Vector result;
        for (unsigned index = 0; index < size; index++) {
            result[index] = (*this)[index] * scalar;
        }
        return result;
    }

    template<typename ElementType, unsigned size>
    Vector<ElementType, size> Vector<ElementType, size>::operator*=(const ElementType &scalar) {
        for (unsigned index = 0; index < size; index++) {
            (*this)[index] *= scalar;
        }
        return *this;
    }

    template<typename ElementType, unsigned size>
        Vector<ElementType, size> Vector<ElementType, size>::cross_product(const Vector<ElementType, size> &rhs) const
    requires(size == 3)
    {
        return {(*this)[1] * rhs[2] - (*this)[2] * rhs[1], (*this)[2] * rhs[0] - (*this)[0] * rhs[2],
            (*this)[0] * rhs[1] - (*this)[1] * rhs[0]};
    }

    template<typename ElementType, unsigned size>
    ElementType &Vector<ElementType, size>::get_element_base() {
        static ElementType element = ElementType();
        return element;
    }

    template<typename ElementType, unsigned size>
    Vector<ElementType, size> Vector<ElementType, size>::normalize() const {
        const auto vector_norm = norm();
        if (vector_norm < std::numeric_limits<double>::epsilon()) {
            return Vector();
        }
        return (*this) * (1. / vector_norm);
    }

    template<typename ElementType, unsigned size>
    double Vector<ElementType, size>::norm() const {
        return std::sqrt(squared_norm());
    }

    template<typename ElementType, unsigned size>
    ElementType Vector<ElementType, size>::squared_norm() const {
        ElementType result = ElementType();
        for (unsigned index = 0; index < size; index++) {
            result += elements_[index] * elements_[index];
        }
        return result;
    }

    template<typename ElementType, unsigned size>
    bool Vector<ElementType, size>::operator==(const Vector<ElementType, size> &vector) const {
        for (unsigned index = 0; index < size; index++) {
            if (elements_[index] != vector[index]) {
                return false;
            }
        }
        return true;
    }

    template<typename ElementType, unsigned size>
    std::ostream &operator<<(std::ostream &ostr, const Vector<ElementType, size> &vector) {
        ostr << "( ";
        for (unsigned index = 0; index < size; index++) {
            if (index > 0) {
                ostr << " ";
            }
            ostr << vector[index];
        }
        return ostr << " )";
    }

} // namespace brasio::math
