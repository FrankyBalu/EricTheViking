cmake_minimum_required(VERSION 3.24)

project(Eric VERSION 0.0.1
        DESCRIPTION "libEric ist als eine Art Framework zum erstellen von Spielen gedacht. Eric ist ein Beispiel dafür"
        LANGUAGES CXX)

#C++ Standart auf c++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FeatureSummary)

option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)


#Abbrechen wenn Windows verwendet wird, geht eh nicht
if (WIN32)
    message("Windows wird zur Zeit noch nicht unterstützt")
    return()
endif ()

########################################################################################################################
#                                                                                                                      #
#   Testen ob Doxygen vorhanden ist, um die API-Dokumentation zu generieren                                            #
#                                                                                                                      #
########################################################################################################################
find_package(Doxygen)
if (Doxygen_FOUND)
    add_subdirectory(docs)
else ()
    message(STATUS "Doxygen not found, not building docs")
endif ()
add_feature_info("Doxygen" Doxygen_FOUND "Generate API doc mir make doc")

########################################################################################################################
#                                                                                                                      #
#   Testen ob Librarys im system installiert sind oder ob die interne Kopie benutzt werden muss                        #
#                                                                                                                      #
########################################################################################################################

find_package(Lua REQUIRED 5.4)

find_package(tinyxml2 REQUIRED)

#Sollte unter Linux immer vorhanden sein, glaub ich zumindest
find_package(ZLIB REQUIRED)
find_package(PhysFS 3.2 REQUIRED)

set(RAYLIB_VERSION 4.2.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/heads/master.zip
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL " " FORCE) # don't build the supplied examples
        set(BUILD_SHARED_LIBS OFF)
        set(USE_EXTERNAL_GLFW OFF)
        set(CMAKE_BUILD_TYPE Release)
        set(WITH_PIC TRUE)
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR} EXCLUDE_FROM_ALL)
    endif ()
    include_directories(" ${raylib_SOURCE_DIR}/src")
endif ()

add_feature_info("System lua" LUA_FOUND "")
add_feature_info("System zlib" ZLIB_FOUND "")
add_feature_info("System tinyxml2" TINYXML2_FOUND "")

########################################################################################################################
#                                                                                                                      #
#   Include Verzeichnisse hinzufügen                                                                                   #
#                                                                                                                      #
########################################################################################################################
include_directories(
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}"
        "${PROJECT_SOURCE_DIR}/Extra/"
        "${LUA_INCLUDE_DIR}"
)


########################################################################################################################
#                                                                                                                      #
#   Datenverzeichnis Festlegen, wo die assets zu finden sind                                                           #
#                                                                                                                      #
########################################################################################################################
if (LINUX)
    set(DATA_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")
    set(INSTALL_PREFIX DATA_INSTALL_PREFIX)
elseif (WIN32)
    #Windows wird noch nicht unterstützt, kommt aber sicher noch irgendwann
    set(DATA_INSTALL_PREFIX "data/")
    set(INSTALL_PREFIX DATA_INSTALL_PREFIX)
endif ()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    set(DEBUG 1)
endif()

configure_file(Config.hpp.in Config.hpp)


########################################################################################################################
#                                                                                                                      #
#   Die ganzen unterverzeichnisse hinzufügen                                                                           #
#                                                                                                                      #
########################################################################################################################
add_subdirectory(Extra)
add_subdirectory(libEric)
add_subdirectory(eric)
add_subdirectory(data)
message("  ")
feature_summary(WHAT ENABLED_FEATURES DESCRIPTION "Enabled features:")
feature_summary(WHAT DISABLED_FEATURES DESCRIPTION "Disabled features: ")
