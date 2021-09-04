cmake_minimum_required(VERSION 3.9)

project(Alfodr 
        VERSION 0.0.1
        DESCRIPTION "Library Alfodr : multi tools for c++ application")

include(GNUInstallDirs)

#Liste des header
file(GLOB_RECURSE INCLUDES_FILES "include/*.h")

# Listes des fichiers CPP à compiler
add_library(Alfodr SHARED
                ${INCLUDES_FILES}
                
                src/Types/Interval.cpp
                src/Types/Parameter.cpp

                src/Tools/Chrono/Chrono.cpp
                src/Tools/CSV/Column.cpp
                src/Tools/CSV/Table.cpp
                src/Tools/CSV/FileCSV.cpp

                )



# Proprieté de la library

# Header Public
set_target_properties(Alfodr PROPERTIES PUBLIC_HEADER
                                "${INCLUDES_FILES}"
                                        )


set_target_properties(  Alfodr PROPERTIES
                        FRAMEWORK TRUE
                        MACOSX_RPATH ON
                    
                        VERSION ${PROJECT_VERSION}
                                        )

set(CMAKE_SKIP_BUILD_RPATH  FALSE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib64")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib64")


target_include_directories(Alfodr PUBLIC include)
target_include_directories(Alfodr PRIVATE src)

install(TARGETS Alfodr
        EXPORT Alfodr
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libalfodr
        RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR})
      
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/" # source directory
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/libalfodr"# target directory
        )

configure_file(Alfodr.pc.in Alfodr.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/Alfodr.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

execute_process (COMMAND bash -c "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib"
    OUTPUT_VARIABLE outVar
)