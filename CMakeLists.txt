cmake_minimum_required(VERSION 3.24)
project(peer_review)

set(CMAKE_CXX_STANDARD 17)

include_directories(task-1)

add_executable(task-1 task-1/ebook.cpp)
