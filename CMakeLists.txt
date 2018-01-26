cmake_minimum_required(VERSION 3.5)
project(CppPractice)

#################################################
# CMAKE SETTINGS
#################################################

# variable to control de verbosity of the custom functions
set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include (Modules/download_file)


#################################################
# COMPILER SETTINGS
#################################################
message(STATUS "Configuring for Unix system")
set (CMAKE_CXX_COMPILER         "clang")
set (CMAKE_CXX_FLAGS            "-std=c++14 -O0 -Wall")


#################################################
# CATCH SETTINGS
#################################################
enable_testing()
include(cmake/thirdparty/Catch.cmake)


#################################################
# THIRD PARTY SETTINGS
#################################################
include(cmake/thirdparty/JSON.cmake)


#################################################
# SOURCE FILES SETTINGS
#################################################
add_subdirectory(visitor)
