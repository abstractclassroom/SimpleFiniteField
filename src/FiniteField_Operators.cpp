#include "FiniteField.hpp"



FiniteField::FieldElement FiniteField::FieldElement::operator+(const FieldElement& other) const {
    Integer result = (value + other.value) % field->getPrime();
    return FieldElement(result < 0 ? result + field->getPrime() : result, field);
}

FiniteField::FieldElement FiniteField::FieldElement::operator-(const FieldElement& other) const {
    Integer result = (value - other.value) % field->getPrime();
    return FieldElement(result < 0 ? result + field->getPrime() : result, field);
}

FiniteField::FieldElement FiniteField::FieldElement::operator*(const FieldElement& other) const {
    Integer result = (value * other.value) % field->getPrime();
    return FieldElement(result < 0 ? result + field->getPrime() : result, field);
}

FiniteField::FieldElement FiniteField::FieldElement::operator/(const FieldElement& other) const {
    return *this * other.inverse();
}

FiniteField::FieldElement& FiniteField::FieldElement::operator+=(const FieldElement& other) {
    value = (value + other.value) % field->getPrime();
    if (value < 0) value += field->getPrime();
    return *this;
}

FiniteField::FieldElement& FiniteField::FieldElement::operator-=(const FieldElement& other) {
    value = (value - other.value) % field->getPrime();
    if (value < 0) value += field->getPrime();
    return *this;
}

FiniteField::FieldElement& FiniteField::FieldElement::operator*=(const FieldElement& other) {
    value = (value * other.value) % field->getPrime();
    if (value < 0) value += field->getPrime();
    return *this;
}

FiniteField::FieldElement& FiniteField::FieldElement::operator/=(const FieldElement& other) {
    *this *= other.inverse();
    return *this;
}

FiniteField::FieldElement FiniteField::FieldElement::operator-() const {
    return FieldElement((field->getPrime() - value) % field->getPrime(), field);
}

bool FiniteField::FieldElement::operator==(const FieldElement& other) const {
    return value == other.value && field->getPrime() == other.field->getPrime();
}

bool FiniteField::FieldElement::operator!=(const FieldElement& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const FiniteField::FieldElement& el) {
    return os << el.value;
}


