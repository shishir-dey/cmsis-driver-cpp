# Collect all test source files
file(GLOB_RECURSE TEST_SOURCES *.cpp)

# Create the test executable
add_executable(cmsis-driver-cpp-tests ${TEST_SOURCES})

# Link the test executable with the library and Google Test
target_link_libraries(cmsis-driver-cpp-tests
    PRIVATE cmsis-driver-cpp
    gmock
    gtest_main
)

# Register tests with CTest
include(GoogleTest)
gtest_discover_tests(cmsis-driver-cpp-tests)