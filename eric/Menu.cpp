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


#include "Menu.hpp"
// #include "PlayState.hpp"
#include "../liberic/PrivateSettings.hpp"
#include "../liberic/UserSettings.hpp"
#include "../liberic/Global_LUA.hpp"
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <sstream>
#include <Config.hpp>
#include "../liberic/Log.hpp"



Eric::Button::Button(std::string text, float x, float y, float width, float height){
    _Activ = false;
    _Text = text;
    _Rect.x = x;
    _Rect.y = y;
    _Rect.width = width;
    _Rect.height = height;
}

void Eric::Button::Resize(float x, float y, float width, float height){
    _Rect.x = x;
    _Rect.y = y;
    _Rect.width = width;
    _Rect.height = height;
}


void Eric::Button::Draw(){
    if (_Activ){
        GuiSetState(STATE_FOCUSED);
    }
    else{
        GuiSetState(STATE_NORMAL);
    }

    GuiButton(_Rect, _Text.c_str());
    GuiSetState(STATE_NORMAL);
}

void Eric::Button::SetActiv(bool activ){
    _Activ = activ;
}

Eric::CheckBox::CheckBox(std::string text, float x, float y, float width, float height, bool checked){
    _Activ = false;
    _Rect.x = x;
    _Rect.y = y;
    _Rect.width = width;
    _Rect.height = height;
    _Check = checked;
    _Text = text;
}

void Eric::CheckBox::Resize(float x, float y, float width, float height){
    _Rect.x = x;
    _Rect.y = y;
    _Rect.width = width;
    _Rect.height = height;
}

bool Eric::CheckBox::IsActivated(){
    return _Check;
}

void Eric::CheckBox::Toggle(bool n){
    _Check = n;
}

void Eric::CheckBox::Draw(){
    if (_Activ){
        GuiSetState(STATE_FOCUSED);
    }
    else{
        GuiSetState(STATE_NORMAL);
    }

    GuiCheckBox(_Rect, _Text.c_str(),_Check);
    GuiSetState(STATE_NORMAL);

}

void Eric::CheckBox::SetActiv(bool activ){
    _Activ = activ;
}

Eric::Slider::Slider(std::string text, float x, float y, float width, float height, float currentVal, float minVal, float maxVal){
    _Activ = false;
    _CurrentValue = currentVal;
    _MinValue = minVal;
    _MaxValue = maxVal;
    _Rect.x = x;
    _Rect.y = y;
    _Rect.width = width;
    _Rect.height = height;
    _Text = text;
}

void Eric::Slider::Resize(float x, float y, float width, float height){
    _Rect.x = x;
    _Rect.y = y;
    _Rect.width = width;
    _Rect.height = height;
}


float Eric::Slider::GetValue(){
    return _CurrentValue;
}

void Eric::Slider::SetValue(float val){
    if (val <= 0)
        val = 0.0;
    if (val > 1)
        val = 1.0;
    if (val == 2.77556e-17)
        val = 0;
    _CurrentValue = val;
}


void Eric::Slider::Draw(){
    if (_Activ){
        GuiSetState(STATE_FOCUSED);
    }
    else{
        GuiSetState(STATE_NORMAL);
    }

    std::stringstream ss;
    int i = 100*_CurrentValue;
    if (_CurrentValue == 0.0)
        ss << "0";
    else
        ss << i;

    GuiSliderBar(_Rect, _Text.c_str(),ss.str().c_str(),_CurrentValue, _MinValue, _MaxValue);
    GuiSetState(STATE_NORMAL);
}


void Eric::Slider::SetActiv(bool activ){
    _Activ = activ;
}


void Eric::Menu::Update()
{
    if (IsKeyPressed(KEY_DOWN)||IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) {
        _LUA_Key_Down();
    }
    if (IsKeyPressed(KEY_UP)||IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_UP)) {
        _LUA_Key_Up();
    }
    if (IsKeyPressed(KEY_LEFT)||IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) {
        _LUA_Key_Left();
    }
    if (IsKeyPressed(KEY_RIGHT)||IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) {
        _LUA_Key_Right();
    }
    if (IsKeyPressed(KEY_ENTER)||IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
        _LUA_Key_Activate();
    }
    if (IsKeyPressed(KEY_ESCAPE)||IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_UP)) {
        _LUA_Key_Back();
    }
    _LUA_Update();
}

void Eric::Menu::Render()
{
    _LUA_Draw();

    if (LibEric::PrivateSettings::Instance()->GetShowVersion())
        DrawText(std::string(std::string("Version: ") + std::string("muss noch")).c_str(), 20, LibEric::UserSettings::Instance()->GetWindowHeight()-20, 20, RED);
}

std::string Eric::Menu::GetStateID() const
{
    return _ID;
}




void Eric::Menu::SetID(std::string id){
    PLOGE << "Setzte ID zu " << id;
    _ID = id;
}



bool Eric::Menu::OnEnter(std::string file)
{
    std::string EricDir = std::string (getenv("HOME")) + std::string ("/.Eric/");
    std::string fontFile = EricDir + std::string ("Font.ttf");
    std::string scriptFile(EricDir);


    if (file.empty()){
        scriptFile += std::string ("Menu/MainMenu.lua");
    }
    else {
        scriptFile += std::string ("Menu/") + file;
    }

    _Font = LoadFontEx(fontFile.c_str(), 25, NULL, 0);
    GuiSetFont(_Font);

    lua.open_libraries(sol::lib::base);
    lua.open_libraries(sol::lib::string);

    lua.new_usertype<Button>("Button",
                            sol::constructors<Button(std::string, float, float, float, float)>(),
                             "Draw", &Button::Draw,
                             "Resize", &Button::Resize,
                             "SetActiv", &Button::SetActiv);
    lua.new_usertype<Slider>("Slider",
                            sol::constructors<Slider(std::string, float, float, float, float, float, float, float)>(),
                             "Draw", &Slider::Draw,
                             "Resize", &Slider::Resize,
                             "SetActiv", &Slider::SetActiv,
                             "GetValue", &Slider::GetValue,
                             "SetValue", &Slider::SetValue);
    lua.new_usertype<CheckBox>("CheckBox",
                            sol::constructors<CheckBox(std::string, float, float, float, float, bool)>(),
                             "Draw", &CheckBox::Draw,
                             "Resize", &CheckBox::Resize,
                             "SetActiv", &CheckBox::SetActiv,
                             "IsActivated", &CheckBox::IsActivated,
                             "Toggle", &CheckBox::Toggle);

    
    LibEric::LuaSetup(&lua);
    lua.set_function("SetID", &Menu::SetID);
    lua.script_file (scriptFile);


    _ID = lua["MENUID"];

    _LUA_Update = lua["Update"];
    _LUA_Draw = lua["Draw"];
    _LUA_Key_Up = lua["Key_Up"];
    _LUA_Key_Down = lua["Key_Down"];
    _LUA_Key_Left = lua["Key_Left"];
    _LUA_Key_Right = lua["Key_Right"];
    _LUA_Key_Activate = lua["Activate"];
    _LUA_Key_Back = lua["Back"];


    return true;
}

bool Eric::Menu::OnExit(){
    return true;
}


