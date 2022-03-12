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

include(GNUInstallDirs)

# root directory
install(FILES
        include/csvinternal.h
        include/csvparser.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/csvparser)

# cast/ directory
install(FILES
        include/cast/cast.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/csvparser/cast)

# free/ directory
install(FILES
        include/free/free.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/csvparser/free)

# ignore/ directory
install(FILES
        include/ignore/ignore.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/csvparser/ignore)

# read/ directory
install(FILES
        include/read/read.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/csvparser/read)

# select/ directory
install(FILES
        include/select/select.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/csvparser/select)
