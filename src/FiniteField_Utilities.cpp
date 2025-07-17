#include "FiniteField.hpp"
#include <tuple>

void FiniteField::setPrime(uint64_t p) {
    if (p < 2) throw std::invalid_argument("Prime must be ≥ 2");
    prime = p;
}

uint64_t FiniteField::FieldElement::modInverse(uint64_t a, uint64_t p) {
    int64_t t = 0, newt = 1;
    int64_t r = p, newr = a;

    while (newr != 0) {
        int64_t quotient = r / newr;
        std::tie(t, newt) = std::make_tuple(newt, t - quotient * newt);
        std::tie(r, newr) = std::make_tuple(newr, r - quotient * newr);
    }

    if (r > 1) throw std::runtime_error("No inverse exists");
    if (t < 0) t += p;

    return t;
}

FiniteField::FieldElement FiniteField::FieldElement::inverse() const {
    return FieldElement(modInverse(value, prime));
}
