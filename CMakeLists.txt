cmake_minimum_required(VERSION 3.22.3)

project($ENV{PROJECT_NAME} VERSION 1.0)

# specify the C standard c++17
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

file(GLOB SOURCES CONFIGURE_DEPENDS src/**/*.c)
add_executable(${PROJECT_NAME} src/main.c ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

# raylib
find_package(raylib REQUIRED)
target_link_libraries(${PROJECT_NAME} raylib)
