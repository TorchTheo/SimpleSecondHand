cmake_minimum_required(VERSION 3.17)
project(Project1)

set(CMAKE_CXX_STANDARD 14)
set(ENV{TERM} "xterm-256color")
add_executable(Project1 main.cpp Manager.cpp Manager.h User.cpp User.h Commodity.cpp Commodity.h Order.cpp Order.h Admin.cpp Admin.h)