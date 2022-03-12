cmake_minimum_required(VERSION 3.10.0)
project(csvparser)

add_library(csvparser
        src/cast/cast.c
        src/free/free.c
        src/read/read.c
        src/select/select.c
        src/ignore/ignore.c
        src/csvinternal.c
        )
target_include_directories(csvparser PUBLIC include/)
set_target_properties(csvparser PROPERTIES PUBLIC_HEADER include/csvparser.h)

include(GNUInstallDirs)

install(TARGETS csvparser
        PUBLIC_HEADER
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/csvparser)

#add_executable(csvtesting csv_testing.c)
#target_link_libraries(csvtesting csvparser)