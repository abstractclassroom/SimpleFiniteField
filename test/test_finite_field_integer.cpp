#include "FiniteField.hpp"
#include <gtest/gtest.h>
#include <sstream>

using Field = FiniteField::FieldElement;

class FiniteFieldIntegerTest : public ::testing::Test {
protected:
    void SetUp() override {
        FiniteField::setPrime(Integer(17));  // Small prime for testability
    }
};

TEST_F(FiniteFieldIntegerTest, ConstructorNormalization) {
    EXPECT_EQ(Field(Integer(17)).value, Integer(0));
    EXPECT_EQ(Field(Integer(34)).value, Integer(0));
    EXPECT_EQ(Field(Integer(-1)).value, Integer(16));
    EXPECT_EQ(Field(Integer(-18)).value, Integer(16));
    EXPECT_EQ(Field(Integer(18)).value, Integer(1));
}

TEST_F(FiniteFieldIntegerTest, Addition) {
    EXPECT_EQ((Field(5) + Field(6)).value, Integer(11));
    EXPECT_EQ((Field(10) + Field(10)).value, Integer(3));
}

TEST_F(FiniteFieldIntegerTest, Subtraction) {
    EXPECT_EQ((Field(10) - Field(3)).value, Integer(7));
    EXPECT_EQ((Field(3) - Field(10)).value, Integer(10));
}

TEST_F(FiniteFieldIntegerTest, Multiplication) {
    EXPECT_EQ((Field(3) * Field(4)).value, Integer(12));
    EXPECT_EQ((Field(6) * Field(3)).value, Integer(1));
}

TEST_F(FiniteFieldIntegerTest, Division) {
    EXPECT_EQ((Field(6) / Field(3)).value, (Integer(6) * Field(3).inverse().value) % Integer(17));
    EXPECT_EQ((Field(15) / Field(5)).value, (Integer(15) * Field(5).inverse().value) % Integer(17));
}

TEST_F(FiniteFieldIntegerTest, Inverse) {
    for (int i = 1; i < 17; ++i) {
        Field x = Field(Integer(i));
        Field inv = x.inverse();
        EXPECT_EQ((x * inv).value, Integer(1)) << "Failed at i = " << i;
    }
    EXPECT_THROW(Field(Integer(0)).inverse(), std::invalid_argument) << "Inverse of zero should throw";
}

TEST_F(FiniteFieldIntegerTest, CompoundOperators) {
    Field a = Field(Integer(4));
    Field b = Field(Integer(5));
    a += b;
    EXPECT_EQ(a.value, Integer(9));
    a *= b;
    EXPECT_EQ(a.value, Integer(11));
    a -= b;
    EXPECT_EQ(a.value, Integer(6));
    a /= b;
    EXPECT_EQ(a.value, (Integer(6) * Field(5).inverse().value) % Integer(17));
}

TEST_F(FiniteFieldIntegerTest, EqualityAndInequality) {
    EXPECT_TRUE(Field(5) == Field(5));
    EXPECT_FALSE(Field(5) == Field(6));
    EXPECT_TRUE(Field(5) != Field(6));
    EXPECT_FALSE(Field(5) != Field(5));
}

TEST_F(FiniteFieldIntegerTest, UnaryNegation) {
    EXPECT_EQ((-Field(0)).value, Integer(0));
    EXPECT_EQ((-Field(1)).value, Integer(16));
    EXPECT_EQ((-Field(2)).value, Integer(15));
    EXPECT_EQ((-Field(8)).value, Integer(9));
    EXPECT_EQ((-Field(16)).value, Integer(1));
}

TEST_F(FiniteFieldIntegerTest, OutputStream) {
    std::ostringstream oss;
    oss << Field(5);
    EXPECT_EQ(oss.str(), "5");
    oss.str("");  // Clear the stream
    oss << Field(16);
    EXPECT_EQ(oss.str(), "16");
}

TEST_F(FiniteFieldIntegerTest, MultiplicativeInverses) {
    for (int i = 1; i < 17; ++i) {
        Field x(i);
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
