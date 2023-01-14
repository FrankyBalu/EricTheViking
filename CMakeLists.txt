cmake_minimum_required(VERSION 3.25)

project(Eric VERSION 0.0.1
	DESCRIPTION "libEric ist als eine Art Framework zum erstellen von Spielen gedacht. Eric ist ein Beispiel dafür"
	LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include (FeatureSummary)
add_compile_options(-Wno-enum-compare)
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
option(ERIC_SYSTEM_TINYXML2 "Use system tinyxml" OFF)
option(ERIC_SYSTEM_ZLIB "Use system zlib" OFF)
option(ERIC_SYSTEM_GLFW "Use system glfw" OFF)
option(ERIC_SYSTEM_LUA "Use system lua" OFF)

add_feature_info("System TinyXML2" ERIC_SYSTEM_TINYXML2 "")
add_feature_info("System ZLIB" ERIC_SYSTEM_TINYXML2 "")
add_feature_info("System GLFW" ERIC_SYSTEM_TINYXML2 "")
add_feature_info("System LUA" ERIC_SYSTEM_TINYXML2 "")

if(LINUX)
    message("This is a ${CMAKE_SYSTEM_NAME} system")
elseif(WIN32)
    message("Windows wird zur Zeit noch nicht unterstützt")
endif()

#um eine warnung von CMake zu unterdrücken
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()


include_directories (
                    "${PROJECT_BINARY_DIR}"
                    "${PROJECT_SOURCE_DIR}"
                    )


find_package(Doxygen)
 if(Doxygen_FOUND)
   add_subdirectory(docs)
 else()
   message(STATUS "Doxygen not found, not building docs")
 endif()


# find_package(Lua51  REQUIRED)

#find_package(tinyxml2  REQUIRED)

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
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    set(BUILD_SHARED_LIBS OFF)
    set(USE_EXTERNAL_GLFW ON)
    set(CMAKE_BUILD_TYPE Release)
    set(WITH_PIC ON)
     add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR} EXCLUDE_FROM_ALL)
  endif()
include_directories ("${raylib_SOURCE_DIR}/src")
endif()

include_directories ("${PROJECT_SOURCE_DIR}/Extra/plog-1.1.8/include")
include_directories ("${PROJECT_SOURCE_DIR}/Extra/")
#find_package(raylib 4.2 REQUIRED)

configure_file (Config.hpp.in Config.hpp)
#${PROJECT_SOURCE_DIR}/hello-config.h.in
#${PROJECT_BINARY_DIR}/hello-config.h

include_directories (
                    "${PROJECT_BINARY_DIR}"
                    "${PROJECT_SOURCE_DIR}/liberic"
                    )
add_subdirectory(Extra)
add_subdirectory(liberic)
add_subdirectory(eric)
add_subdirectory(data)

feature_summary(WHAT ENABLED_FEATURES DESCRIPTION "Enabled features:")
feature_summary(WHAT DISABLED_FEATURES DESCRIPTION "Disabled features:")
