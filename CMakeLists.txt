cmake_minimum_required(VERSION 3.9)
project(SFML-Jumping-balls)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")
add_compile_options(-Wall -ggdb)

file(GLOB TARGET_SRC "./src/*.cpp" )
include_directories("./include")

# Setting SFML_DIR on windows
if (NOT LINUX AND WIN32)
    message(STATUS "Building for Windows!")
    set(SFML_DIR "c:/SFML/lib/cmake/SFML")
else()
    message(STATUS "Building for Linux!")
endif()

# Finding SFML
find_package(SFML 2.5.1 COMPONENTS audio graphics window system REQUIRED)
include_directories(${SFML_INCLUDES})

add_executable(SFML-Jumping-balls ${TARGET_SRC})
target_link_libraries(SFML-Jumping-balls PRIVATE sfml-audio sfml-graphics sfml-window sfml-system)