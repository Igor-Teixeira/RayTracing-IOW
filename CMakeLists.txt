cmake_minimum_required(VERSION 3.20)

# Disable in-source builds
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
    message(FATAL_ERROR
        "In-source builds are disabled. Please create a build directory.")
endif()

# Setup build types
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type")

get_property(GEN_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(GEN_MULTI_CONFIG)
    set(RTIOW_BUILD_TYPES Debug Release)

    set(CMAKE_CONFIGURATION_TYPES ${RTIOW_BUILD_TYPES}
        CACHE STRING "Available build types" FORCE)
endif()

project(raytracer VERSION 1.0.0 LANGUAGES C CXX DESCRIPTION "Ray Tracing in One Weekend")

# Main application
add_executable(raytracer)

# Properties
set_target_properties(raytracer PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON)

# Include directories
target_include_directories(raytracer PRIVATE src)

# Compiler options
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(raytracer PRIVATE /MP /permissive /W4)

elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(raytracer PRIVATE -pedantic -Wall -Wextra)
endif()

# Source files
file(GLOB_RECURSE RTIOW_SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.c)
file(GLOB_RECURSE RTIOW_HEADERS CONFIGURE_DEPENDS src/*.hpp src/*.h)

target_sources(raytracer PRIVATE ${RTIOW_HEADERS} ${RTIOW_SOURCES})
