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

#include "Gateway.hpp"
#include "../liberic/Global_LUA.hpp"
#include "../liberic/GraphicGameObject.hpp"
#include "Player.hpp"
#include <raylib.h>

Eric::Gateway::Gateway()
    : GraphicGameObject(){
}

void Eric::Gateway::Draw()
{
    GraphicGameObject::Draw();
}

void Eric::Gateway::Clean()
{
    GraphicGameObject::Clean();
}

void Eric::Gateway::Update()
{
    if (Player::Instance()->CollisionDetect(this)) {
        _LUA_Enter();
    }
    _LUA_Update();
}

void Eric::Gateway::ChangeToMap(std::string map){

}




void Eric::Gateway::Load(const std::string scriptFile){
    lua.open_libraries(sol::lib::base);
    lua.open_libraries(sol::lib::string);

    LibEric::LuaSetup(&lua);

     std::string EricDir = std::string (getenv("HOME")) + std::string ("/.Eric/");

    lua.set_function("ChangeToMap", &Gateway::ChangeToMap);

    lua.new_usertype<Player>("Player",
        "new", sol::no_constructor,
        "Instance", &Player::Instance,
        "SetPosition", &Player::SetPosition
        );

    lua.script_file (EricDir + scriptFile);

    _ObjectCollision.x = _Position.x + ((_Width - 10)/2);
    _ObjectCollision.y = _Position.y + (_Height-10);
    _ObjectCollision.width = 10;
    _ObjectCollision.height = 10;

    _LUA_Update = lua["Update"];
    _LUA_Draw = lua["Draw"];
    _LUA_Enter = lua["EnterGateway"];

}
