#include "FiniteField.hpp"
#include "Integer.hpp"
#include <cstdint>


FiniteField::FiniteField(const Integer& p) : prime(p) {}


FiniteField::FieldElement::FieldElement(const Integer& v, const FiniteField* f)
    : value(v % f->getPrime()), field(f) {
    if (value < 0)
        value += f->getPrime();
}

FiniteField::FieldElement::FieldElement(int64_t v, const FiniteField* f)
    : FieldElement(Integer(v), f) {}

FiniteField::FieldElement::FieldElement(const std::string& v, const FiniteField* f)
    : FieldElement(Integer(v), f) {}