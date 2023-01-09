project(LibEric)

SET(LIBEric_HPP
    base64.h
    Dialog.hpp
    PrivateSettings.hpp
    Game.hpp
    GameObjectFactory.hpp
    GameObject.hpp
    GameStateFactory.hpp
    GameState.hpp
    GameStateMaschine.hpp
    Global_LUA.hpp
    GraphicGameObject.hpp
    Layer.hpp
    Log.hpp
    Map.hpp
    MapManager.hpp
    MapParser.hpp
    ObjectLayer.hpp
    UserSettings.hpp
    StoryNode.hpp
    TextureManager.hpp
    TileLayer.hpp
   )

# Local source files here
SET(LIBEric_SRC
    base64.cpp
    Dialog.cpp
    PrivateSettings.cpp
    Game.cpp
    GameObjectFactory.cpp
    GameStateFactory.cpp
    GameStateMaschine.cpp
    Global_LUA.cpp
    GraphicGameObject.cpp
    Log.cpp
    Map.cpp
    MapManager.cpp
    MapParser.cpp
    ObjectLayer.cpp
    UserSettings.cpp
    StoryNode.cpp
    TextureManager.cpp
    TileLayer.cpp
    )

add_library(Eric ${LIBEric_SRC})

target_link_libraries(Eric lua_shared
                             raylib
                             tinyxml2
                             z
                             )
#target_include_directories(${PROJECT_NAME} PUBLIC include)
