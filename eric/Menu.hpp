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


#ifndef __MENU
#define __MENU

#include "../liberic/GameState.hpp"
#include "../liberic/GameStateFactory.hpp"
#include <raylib.h>
#define SOL_ALL_SAFETIES_ON 1
#include "../Extra/sol/sol.hpp"

namespace Eric {


class Button {
public:
    Button(std::string text, float x, float y, float width, float height);
    void Resize(float x, float y, float width, float height);

    void Draw();

    void SetActiv(bool activ);
private:
    bool _Activ;
    Rectangle _Rect;
    std::string _Text;
};


class Slider{
public:
    Slider(std::string text, float x, float y, float width, float height, float currentVal, float minVal, float maxVal);
    void Resize(float x, float y, float width, float height);

    void Draw();

    float GetValue();

    void SetValue(float val);

    void SetActiv (bool activ);
private:
    bool _Activ;
    float _CurrentValue;
    float _MinValue;
    float _MaxValue;
    Rectangle _Rect;
    std::string _Text;
};

class CheckBox {
public:
    CheckBox(std::string text, float x, float y, float width, float height, bool checked);
    void Resize(float x, float y, float width, float height);

    void Draw();

    bool IsActivated();

    void Toggle(bool n);

    void SetActiv (bool activ);
private:
    bool _Activ;
    bool _Check;
    Rectangle _Rect;
    std::string _Text;
};

class Menu : public LibEric::GameState
{
public:

    void HandleEvents() override{};
    void Update() override;
    void Render() override;

    bool OnEnter(std::string file) override;
    bool OnExit() override;


    virtual std::string GetStateID() const override;

private:

    void SetID(std::string id);

    Font _Font;
    std::string _ID;
    std::string _LUA_File;

    sol::state lua;

    sol::function _LUA_Update;
    sol::function _LUA_Draw;
    sol::function _LUA_Key_Up;
    sol::function _LUA_Key_Down;
    sol::function _LUA_Key_Left;
    sol::function _LUA_Key_Right;
    sol::function _LUA_Key_Activate;
    sol::function _LUA_Key_Back;

};

class MenuCreator : public LibEric::StateBaseCreator {
public:
    LibEric::GameState* CreateState() const {
        return new Menu();
    }
};

}; //namespace Eric
#endif // __MENU
