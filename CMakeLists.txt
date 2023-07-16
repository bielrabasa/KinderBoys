cmake_minimum_required(VERSION 3.1)

project(Super-Smash-TV)

set(CMAKE_CXX_STANDARD 23)

if(MSVC)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /D _CRT_SECURE_NO_WARNINGS /MP")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D _CRT_SECURE_NO_WARNINGS /MP")
endif()

include(CheckCXXSourceCompiles)
include(GNUInstallDirs)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED COMPONENTS SDL2_image)

include_directories(${SDL2_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src/)

# Source and header files
file(GLOB_RECURSE SSMASHTV_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE SSMASHTV_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")

# Configure executable
add_executable(ssmashtv ${SSMASHTV_SOURCES} ${SSMASHTV_HEADERS})
target_compile_options(ssmashtv PUBLIC "-g")
target_link_libraries(ssmashtv SDL2 SDL2_image SDL2_mixer SDL2_ttf)

