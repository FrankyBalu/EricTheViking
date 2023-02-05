/*
 * LibEric
 * Copyright (C) 2022  Frank Kartheuser <frank.kartheuser1988@gmail.com>
 * Copyright (C) 2023  Frank Kartheuser <frank.kartheuser1988@gmail.com>
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

#include <libEric/Core/GameStateFactory.hpp>
#include <libEric/Core/Log.hpp>

LibEric::GameStateFactory *LibEric::GameStateFactory::_Instance = nullptr;

LibEric::GameStateFactory *LibEric::GameStateFactory::Instance() {
    if (_Instance == nullptr)
        _Instance = new GameStateFactory();
    return _Instance;
}

bool LibEric::GameStateFactory::RegisterType(std::string typeID, StateBaseCreator *creator) {
    if (_Creators.count(typeID) != 0) {
        LOGE("Kann Gamestate mit ID <", typeID, "> nicht regestrieren: ID bereits vorhanden");
        delete creator;
        return false;
    }
    LOGI("Registriere neuen Gamestate mit ID: ", typeID);
    _Creators[typeID] = creator;
    return true;
}

LibEric::GameState *LibEric::GameStateFactory::Create(std::string typeID) {
    if (_Creators.count(typeID) == 0) {
        LOGE("Kann GameState mit ID <", typeID, "> nicht erstellen: ID unbekannt");
        return nullptr;
    }
    return _Creators[typeID]->CreateState();
}