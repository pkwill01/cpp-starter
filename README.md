# CPP STARTER PROJECT
Starter for me so I dont have to work out cmake every time 

## Running 
### Hello World 
```bash 
# Create the build directory and make file 
cmake -B build 
# Navigate to build directory 
cd build 
# Make 
make 
# Run the binary 
./helloWorld
```
### Tests

## Adding Modules
First create new folder in `src/[moduleName]` then add the `moduleName.h` and `moduleName.cpp` files.

Then open the `CMakeLists.txt` file and add;
```CMake
# Source files
set(DIR_SRC src)
set(DIR_MODULE1 ${DIR_SRC}/module1)
set(DIR_MODULENAME ${DIR_SRC}/moduleName)

# Include directories
include_directories(${DIR_MODULE1})
include_directories(${DIR_MODULENAME})

# Static library (moduleName)
file(GLOB SRC_LIB CONFIGURE_DEPENDS ${DIR_MODULENAME}/*.cpp ${DIR_MODULENAME}/*.h)
add_library(moduleName_lib STATIC ${SRC_LIB})

# Link Modules 
target_link_libraries(${TARGET_BIN} moduleName_lib)
```
Your new module should now be added and ready to be called from main!
## TODO 

- [] Add CPPU test and test folder to cmake 
