cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(EXECUTABLE_NAME circle)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)


file(GLOB_RECURSE SOURCE_FILES src/*.cpp include/*.hpp)


add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})
target_include_directories(${EXECUTABLE_NAME} PRIVATE include/)
target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra -Werror -pedantic -fno-exceptions)
target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_std_17)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE SFML::Graphics)
add_subdirectory(libs)
