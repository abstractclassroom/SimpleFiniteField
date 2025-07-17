cmake_minimum_required(VERSION 3.14)
project(FiniteFieldProject)

set(CMAKE_CXX_STANDARD 17)
enable_testing()

include_directories(include)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(finite_field_tests test/test_finite_field.cpp)
target_link_libraries(finite_field_tests gtest_main finite_field)
add_test(NAME FiniteFieldTests COMMAND finite_field_tests)


add_library(finite_field src/FiniteField.cpp)

add_executable(finite_field_example src/finite_field_example.cpp)
target_link_libraries(finite_field_example finite_field)

target_link_libraries(finite_field_tests finite_field)

