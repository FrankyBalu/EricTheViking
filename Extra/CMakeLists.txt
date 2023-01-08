if (NOT ERIK_SYSTEM_TINYXML2)
    add_subdirectory(tinyxml2)
endif ()

if (NOT ERIK_SYSTEM_ZLIB)
    add_subdirectory(zlib)
endif ()


add_subdirectory(lua)
