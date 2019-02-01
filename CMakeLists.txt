cmake_minimum_required(VERSION 3.13)
project(tic_tac_toe)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(SFML 2 COMPONENTS graphics audio network window system REQUIRED)

add_executable(server src/server.cpp src/map.cpp include/map.h include/network.h)
add_executable(client src/client.cpp src/map.cpp include/map.h include/network.h)

include_directories(${SFML_INCLUDE_DIR})
include_directories(include)

target_link_libraries(server ${SFML_LIBRARIES})
target_link_libraries(client ${SFML_LIBRARIES})