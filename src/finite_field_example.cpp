#include "FiniteField.hpp"
#include <iostream>
#include <vector>

using Field = FiniteField::FieldElement;

int main() {
    FiniteField::setPrime(17);

    
    std::vector<Field> elements;
    for (int i = 0; i < 17; ++i) {
        elements.push_back(Field(i));
    }

    std::cout<<"Finite Field Elements (mod 17):\n";
    std::cout<<"Multiplicative Inverses:\n";
    for (const auto& elem : elements) {
        try {
            std::cout << "Element: " << elem.value << ", Inverse: " << elem.inverse().value << " --> ( " << elem.value << " * " << elem.inverse().value << " ≡ 1 )" << std::endl;
        } catch (const std::runtime_error& e) {
            std::cout << "Element: " << elem.value << ", Inverse: Not defined (error: " << e.what() << ")" << std::endl;
        }
    }
    std::cout<<"Additive Inverses:\n";
    for (const auto& elem : elements) {
        std::cout << "Element: " << elem.value << ", Additive Inverse: " << (-elem).value << std::endl;
    }
    std::cout << "Testing field operations:\n";
    Field a(5), b(3);
    std::cout << "a + b = " << (a + b).value << std::endl;
    std::cout << "a - b = " << (a - b).value << std::endl;
    std::cout << "a * b = " << (a * b).value << std::endl;
    std::cout << "a / b = " << (a / b).value << std::endl;
    std::cout << "a += b: " << (a += b).value << std::endl;
    std::cout << "a -= b: " << (a -= b).value << std::endl;
    std::cout << "a *= b: " << (a *= b).value << std::endl;
    std::cout << "a /= b: " << (a /= b).value << std::endl;
    return 0;
}
