cmake_minimum_required(VERSION 3.16)
project(object_serialization)

set(CMAKE_CXX_STANDARD 14)

add_executable(object_serialization main.cpp xml_serialization.h xml_serialization.cpp tinyxml2.h tinyxml2.cpp binary_serialization.cpp binary_serialization.h convert_to_char.cpp convert_to_char.h merge.h)