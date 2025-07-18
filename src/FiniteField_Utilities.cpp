#include "FiniteField.hpp"



FiniteField::FieldElement FiniteField::FieldElement::inverse() const {
    return FieldElement(mod_inverse(value, field->getPrime()), field);
}
