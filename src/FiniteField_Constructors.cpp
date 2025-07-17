#include "FiniteField.hpp"

uint64_t FiniteField::prime = 17;

FiniteField::FieldElement::FieldElement(int64_t v) {
    int64_t tmp = v;
    if (tmp < 0) {
        tmp += prime * ((-tmp / prime) + 1);
    }
    value = tmp % prime;
}
