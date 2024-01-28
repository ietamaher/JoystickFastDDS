cmake_minimum_required(VERSION 3.20)

project(JoystickFastDDS)

# Find requirements
if(NOT fastcdr_FOUND)
    find_package(fastcdr 2 REQUIRED)
endif()

if(NOT fastrtps_FOUND)
    find_package(fastrtps 2.12 REQUIRED)
endif()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(include)

# Find the yaml-cpp package
find_package(yaml-cpp REQUIRED)

# Include the yaml-cpp headers
include_directories(${YAML_CPP_INCLUDE_DIR})

# Set C++11
include(CheckCXXCompilerFlag)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG OR
        CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    check_cxx_compiler_flag(-std=c++11 SUPPORTS_CXX11)
    if(SUPPORTS_CXX11)
        add_compile_options(-std=c++11)
    else()
        message(FATAL_ERROR "Compiler doesn't support C++11")
    endif()
endif()

message(STATUS "Configuring JoystickFastDDS  publisher ...")
file(GLOB JOYSTICK_FASTDDS_SOURCES_CXX "src/generated/*.cxx")

add_executable(JoystickFastDDS src/main.cpp src/joystick_handler.cpp src/dds_publisher.cpp ${JOYSTICK_FASTDDS_SOURCES_CXX})
target_link_libraries(JoystickFastDDS ${SDL2_LIBRARIES} ${YAML_CPP_LIBRARIES} fastrtps fastcdr)
 

