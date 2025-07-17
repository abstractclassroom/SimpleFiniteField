#include "FiniteField.hpp"

FiniteField::FieldElement FiniteField::FieldElement::operator+(const FieldElement& other) const {
    return FieldElement((value + other.value));
}

FiniteField::FieldElement FiniteField::FieldElement::operator-(const FieldElement& other) const {
    return FieldElement(value - other.value);
}

FiniteField::FieldElement FiniteField::FieldElement::operator*(const FieldElement& other) const {
    return FieldElement((value * other.value));
}

FiniteField::FieldElement FiniteField::FieldElement::operator/(const FieldElement& other) const {
    return *this * other.inverse();
}

FiniteField::FieldElement& FiniteField::FieldElement::operator+=(const FieldElement& other) {
    value = (value + other.value) % prime;
    return *this;
}

FiniteField::FieldElement& FiniteField::FieldElement::operator-=(const FieldElement& other) {
    value = (value + prime - other.value) % prime;
    return *this;
}

FiniteField::FieldElement& FiniteField::FieldElement::operator*=(const FieldElement& other) {
    value = (value * other.value) % prime;
    return *this;
}

FiniteField::FieldElement& FiniteField::FieldElement::operator/=(const FieldElement& other) {
    *this *= other.inverse();
    return *this;
}

FiniteField::FieldElement FiniteField::FieldElement::operator-() const {
    return FieldElement((prime - value));
}

bool FiniteField::FieldElement::operator==(const FieldElement& other) const {
    return value == other.value;
}

bool FiniteField::FieldElement::operator!=(const FieldElement& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const FiniteField::FieldElement& el) {
    return os << el.value;
}
