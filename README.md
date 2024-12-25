# cmsis-driver-cpp

## Build Instructions

To build the project, follow these steps:

1. Create a build directory:
   ```
   mkdir build
   ```

2. Generate the build system files using CMake:
   ```
   cmake . -B build
   ```

3. Build the project:
   ```
   cmake --build build
   ```

4. Run the tests:
   ```
   ctest --test-dir build -V
   ```
