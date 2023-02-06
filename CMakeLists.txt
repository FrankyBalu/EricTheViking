cmake_minimum_required(VERSION 3.24)

project(Eric VERSION 0.0.1
        DESCRIPTION "libEric ist als eine Art Framework zum erstellen von Spielen gedacht. Eric ist ein Beispiel dafür"
        LANGUAGES CXX)

#C++ Standart auf c++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FeatureSummary)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)


#Abbrechen wenn Windows verwendet wird, geht eh nicht

if (UNIX)
    add_compile_options(-Wall -Wextra)
elseif(WIN32)
#    add_compile_options(-Wall)
endif()

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
            "Wähle einen Build-Type, möglichkeiten sind: None(CMAKE_CXX_FLAGS oder CMAKE_C_FLAGS benutzen) Debug Release RelWithDebInfo MinSizeRel."
            FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS None Debug Release RelWithDebInfo MinSizeRel)
ENDIF()

if(UNIX)
    # Paths
    SET(BINDIR "${CMAKE_INSTALL_PREFIX}/bin" CACHE PATH "Wo die Programme installiert werden")
    SET(LIBDIR "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}" CACHE PATH "Wo die Libs installiert werden")
    SET(DATAROOTDIR "${CMAKE_INSTALL_PREFIX}/share" CACHE PATH "Wurzelverzeichniss für daten")
    SET(ERIKDATADIR "${CMAKE_INSTALL_PREFIX}/share/games/Erik" CACHE PATH "Datenverzeichnis für Erik")
    SET(LIBERICDATADIR "${CMAKE_INSTALL_PREFIX}/share/libEric" CACHE PATH "LibEric Datenverzeichnis")
    SET(ICONDIR "${DATAROOTDIR}/pixmaps" CACHE PATH "Icon Verzeichnis") #noch haben wir kein icon
else(WIN32)
    SET(ERIKDATADIR "data/" )
    SET(LIBERICDATADIR "data/" )
endif(UNIX)

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

if (UNIX)
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
endif()

########################################################################################################################
#                                                                                                                      #
#   Include Verzeichnisse hinzufügen                                                                                   #
#                                                                                                                      #
########################################################################################################################
if(UNIX)
    include_directories(
            "${PROJECT_BINARY_DIR}"
            "${PROJECT_SOURCE_DIR}"
            "${PROJECT_SOURCE_DIR}/Extra/"
            "${PROJECT_SOURCE_DIR}/Extra/"
            "${LUA_INCLUDE_DIR}"
    )
else()
    include_directories(
            "${PROJECT_SOURCE_DIR}/Extra/lua-5.4.0/include"
            "${PROJECT_SOURCE_DIR}/Extra/physfs-3.2.0/include"
            "${PROJECT_SOURCE_DIR}/Extra/raylib-4.2.0/include"
            "${PROJECT_SOURCE_DIR}/Extra/zlib-1.2.13/"
            "${PROJECT_SOURCE_DIR}/Extra/tinyxml2"
            "${PROJECT_SOURCE_DIR}/Extra/sol"
            "${PROJECT_SOURCE_DIR}/Extra"
            "${PROJECT_SOURCE_DIR}"
            "${PROJECT_BINARY_DIR}"
    )
    link_directories(
            "${PROJECT_SOURCE_DIR}/Extra/lua-5.4.0/lib"
            "${PROJECT_SOURCE_DIR}/Extra/physfs-3.2.0/lib"
            "${PROJECT_SOURCE_DIR}/Extra/raylib-4.2.0/lib"
            "${PROJECT_SOURCE_DIR}/Extra/zlib-1.2.13/"
    )
endif()

########################################################################################################################
#                                                                                                                      #
#   Datenverzeichnis Festlegen, wo die assets zu finden sind                                                           #
#                                                                                                                      #
########################################################################################################################

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    set(DEBUG 1)
endif()

find_package(Git)
add_custom_target(version
        ${CMAKE_COMMAND} -D SRC=${CMAKE_SOURCE_DIR}
        -D DST=${CMAKE_BINARY_DIR}/LibEric_version.h
        -D GIT_EXECUTABLE=${GIT_EXECUTABLE}
        -P ${CMAKE_SOURCE_DIR}/cmake/GenerateVersionHeader.cmake
        )


configure_file(Config_LibEric.hpp.in Config_LibEric.hpp)


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

if(UNIX)
    feature_summary(WHAT ENABLED_FEATURES DESCRIPTION "Enabled features:")
    feature_summary(WHAT DISABLED_FEATURES DESCRIPTION "Disabled features: ")
elseif(WIN32)
    message("Build for Windows")
    message("Nutzen interne kopien von LUA, TINYXML2, PHYSFS und ZLIB")
endif()