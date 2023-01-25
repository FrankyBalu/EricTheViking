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



#include "GameObjectFactory.hpp"
#include "Log.hpp"

LibEric::GameObjectFactory *LibEric::GameObjectFactory::_Instance = nullptr;

bool LibEric::GameObjectFactory::RegisterType(std::string typeID, BaseCreator* creator)
{
    PLOGI << "Regestriere GameObjekt Type: " << typeID;

    //Überprüfen, ob schon ein Creator mit der ID vorhanden ist
    std::map<std::string,BaseCreator*>::iterator it = _Creators.find(typeID);
    bool success = _Creators.end() == it;
    if (success) {
        PLOGI << "\tObjectcreator erfolgreich erstellt";
        _Creators[typeID] = creator;
    }
    else {
        PLOGW << "\t" << typeID << ": " << "Gameobjectcreator mit dieser ID existiert bereits";
        delete creator;
    }
    return success;
}

LibEric::GameObject * LibEric::GameObjectFactory::Create(std::string typeID)
{
    //Überprüfen, ob schon ein Creator mit der ID vorhanden ist
    std::map<std::string, BaseCreator*>::iterator iterator = _Creators.find(typeID);
    bool success = _Creators.end() == iterator;
    GameObject* result;
    if (!success) {
        PLOGI << "Erstelle neues Object vom Typ: " << typeID;
        BaseCreator* creator = (*iterator).second;
        result = creator->CreateObject();
    }
    else {
        PLOGE << "\tKann Gameobject nicht erstellen: Unbekannter Typ " << typeID;
        result = nullptr;
    }
    return result;
}


