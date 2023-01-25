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


#include "Dialog.hpp"
#include <sstream>
#include "UserSettings.hpp"
#include "Log.hpp"
#include <Config.hpp>

LibEric::Dialog* LibEric::Dialog::_Instance = 0;

std::vector<std::string> split_string_by_newline(const std::string& str)
{
    auto result = std::vector<std::string>{};
    auto ss = std::stringstream{str};

    for (std::string line; std::getline(ss, line, '\n');){
        result.push_back(line);

    }

    return result;
}

void LibEric::Dialog::DrawDialog(){
    Rectangle rec;
    rec.x = UserSettings::Instance()->GetWindowWidth()/4;
    rec.y = (UserSettings::Instance()->GetWindowHeight()/3) * 2;
    rec.width = rec.x *2;
    rec.height = (rec.y / 3);
    DrawRectangleRounded(rec, 0.5, 4, Fade(LIGHTGRAY, 0.85f));

    int line = 0;
    for (unsigned long i = _LinePos; i < _MSG.size(); i++){
        if (line == 4)
            return;
        DrawTextEx(_Font, _MSG[i].c_str(), Vector2{rec.x + 15 , (rec.y +15) + (25*line) }, 25, 1, BLACK);
        line++;
    }
}

LibEric::Dialog * LibEric::Dialog::Instance(){
    if (_Instance == nullptr){
        _Instance = new Dialog();
    }
    return _Instance;
}


LibEric::Dialog::Dialog() :
    _MSGAvaible(false), _MSG(), _Font(), _LinePos(0){
    std::string erikDir = std::string (INSTALL_PREFIX) + std::string ("/share/EricTheViking");
    std::string fontFile = erikDir + std::string ("/Font.ttf");

    _Font = LoadFontEx(fontFile.c_str(), 25, NULL, 0);
}

void LibEric::Dialog::SetMSG(std::string msg){
    PLOGW << "setze MSG";
    _MSG = split_string_by_newline(msg);
    _LinePos = 0;
    _MSGAvaible = true;
}

void LibEric::Dialog::Update(){
    if (_MSG.size() > 4){
        if (_LinePos < _MSG.size() - 4){
            if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)||IsKeyPressed(KEY_DOWN)) {
                _LinePos++;
            }
        }
        else{
            if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)||IsKeyPressed(KEY_DOWN)) {
                _MSGAvaible = false;;
            }
        }
    }
    else{
        if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)||IsKeyPressed(KEY_DOWN)) {
            _MSGAvaible = false;;
        }
    }
}

bool LibEric::Dialog::Exist(){
    return _MSGAvaible;
}


