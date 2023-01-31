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

#include <libEric/GameObjectFactory.hpp>
#include <libEric/Log.hpp>

LibEric::GameObjectFactory *LibEric::GameObjectFactory::_Instance = nullptr;

bool LibEric::GameObjectFactory::RegisterType(std::string typeID, BaseCreator *creator) {
    if (_Creators.count(typeID) != 0) {
        LOGE("Ein Klasse mit Type <", typeID, "> wurde bereits registriert");
        delete creator;
        return false;
    } else {
        _Creators[typeID] = creator;
        LOGD("Neue Klasse mit Type <", typeID, "> registriert");
        return true;
    }
}

LibEric::GameObject_Interface *LibEric::GameObjectFactory::Create(std::string typeID) {
    if (_Creators.count(typeID) != 0) {
        BaseCreator *creator = _Creators[typeID];
        LOGD ("Erstelle ein Objekt vom Type: ", typeID);
        return creator->CreateObject();
    } else {
        LOGE ("Kann Gameobjekt nicht erstellen: Unbekannter Typ ", typeID);
        return nullptr;
    }
}
