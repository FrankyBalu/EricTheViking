/*
 * Eric The Viking
 * Copyright (C) 2022  Frank Kartheuser <frank.kartheuser1988@gmail.com>
 * Copyright (C) 2022  Frank Kartheuser <frank.kartheuser1988@gmail.com>
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

#ifndef __MARKER
#define __MARKER

#include "../liberic/GraphicGameObject.hpp"
#include "../liberic/GameObjectFactory.hpp"
#define SOL_ALL_SAFETIES_ON 1
#include "../Extra/sol/sol.hpp"
#include "../liberic/Log.hpp"

namespace Eric {

class Marker : public LibEric::GraphicGameObject
{
public:
    Marker();

    void Draw() override;
    void Update() override;
    void Clean () override;

    void SetText (std::string text);

    void Load(const std::string script) override;

    void SetPosition (float x, float y) override
    {
        GraphicGameObject::SetPosition(x, y);
    }
    void SetWidth (float w) override
    {
        GraphicGameObject::SetWidth(w);
    }
    void SetHeight (float h) override{
        GraphicGameObject::SetHeight(h);
    }
    Rectangle GetActionRect() override{return _ObjectCollision;}
    Rectangle GetCollisionRect() override{return _ObjectCollision;}


private:

    std::string _Text;

    sol::state lua;

    sol::function _LUA_Update;
    sol::function _LUA_Draw;
    sol::function _LUA_GetText;

};

class MarkerCreator : public LibEric::BaseCreator {
public:
    LibEric::GameObject* CreateObject() const {
        return  new Marker();
    }
};

}; //namespace Eric
#endif // ENEMY_H
