#include "FiniteField.hpp"
#include <iostream>
#include <vector>

using Field = FiniteField::FieldElement;

int main() {
    FiniteField GF(17);  

    std::vector<Field> elements;
    for (int i = 0; i < 17; ++i) {
        elements.push_back(GF.element(i));  
    }

    std::cout << "Finite Field Elements (mod 17):\n";
    std::cout << "Multiplicative Inverses:\n";
    for (const auto& elem : elements) {
        try {
            Field inv = elem.inverse();
            std::cout << "Element: " << elem << ", Inverse: " << inv << " --> (" << elem << " * " << inv << " ≡ 1)" << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cout << "Element: " << elem << ", Inverse: Not defined (error: " << e.what() << ")" << std::endl;
        }
    }

    std::cout << "Additive Inverses:\n";
    for (const auto& elem : elements) {
        std::cout << "Element: " << elem << ", Additive Inverse: " << -elem << std::endl;
    }

    std::cout << "Testing GF operations:\n";
    Field a = GF.element(5);
    Field b = GF.element(3);
    std::cout << "a + b = " << (a + b) << std::endl;
    std::cout << "a - b = " << (a - b) << std::endl;
    std::cout << "a * b = " << (a * b) << std::endl;
    std::cout << "a / b = " << (a / b) << std::endl;
    std::cout << "a += b: " << (a += b) << std::endl;
    std::cout << "a -= b: " << (a -= b) << std::endl;
    std::cout << "a *= b: " << (a *= b) << std::endl;
    std::cout << "a /= b: " << (a /= b) << std::endl;

    return 0;
}
