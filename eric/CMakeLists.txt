project(Erik)

SET(Erik_SRC
    erik.cpp
    Gateway.cpp
    Marker.cpp
    Menu.cpp
    Player.cpp
    PlayState.cpp
    )

add_executable(${PROJECT_NAME} ${Erik_SRC})
target_link_libraries(${PROJECT_NAME} PUBLIC Eric
                        lua_shared)

