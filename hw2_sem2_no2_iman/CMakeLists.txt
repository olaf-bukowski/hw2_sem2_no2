cmake_minimum_required(VERSION 3.5)

project(hw2_sem2_no2_iman LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hw2_sem2_no2_iman main.cpp)

install(TARGETS hw2_sem2_no2_iman
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
