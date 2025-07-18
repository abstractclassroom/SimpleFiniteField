#include "FiniteField.hpp"



FiniteField::FieldElement FiniteField::FieldElement::inverse() const {
    return FieldElement(mod_inverse(value, field->getPrime()), field);
}

FiniteField::FieldElement FiniteField::element(const Integer& v) {
    return FieldElement(v, this);  
}

FiniteField::FieldElement FiniteField::element(const int64_t v) {
    return FieldElement(Integer(v),this);
}


