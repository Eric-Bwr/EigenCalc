﻿#This is for Building the whole project
#Nothing for you to do here except you want to include another Library / Change Names of files etc.
cmake_minimum_required (VERSION 3.8)

project (EigenCalc)

set(CMAKE_CXX_STANDARD 17)

set (SOURCE_FILES 
	${PROJECT_NAME}/Application.h
	${PROJECT_NAME}/Application.cpp
	${PROJECT_NAME}/FileStream.h
	${PROJECT_NAME}/FileStream.cpp
)

include_directories(Dependencies)

set(dir ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(Dependencies/Eigen)
include_directories(${PROJECT_NAME})

add_executable (${PROJECT_NAME} ${SOURCE_FILES})
