#ifndef FINITE_FIELD_HPP
#define FINITE_FIELD_HPP

#include "Integer.hpp"
#include <cstdint>
#include <stdexcept>
#include <iostream>
#include <memory>

class FiniteField {
public:
    explicit FiniteField(const Integer& prime);

    class FieldElement {
    public:
        Integer value;
        const FiniteField* field;

        FieldElement(const Integer& v, const FiniteField* field);  // ✅ MUST BE HERE
        FieldElement(int64_t v, const FiniteField* field);   

        // Arithmetic operators
        FieldElement operator+(const FieldElement& other) const;
        FieldElement operator-(const FieldElement& other) const;
        FieldElement operator*(const FieldElement& other) const;
        FieldElement operator/(const FieldElement& other) const;

        // Compound assignment
        FieldElement& operator+=(const FieldElement& other);
        FieldElement& operator-=(const FieldElement& other);
        FieldElement& operator*=(const FieldElement& other);
        FieldElement& operator/=(const FieldElement& other);

        // Comparison
        bool operator==(const FieldElement& other) const;
        bool operator!=(const FieldElement& other) const;

        // Unary minus
        FieldElement operator-() const;

        // Inverse
        FieldElement inverse() const;

        // Output stream
        friend std::ostream& operator<<(std::ostream& os, const FieldElement& el);
    };

    const Integer& getPrime() const;

private:
    Integer prime;
};

#endif // FINITE_FIELD_HPP
