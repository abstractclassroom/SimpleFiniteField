#include "FiniteField.hpp"

void FiniteField::setPrime(const Integer& p) {
    if (p < 2) throw std::invalid_argument("Prime must be ≥ 2");
    prime = p;
}

FiniteField::FieldElement FiniteField::FieldElement::inverse() const {
    return FieldElement(mod_inverse(value, prime));
}
