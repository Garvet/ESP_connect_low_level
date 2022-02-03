cmake_minimum_required(VERSION 3.21)
project(ESP_connect)

set(CMAKE_CXX_STANDARD 14)

add_executable(ESP_connect main.cpp Transfer_controller/Transfer_controller.hpp Transfer_controller/Transfer_controller.cpp Hal/Hal.cpp Hal/Hal.hpp)
