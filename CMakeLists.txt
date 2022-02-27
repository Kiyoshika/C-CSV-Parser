cmake_minimum_required(VERSION 3.10.0)
project(csvparser)

add_library(csvparser src/csvparser.c)
target_include_directories(csvparser PUBLIC include/)

#add_executable(csvtesting csv_testing.c)
#target_link_libraries(csvtesting csvparser)