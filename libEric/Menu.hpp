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
#define MENU

#include <libEric/GameState.hpp>
#include <libEric/GameStateFactory.hpp>
#include <raylib.h>

#define SOL_ALL_SAFETIES_ON 1

#include <Extra/sol/sol.hpp>

namespace LibEric {


    class Button {
    public:
        Button(std::string text, float x, float y, float width, float height);

        void Resize(float x, float y, float width, float height);

        void Draw();

        void SetActiv(bool activ);

    private:
        bool pActiv;
        Rectangle pRect;
        std::string pText;
    };


    class Slider {
    public:
        Slider(std::string text, float x, float y, float width, float height, float currentVal, float minVal,
               float maxVal);

        void Resize(float x, float y, float width, float height);

        void Draw();

        float GetValue();

        void SetValue(float val);

        void SetActiv(bool activ);

    private:
        bool pActiv;
        float pCurrentValue;
        float pMinValue;
        float pMaxValue;
        Rectangle pRect;
        std::string pText;
    };

    class CheckBox {
    public:
        CheckBox(std::string text, float x, float y, float width, float height, bool checked);

        void Resize(float x, float y, float width, float height);

        void Draw();

        bool IsActivated();

        void Toggle(bool n);

        void SetActiv(bool activ);

    private:
        bool pActiv;
        bool pCheck;
        Rectangle pRect;
        std::string pText;
    };

    class Menu : public LibEric::GameState {
    public:

        void HandleEvents() override {};

        void Update() override;

        void Render() override;

        void Resize() override;

        bool OnEnter(std::string file) override;

        bool OnExit() override;


        std::string GetStateID() const override;

    private:

        void SetID(std::string id);

        std::string pID;
        std::string pLUA_File;

        sol::state lua;

        sol::function pLUA_Update;
        sol::function pLUA_Draw;
        sol::function pLUA_Key_Up;
        sol::function pLUA_Key_Down;
        sol::function pLUA_Key_Left;
        sol::function pLUA_Key_Right;
        sol::function pLUA_Key_Activate;
        sol::function pLUA_Key_Back;
        sol::function pLua_Resize;

    };

    class MenuCreator : public LibEric::StateBaseCreator {
    public:
        LibEric::GameState *CreateState() const override {
            return new Menu();
        }
    };

}; //namespace LibEric
#endif // __MENU
