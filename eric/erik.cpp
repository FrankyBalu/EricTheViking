/*
 * libEric
 * Copyright (C) 2022   Frank Kartheuser <frank.kartheuser1988@gmail.com>
 * Copyright (C) 2023   Frank Kartheuser <frank.kartheuser1988@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#define ERIC_APP 1
#include <libEric/LibEric.hpp>

#include "Menu.hpp"
#include "PlayState.hpp"
#include "Marker.hpp"
#include "Gateway.hpp"


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
