# cmsis-driver-cpp

## Fetch Submodules

Before building the project, ensure all submodules are initialized and updated:

```
git submodule update --init --recursive
```

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
