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
#include <libEric/Input.hpp>
#include <libEric/Dialog.hpp>
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION

#include <raygui.h>
#include <raylib-physfs.h>
#include <physfs.h>
#include <sstream>


LibEric::Button::Button(std::string text, float x, float y, float width, float height) {
    pActiv = false;
    pText = text;
    pRect.x = x;
    pRect.y = y;
    pRect.width = width;
    pRect.height = height;
}

void LibEric::Button::Resize(float x, float y, float width, float height) {
    pRect.x = x;
    pRect.y = y;
    pRect.width = width;
    pRect.height = height;
}


void LibEric::Button::Draw() {
    if (pActiv) {
        GuiSetState(STATE_FOCUSED);
    } else {
        GuiSetState(STATE_NORMAL);
    }

    GuiButton(pRect, pText.c_str());
    GuiSetState(STATE_NORMAL);
}

void LibEric::Button::SetActiv(bool activ) {
    pActiv = activ;
}

LibEric::CheckBox::CheckBox(std::string text, float x, float y, float width, float height, bool checked) {
    pActiv = false;
    pRect.x = x;
    pRect.y = y;
    pRect.width = width;
    pRect.height = height;
    pCheck = checked;
    pText = text;
}

void LibEric::CheckBox::Resize(float x, float y, float width, float height) {
    pRect.x = x;
    pRect.y = y;
    pRect.width = width;
    pRect.height = height;
}

bool LibEric::CheckBox::IsActivated() {
    return pCheck;
}

void LibEric::CheckBox::Toggle(bool n) {
    pCheck = n;
}

void LibEric::CheckBox::Draw() {
    if (pActiv) {
        GuiSetState(STATE_FOCUSED);
    } else {
        GuiSetState(STATE_NORMAL);
    }

    GuiCheckBox(pRect, pText.c_str(), pCheck);
    GuiSetState(STATE_NORMAL);

}

void LibEric::CheckBox::SetActiv(bool activ) {
    pActiv = activ;
}

LibEric::Slider::Slider(std::string text, float x, float y, float width, float height, float currentVal, float minVal,
                        float maxVal) {
    pActiv = false;
    pCurrentValue = currentVal;
    pMinValue = minVal;
    pMaxValue = maxVal;
    pRect.x = x;
    pRect.y = y;
    pRect.width = width;
    pRect.height = height;
    pText = text;
}

void LibEric::Slider::Resize(float x, float y, float width, float height) {
    pRect.x = x;
    pRect.y = y;
    pRect.width = width;
    pRect.height = height;
}


float LibEric::Slider::GetValue() {
    return pCurrentValue;
}

void LibEric::Slider::SetValue(float val) {
    if (val <= 0)
        val = 0.0;
    if (val > 1)
        val = 1.0;
    pCurrentValue = val;
}


void LibEric::Slider::Draw() {
    if (pActiv) {
        GuiSetState(STATE_FOCUSED);
    } else {
        GuiSetState(STATE_NORMAL);
    }

    std::stringstream ss;
    int i = 100 * pCurrentValue;
    if (pCurrentValue == 0.0)
        ss << "0";
    else
        ss << i;

    GuiSliderBar(pRect, pText.c_str(), ss.str().c_str(), pCurrentValue, pMinValue, pMaxValue);
    GuiSetState(STATE_NORMAL);
}


void LibEric::Slider::SetActiv(bool activ) {
    pActiv = activ;
}


void LibEric::Menu::Update() {
    if (Button_Down()) {
        pLUA_Key_Down();
    }
    if (Button_Up()) {
        pLUA_Key_Up();
    }
    if (Button_Left()) {
        pLUA_Key_Left();
    }
    if (Button_Right()) {
        pLUA_Key_Right();
    }
    if (Button_A()) {
        pLUA_Key_Activate();
    }
    if (Button_X()) {
        pLUA_Key_Back();
    }
    pLUA_Update();
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
    pLUA_Draw();
#ifdef __linux__
    if (LibEric::LibEricSettings::Instance()->GetShowVersion())
        DrawText(std::string(std::string("Version: ") + std::string(LIBERIC_VERSION)).c_str(), 20,
                 Game::Instance()->GetWindowHeight() - 20, 20, RED);
#endif
}

std::string LibEric::Menu::GetStateID() const {
    return pID;
}


void LibEric::Menu::SetID(std::string id) {
    pID = id;
}

void LibEric::Menu::Resize() {
    pLua_Resize();
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

    pID = lua["MENUID"];

    pLUA_Update = lua["Update"];
    pLUA_Draw = lua["Draw"];
    pLUA_Key_Up = lua["Key_Up"];
    pLUA_Key_Down = lua["Key_Down"];
    pLUA_Key_Left = lua["Key_Left"];
    pLUA_Key_Right = lua["Key_Right"];
    pLUA_Key_Activate = lua["Activate"];
    pLUA_Key_Back = lua["Back"];
    pLua_Resize = lua["Resize"];

    return true;
}

bool LibEric::Menu::OnExit() {
    return true;
}


