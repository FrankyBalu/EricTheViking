project(Erik)

SET(Erik_SRC
        erik.cpp
        #    Gateway.cpp
        Player.hpp
        Player.cpp
        PlayState.hpp
        PlayState.cpp
       # Marker.hpp
       # Marker.cpp
        )

add_executable(${PROJECT_NAME} ${Erik_SRC})
target_link_libraries(${PROJECT_NAME} PUBLIC Eric
        )

if (UNIX)
    INSTALL(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
elseif(WIN32)
    INSTALL(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_BINARY_DIR}/../bin)
endif()
