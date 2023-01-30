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

#include "Marker.hpp"
#include "Player.hpp"
#include <libEric/Game.hpp>
#include <libEric/Dialog.hpp>
#include <libEric/StoryNode.hpp>
#include <libEric/Lua.hpp>
#include <raylib.h>
#include <Config.hpp>

Eric::Marker::Marker()
    : LibEric::GraphicGameObject()
{

}

void Eric::Marker::Draw()
{
    GraphicGameObject::Draw();
    //_LUA_Draw();
}

void Eric::Marker::Clean()
{
    GraphicGameObject::Clean();
}

void Eric::Marker::Update()
{
   /* if (CheckCollisionRecs(Player::Instance()->GetObject(), _ObjectCollision ) ){

        if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)||IsKeyPressed(KEY_DOWN)) {
            LibEric::Dialog::Instance()->SetMSG(_LUA_GetText());
        }
    }*/
    _LUA_Update();

}

void Eric::Marker::SetText(std::string text){
    _Text = text;
}



void Eric::Marker::Load(const std::string script){
    lua.open_libraries(sol::lib::base);
    lua.open_libraries(sol::lib::string);


    LibEric::LuaSetup(&lua);

    std::string EricDir = std::string (INSTALL_PREFIX) + std::string ("/share/EricTheViking/");
    lua.script_file (EricDir + script);



    _LUA_Update = lua["Update"];
    _LUA_Draw = lua["Draw"];
    _LUA_GetText = lua["GetText"];

}
