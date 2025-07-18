#include "FiniteField.hpp"
#include <gtest/gtest.h>
#include <sstream>

using Field = FiniteField::FieldElement;

class FiniteFieldIntegerTest : public ::testing::Test {
protected:
    FiniteField field{Integer(17)};  

    Field val(int64_t x) { return field.element(Integer(x)); }
};

TEST_F(FiniteFieldIntegerTest, ConstructorNormalization) {
    EXPECT_EQ(val(17).value, Integer(0));
    EXPECT_EQ(val(34).value, Integer(0));
    EXPECT_EQ(val(-1).value, Integer(16));
    EXPECT_EQ(val(-18).value, Integer(16));
    EXPECT_EQ(val(18).value, Integer(1));
}

TEST_F(FiniteFieldIntegerTest, Addition) {
    EXPECT_EQ((val(5) + val(6)).value, Integer(11));
    EXPECT_EQ((val(10) + val(10)).value, Integer(3));
}

TEST_F(FiniteFieldIntegerTest, Subtraction) {
    EXPECT_EQ((val(10) - val(3)).value, Integer(7));
    EXPECT_EQ((val(3) - val(10)).value, Integer(10));
}

TEST_F(FiniteFieldIntegerTest, Multiplication) {
    EXPECT_EQ((val(3) * val(4)).value, Integer(12));
    EXPECT_EQ((val(6) * val(3)).value, Integer(1));
}

TEST_F(FiniteFieldIntegerTest, Division) {
    EXPECT_EQ((val(6) / val(3)).value, (Integer(6) * val(3).inverse().value) % Integer(17));
    EXPECT_EQ((val(15) / val(5)).value, (Integer(15) * val(5).inverse().value) % Integer(17));
}

TEST_F(FiniteFieldIntegerTest, Inverse) {
    for (int i = 1; i < 17; ++i) {
        Field x = val(i);
        Field inv = x.inverse();
        EXPECT_EQ((x * inv).value, Integer(1)) << "Failed at i = " << i;
    }
    EXPECT_THROW(val(0).inverse(), std::invalid_argument);
}

TEST_F(FiniteFieldIntegerTest, CompoundOperators) {
    Field a = val(4);
    Field b = val(5);
    a += b;
    EXPECT_EQ(a.value, Integer(9));
    a *= b;
    EXPECT_EQ(a.value, Integer(11));
    a -= b;
    EXPECT_EQ(a.value, Integer(6));
    a /= b;
    EXPECT_EQ(a.value, (Integer(6) * val(5).inverse().value) % Integer(17));
}

TEST_F(FiniteFieldIntegerTest, EqualityAndInequality) {
    EXPECT_TRUE(val(5) == val(5));
    EXPECT_FALSE(val(5) == val(6));
    EXPECT_TRUE(val(5) != val(6));
    EXPECT_FALSE(val(5) != val(5));
}

TEST_F(FiniteFieldIntegerTest, UnaryNegation) {
    EXPECT_EQ((-val(0)).value, Integer(0));
    EXPECT_EQ((-val(1)).value, Integer(16));
    EXPECT_EQ((-val(2)).value, Integer(15));
    EXPECT_EQ((-val(8)).value, Integer(9));
    EXPECT_EQ((-val(16)).value, Integer(1));
}

TEST_F(FiniteFieldIntegerTest, OutputStream) {
    std::ostringstream oss;
    oss << val(5);
    EXPECT_EQ(oss.str(), "5");
    oss.str("");
    oss << val(16);
    EXPECT_EQ(oss.str(), "16");
}

TEST_F(FiniteFieldIntegerTest, MultiplicativeInverses) {
    for (int i = 1; i < 17; ++i) {
        Field x = val(i);
        try {
            Field inv = x.inverse();
            EXPECT_EQ((x * inv).value, Integer(1)) << "Inverse failed for element: " << i;
        } catch (const std::runtime_error& e) {
            FAIL() << "Inverse should not throw for element: " << i;
        }
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
