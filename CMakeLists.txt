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



# Target names
set(TARGET_LIB common)
set(TARGET_BIN ${PROJECT_NAME})


# Source files

set(DIR_SRC src)
set(DIR_MODULE1 ${DIR_SRC}/module1)
# set(DIR_TEST_SRC test/src)

# Include directories
include_directories(${DIR_MODULE1})

# Application
file(GLOB SRC_BIN CONFIGURE_DEPENDS ${DIR_SRC}/*.cpp ${DIR_SRC}/*.h ${DIR_SRC}/*.hpp)

# Static library (module1)
file(GLOB SRC_LIB CONFIGURE_DEPENDS ${DIR_MODULE1}/*.cpp ${DIR_MODULE1}/*.h)
add_library(module1_lib STATIC ${SRC_LIB})

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

# Link Modules 
target_link_libraries(${TARGET_BIN} module1_lib)
target_link_libraries(${TARGET_BIN} ${LIBS})



# Run unit tests after building executables
# add_custom_target(run_tests ALL
#     COMMAND ${TARGET_TEST} --no-intro --force-colors=true
#     DEPENDS ${TARGET_TEST}
#     DEPENDS ${TARGET_BIN}
#     WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
#     COMMENT "Running tests"
# )

set_property(GLOBAL PROPERTY TARGET_MESSAGES OFF)
