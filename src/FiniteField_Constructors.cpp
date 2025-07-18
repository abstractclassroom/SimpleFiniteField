#include "FiniteField.hpp"

Integer FiniteField::prime = Integer(2);  // Default prime

FiniteField::FieldElement::FieldElement(const Integer& v) {
    value = v % prime;
    if (value < 0)
        value += prime;
}

FiniteField::FieldElement::FieldElement(int64_t v)
    : FiniteField::FieldElement(Integer(v)) {}
