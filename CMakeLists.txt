cmake_minimum_required(VERSION 3.9)

set(DEFAULT_BUILD_TYPE "Release")

project(Alfodr 
        VERSION 0.0.1
        DESCRIPTION "Library Alfodr : multi tools for c++ application")

include(GNUInstallDirs)
#Liste des header
file(GLOB_RECURSE HEADERS "include/*.h")

# Listes des fichiers CPP à compiler
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(${PROJECT_NAME} SHARED
                
                src/Types/Interval.cpp
                src/Types/Parameter.cpp

                src/Tools/Chrono/Chrono.cpp
                src/Tools/CSV/Column.cpp
                src/Tools/CSV/Table.cpp
                src/Tools/CSV/FileCSV.cpp
                
                src/Tools/JSON/Objet.cpp
                src/Tools/JSON/Pair.cpp
                src/Tools/JSON/Value.cpp
                src/Tools/JSON/JSONFile.cpp

                src/Tools/Chrono/Chrono.cpp
                
                src/SoftwareManager/User/Setup.cpp
                #src/SoftwareManager/User/User.cpp
                src/SoftwareManager/User/Logs.cpp

                src/SoftwareManager/ArgumentReader.cpp
                src/SoftwareManager/SoftwareManager.cpp)


# Definition de compilation
if (UNIX)
    add_definitions(-DLINUX)
endif (UNIX)

# Proprieté de la library

# Header Public
set_target_properties(${PROJECT_NAME} PROPERTIES
                        PUBLIC_HEADER "${HEADERS}")

set_target_properties(  Alfodr PROPERTIES
                        FRAMEWORK TRUE
                        MACOSX_RPATH ON
                        
                        VERSION ${PROJECT_VERSION}
                                        )

set(CMAKE_SKIP_BUILD_RPATH  FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib64")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib64")
                        
                                        
# Install
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/" # source directory
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}"# target directory
)

configure_file(${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

execute_process (COMMAND bash -c "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib"
    OUTPUT_VARIABLE outVar
)

# Install for CMake
install(TARGETS ${PROJECT_NAME} 
        EXPORT ${PROJECT_NAME}Config
        ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
install(EXPORT ${PROJECT_NAME}Config DESTINATION share/${PROJECT_NAME}/cmake)
export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}Config.cmake)
