project(LibEric)

# Local source files here
SET(LIBERIC_CORE_SRC
        core/base64.cpp
        core/base64.h
        core/CollisionManager.cpp
        core/CollisionManager.hpp
        core/GameObject_Interface.hpp
        core/GameObjectFactory.cpp
        core/GameObjectFactory.hpp
        core/GameObjectManager.cpp
        core/GameObjectManager.hpp
        core/GameState.hpp
        core/GameStateFactory.cpp
        core/GameStateFactory.hpp
        core/GameStateMaschine.cpp
        core/GameStateMaschine.hpp
        core/Input.cpp
        core/Input.hpp
        core/LibEricApp.cpp
        core/LibEricApp.hpp
        core/LibEricSettings.cpp
        core/LibEricSettings.hpp
        core/Log.cpp
        core/Log.hpp
        core/Lua.cpp
        core/Lua.hpp
        core/Rectangle.hpp
        core/UserSettings.cpp
        core/UserSettings.hpp
        )

SET(LIBERIC_GRAPHIC_SRC
        Graphic/Animation.cpp
        Graphic/Animation.hpp
        Graphic/Dialog.cpp
        Graphic/Dialog.hpp
        Graphic/GraphicGameObject.hpp
        Graphic/GraphicGameObject.cpp
        Graphic/Menu.hpp
        Graphic/Menu.cpp
        Graphic/RenderManager.cpp
        Graphic/RenderManager.hpp
        Graphic/Sprite.cpp
        Graphic/Sprite.hpp
        )

SET(LIBERIC_MAPS_SRC
        Maps/Layer.hpp
        Maps/Map.hpp
        Maps/Map.cpp
        Maps/MapManager.hpp
        Maps/MapManager.cpp
        Maps/MapParser.cpp
        Maps/MapParser.hpp
        Maps/ObjectLayer.hpp
        Maps/ObjectLayer.cpp
        Maps/TileLayer.cpp
        )

SET(LIBERIC_SRC
        StoryNode.cpp
        StoryNode.hpp
        libEric_API.hpp
        )
if (WIN32)
    set(EXTRA_SRC
            core/Windows.cpp
            core/Windows.hpp
            ../Extra/tinyxml2/tinyxml2.cpp
            )
else ()
    set(EXTRA_SRC
            core/Linux.cpp
            core/Linux.hpp
            )
endif ()

if (UNIX)
    add_library(Eric  ${LIBERIC_SRC} ${LIBERIC_CORE_SRC} ${LIBERIC_GRAPHIC_SRC} ${LIBERIC_MAPS_SRC} ${EXTRA_SRC})
else ()
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    add_library(Eric  ${LIBERIC_SRC} ${LIBERIC_CORE_SRC} ${LIBERIC_GRAPHIC_SRC} ${LIBERIC_MAPS_SRC} ${EXTRA_SRC})
endif ()

add_dependencies(Eric version)

if (UNIX)
    target_link_libraries(Eric ${LUA_LIBRARY}
            raylib
            tinyxml2
            z
            physfs
            )
else ()
    target_link_libraries(Eric lua54.lib
            raylibdll.lib
            libz.lib
            physfs.lib
            )
endif ()

if (UNIX)
install(TARGETS Eric
        EXPORT Eric
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        )

INSTALL(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/ DESTINATION ${CMAKE_INSTALL_PREFIX}/include/libEric
        FILES_MATCHING PATTERN "*.h*")
elseif (WIN32)
    install(TARGETS Eric
            EXPORT Eric
            LIBRARY DESTINATION "${PROJECT_BINARY_DIR}/../bin"
            ARCHIVE DESTINATION "${PROJECT_BINARY_DIR}/../bin"
            RUNTIME DESTINATION "${PROJECT_BINARY_DIR}/../bin"
            )
endif()
