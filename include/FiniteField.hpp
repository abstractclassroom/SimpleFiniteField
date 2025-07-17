#ifndef FINITE_FIELD_HPP
#define FINITE_FIELD_HPP

#include <cstdint>
#include <stdexcept>
#include <iostream>

class FiniteField {
public:
    static void setPrime(uint64_t p);

    class FieldElement {
    public:
        uint64_t value;

        // Constructor
        FieldElement(int64_t v = 0);

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
    static uint64_t prime;
};

#endif // FINITE_FIELD_HPP
