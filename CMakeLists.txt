cmake_minimum_required(VERSION 3.10)

project(Eric VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wno-enum-compare)
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
option(ERIC_SYSTEM_TINYXML2 "Use system tinyxml" OFF)
option(ERIC_SYSTEM_ZLIB "Use system zlib" OFF)
option(ERIC_SYSTEM_GLFW "Use system glfw" OFF)


#um eine warnung von CMake zu unterdrücken
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()


include_directories (
                    "${PROJECT_BINARY_DIR}"
                    "${PROJECT_SOURCE_DIR}"
                    )

#Add target to build documents from visual studio.
set(DOXYGEN_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
#set the output directory of the documentation
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/docs)
# sanity check...
message("Doxygen Output ${DOXYGEN_OUTPUT_DIR}")
find_package(Doxygen)

if(DOXYGEN_FOUND)
    # create the output directory where the documentation will live
    file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR})
    # configure our Doxygen configuration file. This will be the input to the doxygen
    # executable
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

# now add the custom target. This will create a build target called 'DOCUMENTATION'
# in your project
ADD_CUSTOM_TARGET(DOCUMENTATION
  COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
  COMMAND ${CMAKE_COMMAND} -E make_directory ${DOXYGEN_OUTPUT_DIR}
  COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${CMAKE_COMMAND} -E echo "Done."
  WORKING_DIRECTORY ${DOXYGEN_OUTPUT_DIR})

endif(DOXYGEN_FOUND)


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
     add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
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
                    "${PROJECT_SOURCE_DIR}/liberic/include"
                    )
add_subdirectory(Extra)
add_subdirectory(liberic)
add_subdirectory(eric)

