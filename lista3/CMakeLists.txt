cmake_minimum_required(VERSION 3.26.4)

project(AOD3)

add_executable(${PROJECT_NAME} main.cpp)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

add_library(graph lib.cpp)

set_target_properties(graph PROPERTIES PUBLIC_HEADER lib.hpp)

install(TARGETS graph LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION include)

target_link_libraries(${PROJECT_NAME} graph)
