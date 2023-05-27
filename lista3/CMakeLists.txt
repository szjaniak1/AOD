cmake_minimum_required(VERSION 3.26.4)

project(AOD3)

add_executable(${PROJECT_NAME} main.cpp)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

add_library(graph lib.cpp)
add_library(radixheap radixheap.cpp)

set_target_properties(graph PROPERTIES PUBLIC_HEADER lib.hpp)
set_target_properties(radixheap PROPERTIES PUBLIC_HEADER radixheap.hpp)

install(TARGETS graph radixheap LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION include)

target_link_libraries(${PROJECT_NAME} graph)
target_link_libraries(${PROJECT_NAME} radixheap)
