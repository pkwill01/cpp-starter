cmake_minimum_required(VERSION 3.14)

# Set the project name
project(helloWorld)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# Force coloured compiler output
add_compile_options(-fdiagnostics-color)

# CXX flags
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS "-Wall") # -Wextra -Wpedantic
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_definitions(-DEIGEN_INITIALIZE_MATRICES_BY_NAN)

# Workaround for Qt5 being unlinked under MacOS
if(APPLE AND (NOT DEFINED ENV{Qt5_DIR} OR ENV{Qt5_DIR} STREQUAL "Qt5_DIR-NOTFOUND"))
    execute_process(COMMAND brew --prefix qt@5 OUTPUT_VARIABLE PREFIX_QT5 OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(ENV{Qt5_DIR} ${PREFIX_QT5}/lib/cmake/Qt5)
endif()

# find_package(OpenCV 4.5 REQUIRED)

# Target names
set(TARGET_LIB common)
set(TARGET_BIN ${PROJECT_NAME})
# set(TARGET_TEST tests)

# Libraries
# set(LIBS
#     ${OpenCV_LIBS}
# )

# Source files
set(DIR_SRC src)
# set(DIR_TEST_SRC test/src)


# Application
file(GLOB SRC_BIN CONFIGURE_DEPENDS ${DIR_SRC}/*.cpp ${DIR_SRC}/*.h ${DIR_SRC}/*.hpp)

# Static library
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
target_link_libraries(${TARGET_BIN} ${LIBS})



# Run unit tests after building executables
add_custom_target(run_tests ALL
    COMMAND ${TARGET_TEST} --no-intro --force-colors=true
    DEPENDS ${TARGET_TEST}
    DEPENDS ${TARGET_BIN}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running tests"
)

set_property(GLOBAL PROPERTY TARGET_MESSAGES OFF)
