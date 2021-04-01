cmake_minimum_required(VERSION 3.17)
project(SiberianGameJam)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

file(GLOB_RECURSE HEADER_FILES "${CMAKE_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/sources/*.cpp")

add_executable(SiberianGameJam main.cpp ${HEADER_FILES} ${SOURCE_FILES} include/TileMap.h)

target_link_libraries(SiberianGameJam sfml-graphics sfml-audio sfml-window sfml-system)