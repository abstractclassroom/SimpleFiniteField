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
    // explicit FiniteField(int64_t prime);
    explicit FiniteField(const std::string& prime);

    class FieldElement {
    public:
        Integer value;
        const FiniteField* field;

        // Constructors
        //constructor accepting string
        FieldElement(const std::string& v, const FiniteField* field);
        FieldElement(const Integer& v, const FiniteField* field);  
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

        const Integer& getPrime() const;
    };

    FieldElement element(const Integer& v);
    FieldElement element(const int64_t v);
    FieldElement element(const std::string& v);
    const Integer& getPrime() const;

private:
    Integer prime;
};

#endif // FINITE_FIELD_HPP
