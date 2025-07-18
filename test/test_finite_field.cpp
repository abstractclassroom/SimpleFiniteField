#include "FiniteField.hpp"
#include <gtest/gtest.h>

using Field = FiniteField::FieldElement;

class FiniteFieldTest : public ::testing::Test {
protected:
    void SetUp() override {
        FiniteField::setPrime(17);  // Small prime for testability
    }
};

TEST_F(FiniteFieldTest, ConstructorNormalization) {
    EXPECT_EQ(Field(17).value, 0);
    EXPECT_EQ(Field(34).value, 0);
    EXPECT_EQ(Field(-1).value, 16);
    EXPECT_EQ(Field(-18).value, 16);
    EXPECT_EQ(Field(18).value, 1);
}

TEST_F(FiniteFieldTest, Addition) {
    EXPECT_EQ((Field(5) + Field(6)).value, 11);
    EXPECT_EQ((Field(10) + Field(10)).value, 3);
}

TEST_F(FiniteFieldTest, Subtraction) {
    EXPECT_EQ((Field(10) - Field(3)).value, 7);
    EXPECT_EQ((Field(3) - Field(10)).value, 10);
}

TEST_F(FiniteFieldTest, Multiplication) {
    EXPECT_EQ((Field(3) * Field(4)).value, 12);
    EXPECT_EQ((Field(6) * Field(3)).value, 1);
}

TEST_F(FiniteFieldTest, Division) {
    EXPECT_EQ((Field(6) / Field(3)).value, (6 * Field(3).inverse().value) % 17);
    EXPECT_EQ((Field(15) / Field(5)).value, (15 * Field(5).inverse().value) % 17);
}

TEST_F(FiniteFieldTest, Inverse) {
    for (int i = 1; i < 17; ++i) {
        Field x(i);
        Field inv = x.inverse();
        EXPECT_EQ((x * inv).value, 1) << "Failed at i = " << i;
    }
    EXPECT_THROW(Field(0).inverse(), std::invalid_argument) << "Inverse of zero should throw";
}

TEST_F(FiniteFieldTest, CompoundOperators) {
    Field a = 4;
    Field b = 5;
    a += b;
    EXPECT_EQ(a.value, 9);
    a *= b;
    EXPECT_EQ(a.value, 11);
    a -= b;
    EXPECT_EQ(a.value, 6);
    a /= b;
    EXPECT_EQ(b.inverse().value, 7); 
}

TEST_F(FiniteFieldTest, EqualityAndInequality) {
    EXPECT_TRUE(Field(5) == Field(5));
    EXPECT_FALSE(Field(5) == Field(6));
    EXPECT_TRUE(Field(5) != Field(6));
    EXPECT_FALSE(Field(5) != Field(5));
}

TEST_F(FiniteFieldTest, UnaryNegation) {
    EXPECT_EQ((-Field(0)).value, 0);
    EXPECT_EQ((-Field(1)).value, 16);
    EXPECT_EQ((-Field(2)).value, 15);
    EXPECT_EQ((-Field(8)).value, 9);
    EXPECT_EQ((-Field(16)).value, 1);
}

TEST_F(FiniteFieldTest, OutputStream) {
    std::ostringstream oss;
    oss << Field(5);
    EXPECT_EQ(oss.str(), "5");
    oss.str("");  // Clear the stream
    oss << Field(16);
    EXPECT_EQ(oss.str(), "16");
}

TEST_F(FiniteFieldTest, MultiplicativeInverses) {
    for (int i = 1; i < 17; ++i) {
        Field x(i);
        try {
            Field inv = x.inverse();
            EXPECT_EQ((x * inv).value, 1) << "Inverse failed for element: " << i;
        } catch (const std::runtime_error& e) {
            EXPECT_TRUE(false) << "Inverse should not throw for element: " << i;
        }
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
