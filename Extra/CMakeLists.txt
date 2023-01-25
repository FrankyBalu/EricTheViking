if (NOT ERIK_SYSTEM_TINYXML2)
    add_subdirectory(tinyxml2 EXCLUDE_FROM_ALL)
endif ()

if (NOT ERIK_SYSTEM_ZLIB)
    add_subdirectory(zlib EXCLUDE_FROM_ALL)
endif ()

if (NOT ERIC_SYSTEM_LUA)
    add_subdirectory(lua EXCLUDE_FROM_ALL)
endif()