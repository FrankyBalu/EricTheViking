#include "../liberic/Game.hpp"
#include "../liberic/GameStateFactory.hpp"
#include "../liberic/GameStateMaschine.hpp"
#include "../liberic/GameObjectFactory.hpp"
#include "Menu.hpp"
#include "PlayState.hpp"
#include "Marker.hpp"
#include "Gateway.hpp"
#include "../liberic/Log.hpp"


int main (){
    LibEric::Game::Instance()->Init("Erik der Wikinger");

    LibEric::GameStateFactory::Instance()->RegisterType("Menu", new Eric::MenuCreator());
    LibEric::GameStateFactory::Instance()->RegisterType("Play", new Eric::PlayCreator());

    LibEric::GameObjectFactory::Instance()->RegisterType("Marker", new Eric::MarkerCreator());
    LibEric::GameObjectFactory::Instance()->RegisterType("Gateway", new Eric::GatewayCreator());

    LibEric::GameStateMaschine::Instance()->ChangeState("Menu", "Main.menu");
    while (LibEric::Game::Instance()->Running()){
        LibEric::Game::Instance()->HandleEvents();
        LibEric::Game::Instance()->Update();
        LibEric::Game::Instance()->Render();
    }
    LibEric::Game::Instance()->Clean();
    return 0;
}
