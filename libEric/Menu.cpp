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


#include <libEric/Menu.hpp>
#include <libEric/Lua.hpp>
#include <libEric/RenderManager.hpp>
#include <libEric/Game.hpp>
#include <libEric/LibEricSettings.hpp>
#include <Config.hpp>
#include <libEric/Input.hpp>
#include <libEric/Log.hpp>
#include <libEric/Dialog.hpp>
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION

#include <raygui.h>
#include <raylib-physfs.h>
#include <physfs.h>
#include <sstream>


LibEric::Button::Button(std::string text, float x, float y, float width, float height) {
    _Activ = false;
    _Text = text;
    _Rect.x = x;
    _Rect.y = y;
    _Rect.width = width;
    _Rect.height = height;
}

void LibEric::Button::Resize(float x, float y, float width, float height) {
    _Rect.x = x;
    _Rect.y = y;
    _Rect.width = width;
    _Rect.height = height;
}


void LibEric::Button::Draw() {
    if (_Activ) {
        GuiSetState(STATE_FOCUSED);
    } else {
        GuiSetState(STATE_NORMAL);
    }

    GuiButton(_Rect, _Text.c_str());
    GuiSetState(STATE_NORMAL);
}

void LibEric::Button::SetActiv(bool activ) {
    _Activ = activ;
}

LibEric::CheckBox::CheckBox(std::string text, float x, float y, float width, float height, bool checked) {
    _Activ = false;
    _Rect.x = x;
    _Rect.y = y;
    _Rect.width = width;
    _Rect.height = height;
    _Check = checked;
    _Text = text;
}

void LibEric::CheckBox::Resize(float x, float y, float width, float height) {
    _Rect.x = x;
    _Rect.y = y;
    _Rect.width = width;
    _Rect.height = height;
}

bool LibEric::CheckBox::IsActivated() {
    return _Check;
}

void LibEric::CheckBox::Toggle(bool n) {
    _Check = n;
}

void LibEric::CheckBox::Draw() {
    if (_Activ) {
        GuiSetState(STATE_FOCUSED);
    } else {
        GuiSetState(STATE_NORMAL);
    }

    GuiCheckBox(_Rect, _Text.c_str(), _Check);
    GuiSetState(STATE_NORMAL);

}

void LibEric::CheckBox::SetActiv(bool activ) {
    _Activ = activ;
}

LibEric::Slider::Slider(std::string text, float x, float y, float width, float height, float currentVal, float minVal,
                        float maxVal) {
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

void LibEric::Slider::Resize(float x, float y, float width, float height) {
    _Rect.x = x;
    _Rect.y = y;
    _Rect.width = width;
    _Rect.height = height;
}


float LibEric::Slider::GetValue() {
    return _CurrentValue;
}

void LibEric::Slider::SetValue(float val) {
    if (val <= 0)
        val = 0.0;
    if (val > 1)
        val = 1.0;
    if (val == 2.77556e-17)
        val = 0;
    _CurrentValue = val;
}


void LibEric::Slider::Draw() {
    if (_Activ) {
        GuiSetState(STATE_FOCUSED);
    } else {
        GuiSetState(STATE_NORMAL);
    }

    std::stringstream ss;
    int i = 100 * _CurrentValue;
    if (_CurrentValue == 0.0)
        ss << "0";
    else
        ss << i;

    GuiSliderBar(_Rect, _Text.c_str(), ss.str().c_str(), _CurrentValue, _MinValue, _MaxValue);
    GuiSetState(STATE_NORMAL);
}


void LibEric::Slider::SetActiv(bool activ) {
    _Activ = activ;
}


void LibEric::Menu::Update() {
    //   for (int i = 0; i < 3; i++) {
    //       LOGE("Gampad ", i, ": ", IsGamepadButtonPressed(i, GAMEPAD_BUTTON_LEFT_FACE_DOWN));
    //   }
    if (Button_Down()) {
        _LUA_Key_Down();
    }
    if (Button_Up()) {
        _LUA_Key_Up();
    }
    if (Button_Left()) {
        _LUA_Key_Left();
    }
    if (Button_Right()) {
        _LUA_Key_Right();
    }
    if (Button_A()) {
        _LUA_Key_Activate();
    }
    if (Button_X()) {
        _LUA_Key_Back();
    }
    _LUA_Update();
}

void LibEric::Menu::Render() {
    Rectangle src;
    Rectangle dest;
    src.x = dest.x = 0;
    src.y = dest.y = 0;
    src.width = 1920;
    src.height = 1080;
    dest.width = Game::Instance()->GetWindowWidth();
    dest.height = Game::Instance()->GetWindowHeight();
    RenderManager::Instance()->DrawEx("BGI", src, dest, 0.0f);
    _LUA_Draw();
#ifdef __linux__
    if (LibEric::LibEricSettings::Instance()->GetShowVersion())
        DrawText(std::string(std::string("Version: ") + std::string(LIBERIC_VERSION)).c_str(), 20,
                 Game::Instance()->GetWindowHeight() - 20, 20, RED);
#endif
}

std::string LibEric::Menu::GetStateID() const {
    return _ID;
}


void LibEric::Menu::SetID(std::string id) {
    // PLOGE << "Setzte ID zu " << id;
    _ID = id;
}

void LibEric::Menu::Resize() {
    _Lua_Resize();
}


void CreateExitDialog() {
    LibEric::Dialog::Instance()->NewSelectDialog("\n\t\tWirklich Beenden", "Ja", "Nein", 1);
}

bool ExitGameDialog() {
    if (LibEric::Dialog::Instance()->GetAnswer() == 0)
        return true;
    else
        return false;
}

bool LibEric::Menu::OnEnter(std::string file) {
#ifdef __linux__
    std::string scriptpath = PHYSFS_getRealDir("/system");
    std::string scriptFile = scriptpath + std::string("/Menu/") + file;
#else
    std::string scriptFile = std::string("data\\Menu\\") + file;
#endif

    LOGE("SCRIPT: ", scriptFile);
    GuiSetFont(Game::Instance()->GetDefaultFont());

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
    lua.set_function("CreateExitDialog", &CreateExitDialog);
    lua.set_function("ExitGame", &ExitGameDialog);

    lua.script_file(scriptFile.c_str());

    _ID = lua["MENUID"];

    _LUA_Update = lua["Update"];
    _LUA_Draw = lua["Draw"];
    _LUA_Key_Up = lua["Key_Up"];
    _LUA_Key_Down = lua["Key_Down"];
    _LUA_Key_Left = lua["Key_Left"];
    _LUA_Key_Right = lua["Key_Right"];
    _LUA_Key_Activate = lua["Activate"];
    _LUA_Key_Back = lua["Back"];
    _Lua_Resize = lua["Resize"];

    return true;
}

bool LibEric::Menu::OnExit() {
    return true;
}


