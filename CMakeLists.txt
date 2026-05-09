cmake_minimum_required(VERSION 3.10)
project(NitroCppTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Common source files
set(COMMON_SOURCES
    src/Rectangle.cpp
    src/IntersectionFinder.cpp
)

# Main executable
add_executable(nitro_test 
    src/main.cpp
    ${COMMON_SOURCES}
)

# Test executable (manual tests only)
add_executable(run_tests 
    tests/manual_tests.cpp
    ${COMMON_SOURCES}
)

# Include paths
target_include_directories(nitro_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/third_party
    ${CMAKE_SOURCE_DIR}/src
)

target_include_directories(run_tests PRIVATE 
    ${CMAKE_SOURCE_DIR}/third_party
    ${CMAKE_SOURCE_DIR}/src
)

# Compiler options
if(MSVC)
    target_compile_options(nitro_test PRIVATE /W4 /std:c++17)
    target_compile_options(run_tests PRIVATE /W4 /std:c++17)
else()
    target_compile_options(nitro_test PRIVATE -Wall -Wextra -std=c++17)
    target_compile_options(run_tests PRIVATE -Wall -Wextra -std=c++17)
endif()

# Custom target to run tests
add_custom_target(check
    COMMAND run_tests
    DEPENDS run_tests
    COMMENT "Running unit tests..."
    VERBATIM
)

# Set working directory for tests (Windows)
if(MSVC)
    set_property(TARGET run_tests PROPERTY VS_DEBUGGER_WORKING_DIRECTORY 
        ${CMAKE_BINARY_DIR}/$<CONFIGURATION>)
endif()

message(STATUS "")
message(STATUS "=== Build Configuration ===")
message(STATUS "Main executable: nitro_test")
message(STATUS "Test executable: run_tests")
message(STATUS "Run tests: cmake --build . --target check")
message(STATUS "==========================")