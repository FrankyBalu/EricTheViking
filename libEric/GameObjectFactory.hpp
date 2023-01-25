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



#ifndef __GAMEOBJECTFACTORY
#define __GAMEOBJECTFACTORY

#include <string>
#include <map>
#include "GameObject.hpp"

namespace LibEric {

//Von dieser Klasse müssen alle ObjectCreators abgeleitet werden,
//damit die objecte dynamisch aus dateien geladen werden können
class BaseCreator
{
public:
    //Gibt einen Zeiger auf ein erstelltes GameObject (egal welcher Type) zurück
    virtual GameObject* CreateObject() const = 0;
    virtual ~BaseCreator() {}
};

//Erstellt die GameObjekte
class GameObjectFactory
{
public:

    //Neuen Typen regestrieren, um dynamisch Objekte zu erstellen
    bool RegisterType(std::string typeID, BaseCreator* creator);

    //Neues Objekt erstellen
    GameObject* Create(std::string typeID);

    //Damit die Klasse ein Singleton ist, wir brauchen ja nur eine Instanze
    static GameObjectFactory* Instance()
    {
        if (_Instance == nullptr)
            _Instance = new GameObjectFactory();
        return _Instance;
    }

private:


    GameObjectFactory():_Creators() {}

    std::map<std::string, BaseCreator*> _Creators;

    static GameObjectFactory *_Instance;
};

}; //namespace LibEric
#endif // __GAMEOBJECTFACTORY