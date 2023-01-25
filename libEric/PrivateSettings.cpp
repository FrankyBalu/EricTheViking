/*
 * LibEric
 * Copyright (C) 2022  Frank Kartheuser <frank.kartheuser1988@gmail.com>
 * Copyright (C) 2023  Frank Kartheuser <frank.kartheuser1988@gmail.com>
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

#include <fstream>
#include <filesystem>

#include <raylib.h>
#include "PrivateSettings.hpp"
#include "Log.hpp"
#include <Config.hpp>

#define SOL_ALL_SAFETIES_ON 1
#include "../../Extra/sol/sol.hpp"

LibEric::PrivateSettings* LibEric::PrivateSettings::_Instance = nullptr;

LibEric::PrivateSettings* LibEric::PrivateSettings::Instance() {
    if (_Instance == nullptr){
        _Instance = new PrivateSettings();
    }
    return _Instance;
}

LibEric::PrivateSettings::PrivateSettings()
    : _FirstState("MainMenu"),_ShowVersion(false),_PlayerAnimationSpeed(4),
      _BackgroundColorRed(0), _BackgroundColorGreen(82), _BackgroundColorBlue(172), _BackgroundColorAlpha(255),
      _LogLevel(8)
{
}

void LibEric::PrivateSettings::Load() {
    sol::state lua;
    lua.open_libraries(sol::lib::base);
    lua.open_libraries(sol::lib::string);

    std::string confFile = std::string (getenv("HOME")) + std::string ("/.Eric/PrivateSettings.lua");

    if (!FileExists(confFile.c_str())){
            Save();
    }

    lua.script_file (confFile.c_str());
    _FirstState = lua.get<std::string>("FirstState");
    _ShowVersion = lua.get<bool>("ShowVersion");
    _PlayerAnimationSpeed = lua.get<int>("PlayerAnimationSpeed");
    _BackgroundColorRed = lua.get<int>("BackgroundColorRed");
    _BackgroundColorGreen = lua.get<int>("BackgroundColorGreen");
    _BackgroundColorBlue = lua.get<int>("BackgroundColorBlue");
    _BackgroundColorAlpha = lua.get<int>("BackgroundColorAlpha");
    _LogLevel = lua.get<int>("LogLevel");
}

void LibEric::PrivateSettings::Save(){
    std::ofstream file;
    std::string confFile = std::string (getenv("HOME")) + std::string ("/.Eric/PrivateSettings.lua");
    std::string erikDir = std::string (getenv("HOME")) + std::string ("/.Eric");

    if (!FileExists(confFile.c_str())){
            if (!DirectoryExists(erikDir.c_str())){
                PLOGI << "Erstelle Verzeichnis: " << erikDir;
                std::filesystem::create_directory(erikDir);
            }
    }
    file.open (confFile);

    if (_ShowVersion){
        file << "ShowVersion = true\n";
    }
    else{
        file << "ShowVersion = false\n";
    }
    file << "FirstState = '" << _FirstState << "'\n";
    file << "PlayerAnimationSpeed = " << _PlayerAnimationSpeed << "\n";
    file << "BackgroundColorRed = " << _BackgroundColorRed << "\n";
    file << "BackgroundColorGreen = " << _BackgroundColorGreen << "\n";
    file << "BackgroundColorBlue = " << _BackgroundColorBlue << "\n";
    file << "BackgroundColorAlpha = " << _BackgroundColorAlpha << "\n";
    file << "LogLevel = " << _LogLevel << "\n";
    PLOGI << "Settings in " << confFile << " gespeichert!";
    file.close();
}


std::string LibEric::PrivateSettings::GetFirstState(){
    return _FirstState;
}

bool LibEric::PrivateSettings::GetShowVersion(){
    return _ShowVersion;
}

int LibEric::PrivateSettings::GetPlayerAnimationSpeed(){
    return _PlayerAnimationSpeed;
}

Color LibEric::PrivateSettings::GetBackgroundColor(){
    return Color {(unsigned char)_BackgroundColorRed, (unsigned char)_BackgroundColorGreen, (unsigned char)_BackgroundColorBlue, (unsigned char)_BackgroundColorAlpha};
}

int LibEric::PrivateSettings::GetLogLevel(){
    return _LogLevel;
}


