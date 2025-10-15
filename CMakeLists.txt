cmake_minimum_required(VERSION 3.12...3.21 FATAL_ERROR)
project(UUIDGenerator VERSION 1.0 DESCRIPTION "UUID Generator Online Tool" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(WTHTTP REQUIRED wthttp)
# pkg_check_modules(WT REQUIRED wt)

list(APPEND CMAKE_MODULE_PATH "/usr/local/lib/cmake/wt")
find_package(Wt REQUIRED COMPONENTS Wt HTTP)

# Include directories
include_directories(${WTHTTP_INCLUDE_DIRS})
include_directories(${WT_INCLUDE_DIRS})

# Create executable
add_executable(uuid-generator src/main.cpp src/UUIDGenerator.h)

# Link libraries
target_link_libraries(uuid-generator PRIVATE Wt::Wt Wt::HTTP)

# Compiler flags
target_compile_options(uuid-generator PRIVATE ${WTHTTP_CFLAGS_OTHER} ${WT_CFLAGS_OTHER})
