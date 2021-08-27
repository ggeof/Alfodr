cmake_minimum_required(VERSION 3.9)

project(Alfodr VERSION 0.0.1 DESCRIPTION "Library Alfodr : multi tools for c++ application")

add_library(Alfodr SHARED
                src/Types/Interval.cpp
                src/Types/Parameter.cpp
                src/Tools/Chrono/Chrono.cpp)


# Propriet� sur les versions
set_target_properties(Alfodr PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(Alfodr PROPERTIES SOVERSION 1)

# Header Public
set_target_properties(Alfodr PROPERTIES PUBLIC_HEADER
                                include/Alfodr.h
                                        )


target_include_directories(Alfodr PRIVATE include)
target_include_directories(Alfodr PRIVATE src)

include(GNUInstallDirs)
install(TARGETS Alfodr
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

configure_file(Alfodr.pc.in Alfodr.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/Alfodr.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)