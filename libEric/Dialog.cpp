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


#include <libEric/Dialog.hpp>
#include <libEric/UserSettings.hpp>
#include <libEric/LibEricSettings.hpp>
#include <libEric/Log.hpp>
#include <Config.hpp>
#include <libEric/Game.hpp>
#include <libEric/Input.hpp>
#include <sstream>

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
    Rectangle TextBox;

    TextBox.width = UserSettings::Instance()->GetWindowWidth() * LibEricSettings::Instance()->GetDialogBoxWidth();
    TextBox.height = UserSettings::Instance()->GetWindowHeight() * LibEricSettings::Instance()->GetDialogBoxHeight();
    TextBox.x = (UserSettings::Instance()->GetWindowWidth() - TextBox.width) / 2;
    TextBox.y = UserSettings::Instance()->GetWindowHeight() - (5 + TextBox.height); //5 ist der Rand bis zum unteren Bildschirmrand

    DrawRectangleRounded(TextBox, 0.5, 4, Fade(LIGHTGRAY, 0.85f));

    int line = 0;
    for (unsigned long i = _LinePos; i < _MSG.size(); i++){
        if (line == 4)
            return;
        int TextSpaceToLeft = 20;
        int TextSpaceToTOP = 8;
        DrawTextEx(_Font, _MSG[i].c_str(), Vector2{TextBox.x + TextSpaceToLeft , (TextBox.y + TextSpaceToTOP) + (_FontSize*line) }, _FontSize, 1, BLACK);
        line++;
    }

    if (_OptinAvaible){
        Rectangle OptionBox1, OptionBox2;
        OptionBox1.width = UserSettings::Instance()->GetWindowWidth() * (LibEricSettings::Instance()->GetDialogBoxWidth()/3);
        OptionBox1.height = _FontSize + 10;//obenhalb und unterhalb der Schrift lassen wir 5 pixel platz
        OptionBox1.x = (UserSettings::Instance()->GetWindowWidth() - TextBox.width) / 2;
        OptionBox1.y = TextBox.y - OptionBox1.height + 5; // Um 5 Pixel überlappt es mit der textbox
        OptionBox2.width = UserSettings::Instance()->GetWindowWidth() * (LibEricSettings::Instance()->GetDialogBoxWidth()/3);
        OptionBox2.height = _FontSize + 10;//obenhalb und unterhalb der Schrift lassen wir 5 pixel platz
        OptionBox2.x = OptionBox1.x + (OptionBox1.width*2);
        OptionBox2.y =  TextBox.y - OptionBox1.height + 5; //5 Um 5 Pixel überlappt es mit der textbox

        if (_SelectedOption == 0) {
            DrawRectangleRounded(OptionBox1, 0.5, 4, Fade(SKYBLUE, 0.85f));
            DrawRectangleRounded(OptionBox2, 0.5, 4, Fade(LIGHTGRAY, 0.85f));
        }
        else{
            DrawRectangleRounded(OptionBox1, 0.5, 4, Fade(LIGHTGRAY, 0.85f));
            DrawRectangleRounded(OptionBox2, 0.5, 4, Fade(SKYBLUE, 0.85f));
        }
        DrawTextEx(_Font, _Option1.c_str(), Vector2{OptionBox1.x + 20 , (OptionBox1.y + 5) }, _FontSize, 1, BLACK);
        DrawTextEx(_Font, _Option2.c_str(), Vector2{OptionBox2.x + 20 , (OptionBox1.y + 5) }, _FontSize, 1, BLACK);
    }
}

LibEric::Dialog * LibEric::Dialog::Instance(){
    if (_Instance == nullptr){
        _Instance = new Dialog();
    }
    return _Instance;
}

//TODO Dialog
// - Textbox größe hier Festlegen (was passiert bei auflösungs wechsel)
// - Auswahldialog
LibEric::Dialog::Dialog() :
    _MSGAvaible(false), _MSG(), _Font(), _LinePos(0), _FontSize(25){
    std::string erikDir = std::string (INSTALL_PREFIX) + std::string ("/share/EricTheViking");
    std::string fontFile = erikDir + std::string ("/Font.ttf");

    _Font = LoadFontEx(fontFile.c_str(), _FontSize, NULL, 0);
}

void LibEric::Dialog::SetMSG(std::string msg){
    LOGV ("Erstelle DialogBox: ");
    LOGV ("\t", msg);
    _MSG = split_string_by_newline(msg);
    _LinePos = 0;
    _MSGAvaible = true;
}

void LibEric::Dialog::SetOption(std::string msg, std::string option1, std::string option2) {
    _Option1 = option1;
    _Option2 = option2;
    _MSG = split_string_by_newline(msg);
    _LinePos = 0;
    _SelectedOption = 0;
    _FinalOption = 0;
    _MSGAvaible = true;
    _OptinAvaible = true;
}

int LibEric::Dialog::GetOption() {
    int ret = _FinalOption;
    _FinalOption = 0;
    return ret;
}

void LibEric::Dialog::Update(){
    if (_OptinAvaible){
        if (_SelectedOption == 0){
            if (Button_Left() || Button_Right()){
                _SelectedOption = 1;
            }
            else if (Button_A()){
                _FinalOption = 1;
                _OptinAvaible = false;
                _MSGAvaible = false;
            }
        }
        else if (_SelectedOption == 1){
            if (Button_Left() || Button_Right()){
                _SelectedOption = 0;
            }
            else if (Button_A()){
                _FinalOption = 2;
                _OptinAvaible = false;
                _MSGAvaible = false;
            }
        }
        return;
    }

    if (_MSG.size() > 4){
        if (_LinePos < _MSG.size() - 4){
            if(Button_A()) {
                _LinePos++;
            }
        }
        else{
            if (Button_A()) {
                _MSGAvaible = false;;
            }
        }
    }
    else{
        if (Button_A()) {
            _MSGAvaible = false;;
        }
    }
}

bool LibEric::Dialog::Exist(){
    return _MSGAvaible;
}


