cmake_minimum_required(VERSION 3.13)
project(tic_tac_toe)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(SFML 2 COMPONENTS graphics audio network window system REQUIRED)

add_executable(server src/server.cpp)
add_executable(client src/client.cpp)

target_link_libraries(server ${SFML_LIBRARIES})
target_link_libraries(client ${SFML_LIBRARIES})