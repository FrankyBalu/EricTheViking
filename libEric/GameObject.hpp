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


#ifndef __GAMEOBJECT
#define __GAMEOBJECT


#include <string>
#include <raylib.h>

namespace LibEric {

class GameObject {
public:

    //Um das Object auf den Bildschirm dar zu stellen
    virtual void Draw() = 0;

    //Inderne Logik des Objektes abarbeiten
    virtual void Update() = 0;

    //Speicher aufräumen
    virtual void Clean() = 0;

    //Scriptdatei laden
    virtual void Load(const std::string script) = 0;

    //Position und größe festlegen
    virtual void SetPosition (float x, float y) = 0;
    virtual void SetWidth (float w) = 0;
    virtual void SetHeight (float h) = 0;

    virtual Rectangle GetCollisionRect () = 0;
    virtual Rectangle GetActionRect () = 0;

protected:

    GameObject() {}
    virtual ~GameObject() {}
};

}; //namespace LibEric
#endif /* __GAMEOBJECT */
