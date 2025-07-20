cmake_minimum_required(VERSION 3.14)
project(FiniteFieldProject)

set(CMAKE_CXX_STANDARD 17)
enable_testing()

include(FetchContent)

# --- Fetch BigInteger ---
FetchContent_Declare(
  BigInteger
  GIT_REPOSITORY https://github.com/UofL-CSE-AutoGrader/BigInteger_Complete.git
  GIT_TAG v1.0.1
  DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(BigInteger)

# --- Fetch GoogleTest ---
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(googletest)

# --- Include directories ---
include_directories(
  include
  ${biginteger_SOURCE_DIR}/include
)

# --- Build finite_field library ---
add_library(finite_field
  src/FiniteField.cpp
  src/FiniteField_Constructors.cpp
  src/FiniteField_Operators.cpp
  src/FiniteField_Utilities.cpp
)

# Link BigInteger to finite_field
target_link_libraries(finite_field
  PUBLIC BigInteger::BigInteger
)

target_include_directories(finite_field
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
         ${biginteger_SOURCE_DIR}/include
)

# --- Build example ---
add_executable(finite_field_example
  main/finite_field_example.cpp
)
target_link_libraries(finite_field_example
  finite_field
)

# --- Unit tests ---
# First test executable
add_executable(finite_field_tests test/test_finite_field.cpp)
target_link_libraries(finite_field_tests gtest_main finite_field)
add_test(NAME FiniteFieldTests COMMAND finite_field_tests)

# Second test executable
add_executable(finite_field_integer_tests test/test_finite_field_integer.cpp)
target_link_libraries(finite_field_integer_tests gtest_main finite_field)
add_test(NAME FiniteFieldIntegerTests COMMAND finite_field_integer_tests)

target_link_libraries(finite_field_tests
  gtest_main
  finite_field
)

