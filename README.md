# Nitro C++ Proficiency Test

## Prerequisites
- CMake 3.10 or higher
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- Google Test (will be downloaded automatically)

## Building the Project

### Clean the Build (Optional, if rebuilding from scratch)
To clean the previous build files:

```bash
# From the project root
cmake --build build --target clean
```

### Build Instructions

```bash
# Clone the repository (if not already done)
git clone <repository-url>
cd NitroCppTest-YourName

# Create build directory (if not exists)
mkdir build && cd build

# Configure the project
cmake ..

# Build the project
cmake --build . --config Release
```

## Running the Program
After building, run the main executable:

```bash
# From the build directory
./Release/nitro_test ../sample_input/sample1.json
```

## Running Tests
To run the tests:

```bash
# From the build directory
./Release/run_tests
```

Or, using CMake target:

```bash
# From the project root
cmake --build build --target check
```