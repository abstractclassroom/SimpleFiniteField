#ifndef FINITE_FIELD_HPP
#define FINITE_FIELD_HPP

#include "Integer.hpp"  

#include <cstdint>
#include <stdexcept>
#include <iostream>

class FiniteField {
public:
    static void setPrime(const Integer& p);

    class FieldElement {
    public:
        Integer value;

        // Constructor
        FieldElement();  // default = 0
        FieldElement(int64_t v = 0); // convenience constructor
        FieldElement(const Integer& v);

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

    private:
        static uint64_t modInverse(uint64_t a, uint64_t p);
    };

private:
    static Integer prime;
};


#endif // FINITE_FIELD_HPP