cmake_minimum_required(VERSION 3.14)

# Set the project name
project(helloWorld)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# Force colored compiler output
add_compile_options(-fdiagnostics-color)

# CXX flags
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS "-Wall") # Consider adding -Wextra -Wpedantic if needed
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_definitions(-DEIGEN_INITIALIZE_MATRICES_BY_NAN)

# Find CppUTest
find_package(PkgConfig REQUIRED)
pkg_search_module(CPPUTEST REQUIRED cpputest>=3.8)
message(STATUS "Found CppUTest version ${CPPUTEST_VERSION}")

# Target names
set(TARGET_LIB common)
set(TARGET_BIN ${PROJECT_NAME})
set(TEST_BIN ${PROJECT_NAME}_test)

# Source files 
set(DIR_SRC src)
set(DIR_MODULE1 ${DIR_SRC}/module1)
set(DIR_TEST_SRC test/src) 

# Include directories
include_directories(${CPPUTEST_INCLUDE_DIRS} ${DIR_MODULE1})

# Link directories
link_directories(${CPPUTEST_LIBRARIES})

# Application
file(GLOB SRC_BIN CONFIGURE_DEPENDS ${DIR_SRC}/*.cpp ${DIR_SRC}/*.h ${DIR_SRC}/*.hpp)

# Static library (module1)
file(GLOB SRC_LIB CONFIGURE_DEPENDS ${DIR_MODULE1}/*.cpp ${DIR_MODULE1}/*.h)
add_library(module1_lib STATIC ${SRC_LIB})

# Exclude main.cpp from the static library
set(SRC_LIB ${SRC_BIN})
list(FILTER SRC_LIB EXCLUDE REGEX ".*main.cpp$")

# Unit tests
file(GLOB SRC_TEST CONFIGURE_DEPENDS ${DIR_TEST_SRC}/*.cpp ${DIR_TEST_SRC}/*.h ${DIR_TEST_SRC}/*.hpp)

# Targets

# Static library
if(SRC_LIB)
    add_library(${TARGET_LIB} ${SRC_LIB})
endif()

# Application
add_executable(${TARGET_BIN} src/main.cpp)

if(SRC_LIB)
    target_link_libraries(${TARGET_BIN} ${TARGET_LIB})
endif()

# Link Modules 
target_link_libraries(${TARGET_BIN} module1_lib)

# Testing Setup 
add_executable(${TEST_BIN} ${SRC_TEST})
target_link_libraries(${TEST_BIN} ${CPPUTEST_LDFLAGS})

# Custom command to run tests
add_custom_command(TARGET ${TEST_BIN} POST_BUILD
                   COMMAND ${TEST_BIN} -c
                   COMMENT "Running tests"
                   DEPENDS ${TEST_BIN})

set_property(GLOBAL PROPERTY TARGET_MESSAGES OFF)
