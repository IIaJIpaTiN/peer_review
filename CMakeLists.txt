cmake_minimum_required(VERSION 3.24)
project(peer_review)

set(CMAKE_CXX_STANDARD 17)

include_directories(task-1)
include_directories(task-2)
include_directories(task-3)

add_executable(task-1 task-1/ebook.cpp)

add_executable(task-2
        task-2/main.cpp
        task-2/domain_checker.h
        task-2/domain_checker_test.h)

add_executable(task-3
        task-3/ParseCitySubjson.cpp
        task-3/CheckDateTimeValidity.cpp
        task-3/LoadPerson.cpp)
