project(LibEric)

# Local source files here
SET(LIBEric_SRC
        base64.cpp
        base64.h
        Log.cpp
        Log.hpp
        LibEricSettings.cpp
        LibEricSettings.hpp
        Game.cpp
        Game.hpp
        UserSettings.cpp
        UserSettings.hpp
        RenderManager.cpp
        RenderManager.hpp
        GameState.hpp
        GameStateMaschine.cpp
        GameStateMaschine.hpp
        GameStateFactory.cpp
        GameStateFactory.hpp
        Lua.cpp
        Lua.hpp
        Menu.hpp
        Menu.cpp
        Dialog.cpp
        Dialog.hpp
        GameObject_Interface.hpp
        GameObjectFactory.cpp
        GameObjectFactory.hpp
        Layer.hpp
        StoryNode.cpp
        StoryNode.hpp
        Input.cpp Input.hpp
        GraphicGameObject.hpp
        GraphicGameObject.cpp
        GameObjectManager.cpp
        GameObjectManager.hpp
        CollisionManager.cpp
        CollisionManager.hpp
        Map.hpp
        Map.cpp
        TileLayer.cpp
        ObjectLayer.hpp
        ObjectLayer.cpp
        MapManager.hpp
        MapManager.cpp
        MapParser.cpp
        Rectangle.hpp Animation.cpp Animation.hpp Sprite.cpp Sprite.hpp libEric.hpp libEric.hpp)
if (UNIX)
    add_library(Eric SHARED ${LIBEric_SRC})
else ()
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    add_library(Eric SHARED ${LIBEric_SRC} ../Extra/tinyxml2/tinyxml2.cpp)
endif ()

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

install(TARGETS Eric
        EXPORT Eric
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        )

INSTALL(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/ DESTINATION ${CMAKE_INSTALL_PREFIX}/include/libEric
        FILES_MATCHING PATTERN "*.h*")
