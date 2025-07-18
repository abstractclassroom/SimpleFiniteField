#include "FiniteField.hpp"

FiniteField::FieldElement FiniteField::FieldElement::operator+(const FieldElement& other) const {
    Integer result = (value + other.value) % prime;
    return FieldElement(result < 0 ? result + prime : result);
}

FiniteField::FieldElement FiniteField::FieldElement::operator-(const FieldElement& other) const {
    Integer result = (value - other.value) % prime;
    return FieldElement(result < 0 ? result + prime : result);
}

FiniteField::FieldElement FiniteField::FieldElement::operator*(const FieldElement& other) const {
    Integer result = (value * other.value) % prime;
    return FieldElement(result < 0 ? result + prime : result);
}

FiniteField::FieldElement FiniteField::FieldElement::operator/(const FieldElement& other) const {
    return *this * other.inverse();
}

FiniteField::FieldElement& FiniteField::FieldElement::operator+=(const FieldElement& other) {
    value = (value + other.value) % prime;
    if (value < 0) value += prime;
    return *this;
}

FiniteField::FieldElement& FiniteField::FieldElement::operator-=(const FieldElement& other) {
    value = (value - other.value) % prime;
    if (value < 0) value += prime;
    return *this;
}

FiniteField::FieldElement& FiniteField::FieldElement::operator*=(const FieldElement& other) {
    value = (value * other.value) % prime;
    if (value < 0) value += prime;
    return *this;
}

FiniteField::FieldElement& FiniteField::FieldElement::operator/=(const FieldElement& other) {
    *this *= other.inverse();
    return *this;
}

FiniteField::FieldElement FiniteField::FieldElement::operator-() const {
    return FieldElement((prime - value) % prime);
}

bool FiniteField::FieldElement::operator==(const FieldElement& other) const {
    return value == other.value;
}

bool FiniteField::FieldElement::operator!=(const FieldElement& other) const {
    return value != other.value;
}

std::ostream& operator<<(std::ostream& os, const FiniteField::FieldElement& el) {
    return os << el.value;
}
