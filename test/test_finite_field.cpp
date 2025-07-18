#include "FiniteField.hpp"
#include <gtest/gtest.h>
#include <sstream>

using Field = FiniteField::FieldElement;

class FiniteFieldTest : public ::testing::Test {
protected:
    FiniteField field{17}; 

    Field val(int64_t x) {
        return Field(x, &field);
    }
};

TEST_F(FiniteFieldTest, ConstructorNormalization) {
    EXPECT_EQ(val(17).value, 0);
    EXPECT_EQ(val(34).value, 0);
    EXPECT_EQ(val(-1).value, 16);
    EXPECT_EQ(val(-18).value, 16);
    EXPECT_EQ(val(18).value, 1);
}

TEST_F(FiniteFieldTest, Addition) {
    EXPECT_EQ((val(5) + val(6)).value, 11);
    EXPECT_EQ((val(10) + val(10)).value, 3);
}

TEST_F(FiniteFieldTest, Subtraction) {
    EXPECT_EQ((val(10) - val(3)).value, 7);
    EXPECT_EQ((val(3) - val(10)).value, 10);
}

TEST_F(FiniteFieldTest, Multiplication) {
    EXPECT_EQ((val(3) * val(4)).value, 12);
    EXPECT_EQ((val(6) * val(3)).value, 1);
}

TEST_F(FiniteFieldTest, Division) {
    EXPECT_EQ((val(6) / val(3)).value, (6 * val(3).inverse().value) % 17);
    EXPECT_EQ((val(15) / val(5)).value, (15 * val(5).inverse().value) % 17);
}

TEST_F(FiniteFieldTest, Inverse) {
    for (int i = 1; i < 17; ++i) {
        Field x = val(i);
        Field inv = x.inverse();
        EXPECT_EQ((x * inv).value, 1) << "Failed at i = " << i;
    }
    EXPECT_THROW(val(0).inverse(), std::invalid_argument);
}

TEST_F(FiniteFieldTest, CompoundOperators) {
    Field a = val(4);
    Field b = val(5);
    a += b;
    EXPECT_EQ(a.value, 9);
    a *= b;
    EXPECT_EQ(a.value, 11);
    a -= b;
    EXPECT_EQ(a.value, 6);
    a /= b;
    EXPECT_EQ(a.value, 6 * b.inverse().value % 17);
}

TEST_F(FiniteFieldTest, EqualityAndInequality) {
    EXPECT_TRUE(val(5) == val(5));
    EXPECT_FALSE(val(5) == val(6));
    EXPECT_TRUE(val(5) != val(6));
    EXPECT_FALSE(val(5) != val(5));
}

TEST_F(FiniteFieldTest, UnaryNegation) {
    EXPECT_EQ((-val(0)).value, 0);
    EXPECT_EQ((-val(1)).value, 16);
    EXPECT_EQ((-val(2)).value, 15);
    EXPECT_EQ((-val(8)).value, 9);
    EXPECT_EQ((-val(16)).value, 1);
}

TEST_F(FiniteFieldTest, OutputStream) {
    std::ostringstream oss;
    oss << val(5);
    EXPECT_EQ(oss.str(), "5");
    oss.str("");
    oss << val(16);
    EXPECT_EQ(oss.str(), "16");
}

TEST_F(FiniteFieldTest, MultiplicativeInverses) {
    for (int i = 1; i < 17; ++i) {
        Field x = val(i);
        try {
            Field inv = x.inverse();
            EXPECT_EQ((x * inv).value, 1) << "Inverse failed for element: " << i;
        } catch (const std::runtime_error& e) {
            FAIL() << "Inverse should not throw for element: " << i;
        }
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
