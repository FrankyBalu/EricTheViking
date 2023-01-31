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

#include <libEric/Log.hpp>
#include <libEric/Game.hpp>
#include <libEric/LibEricSettings.hpp>
#include <libEric/RenderManager.hpp>
#include <libEric/GameStateMaschine.hpp>
#include <libEric/Menu.hpp>
#include "Marker.hpp"
#include "PlayState.hpp"

int main() {
    if (!LibEric::Game::Instance()->Init("EricTheViking")) {
        LOGE("Konnte libEric nicht Initialisieren!\nAbbruch!");
        return 1;
    }

    LibEric::RenderManager::Instance()->LoadTextureFromFile("BGI", "assets/Background.png");

    if (!LibEric::GameStateFactory::Instance()->RegisterType("Menu", new LibEric::MenuCreator())) {
        LOGE("Konnte Type <Menu> nicht regestrieren: Breche ab!");
        return 1;
    }
    if (!LibEric::GameStateFactory::Instance()->RegisterType("Play", new Eric::PlayCreator())) {
        LOGE("Konnte Type <Play> nicht regestrieren: Breche ab!");
        return 1;
    }

    if (!LibEric::GameStateMaschine::Instance()->ChangeState("Menu", "MainMenu.lua")) {
        LOGE ("Konnte nicht zu MeinMenu.lua wechseln! Abbruch");
        return 1;
    }

    LibEric::GameObjectFactory::Instance()->RegisterType("Marker", new Eric::MarkerCreator());
    //scheinbar ein Fehler in meiner Arch Linux installation, aber bei mir funktioniert 0 nicht
    LibEric::Game::Instance()->SetGamepad(3);

    LibEric::Game::Instance()->Run();

    LibEric::RenderManager::Instance()->ClearRenderManager();
    return 0;
}
