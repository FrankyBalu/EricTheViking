/*
 * LibEric
 * Copyright (C) 2021  Frank Kartheuser <frank.kartheuser1988@gmail.com>
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


#include "GameStateFactory.hpp"
#include "Log.hpp"

LibEric::GameStateFactory *LibEric::GameStateFactory::_Instance = nullptr;

bool LibEric::GameStateFactory::RegisterType(std::string typeID, StateBaseCreator* creator)
{
    PLOGI << "Regestriere GameState: " << typeID;

    //Überprüfen, ob schon ein Creator mit der ID vorhanden ist
    std::map<std::string,StateBaseCreator*>::iterator it = _Creators.find(typeID);
    bool success = _Creators.end() == it;
    if (success) {
        PLOGI << "\tStatecreator erfolgreich erstellt";
        _Creators[typeID] = creator;
    }
    else {
        PLOGW << "\t" << typeID << ": " << "Statecreator mit dieser ID existiert bereits";
        delete creator;
    }
    return success;
}

LibEric::GameState * LibEric::GameStateFactory::Create(std::string typeID)
{
    //Überprüfen, ob schon ein Creator mit der ID vorhanden ist
    std::map<std::string, StateBaseCreator*>::iterator iterator = _Creators.find(typeID);
    bool success = _Creators.end() == iterator;
    GameState* result;
    if (!success) {
        PLOGI << "Erstelle neuen State vom Typ: " << typeID;
        StateBaseCreator* creator = (*iterator).second;
        result = creator->CreateState();
    }
    else {
        PLOGE << "\tKann State nicht erstellen: Unbekannter Typ " << typeID;
        result = nullptr;
    }
    return result;
}


