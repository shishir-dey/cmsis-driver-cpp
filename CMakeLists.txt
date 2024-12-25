cmake_minimum_required(VERSION 3.10)
project(cmsis-driver-cpp VERSION 0.1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the library
add_library(cmsis-driver-cpp INTERFACE)
target_include_directories(cmsis-driver-cpp INTERFACE ${PROJECT_SOURCE_DIR}/include)

# Set library properties
set_target_properties(cmsis-driver-cpp PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

# Install the library
install(TARGETS cmsis-driver-cpp
    EXPORT cmsis-driver-cpp-config
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# Install headers
install(DIRECTORY include/
    DESTINATION include/cmsis-driver-cpp
    FILES_MATCHING PATTERN "*.hpp"
)

# Add Google Test subdirectory
add_subdirectory(external/googletest)

# Enable testing
enable_testing()

# Add test directory
add_subdirectory(tests)