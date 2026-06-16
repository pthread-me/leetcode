cmake_minimum_required(VERSION 4.0)
project(coding VERSION 0.1 DESCRIPTION "I am SPEED")

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED on )
set(CMAKE_BUILD_TYPE Debug)


add_executable(main src/main.cpp)

target_compile_options(main PRIVATE
  -O3
  -Wextra
  -Wpedantic
)


