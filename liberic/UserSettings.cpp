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
#include "UserSettings.hpp"
#include "Log.hpp"
#include <Config.hpp>

#define SOL_ALL_SAFETIES_ON 1
#include "../../Extra/sol/sol.hpp"

LibEric::UserSettings* LibEric::UserSettings::_Instance = nullptr;

LibEric::UserSettings* LibEric::UserSettings::Instance() {
    if (_Instance == nullptr)
        _Instance = new UserSettings();
    return _Instance;
}

LibEric::UserSettings::UserSettings()
    : _Fullscreen(true), _CollisionBoxes(false), _WindowedWidth(800),
      _WindowedHeight(600), _FPS(60), _MusicVolume(0.5f), _EffectVolume(0.5f)
{
}

bool LibEric::UserSettings::Load() {
    sol::state lua;
    lua.open_libraries(sol::lib::base);
    lua.open_libraries(sol::lib::string);
//TODO System-weiter Speicherort bzw Windows Speicherort 
    std::string confFile = std::string (getenv("HOME")) + std::string ("/.Erik/UserSettings.lua");

    if (!FileExists(confFile.c_str())){
            Save();
    }

    lua.script_file (confFile);
    _Fullscreen = lua.get<bool>("FULLSCREEN");
    _CollisionBoxes = lua.get<bool>("COLLISIONBOXES");
    _WindowedWidth =  lua.get<int>("WINDOWWIDTH");
    _WindowedHeight =  lua.get<int>("WINDOWHEIGHT");
    _MusicVolume =  lua.get<float>("MUSICVOLUME");
    _EffectVolume =  lua.get<float>("EFECTVOLUME");

    return true;
}

void LibEric::UserSettings::Save(){
    std::ofstream file;
//TODO Windows Speicherort 
    std::string confFile = std::string (getenv("HOME")) + std::string ("/.Erik/UserSettings.lua");
    std::string erikDir = std::string (getenv("HOME")) + std::string ("/.Erik");

    if (!FileExists(confFile.c_str())){
            if (!DirectoryExists(erikDir.c_str())){
                PLOGI << "Erstelle Verzeichnis: " << erikDir;
                std::filesystem::create_directory(erikDir);
            }
    }
    file.open (confFile);
    file << "FULLSCREEN = ";
    if (_Fullscreen)
        file << "true\n";
    else
        file << "false\n";
    file << "COLLISIONBOXES = ";
    if (_CollisionBoxes)
        file << "true\n";
    else
        file << "false\n";
    file << "WINDOWWIDTH = " << _WindowedWidth << "\n";
    file << "WINDOWHEIGHT = " << _WindowedHeight << "\n";
    file << "MUSICVOLUME = " << _MusicVolume << "\n";
    file << "EFECTVOLUME = " << _EffectVolume << "\n";
    PLOGI << "UserSettings in " << confFile << " gespeichert!";
    file.close();
}


void LibEric::UserSettings::SetFullscreen(bool fullscreen) {
    _Fullscreen = fullscreen;
}

void LibEric::UserSettings::SetCollisionBoxes(bool boxes) {
    _CollisionBoxes = boxes;
}



void LibEric::UserSettings::SetWindowWidth(int width) {
    _WindowedWidth = width;
}

void LibEric::UserSettings::SetWindowHeight(int height) {
    _WindowedHeight = height;
}

void LibEric::UserSettings::SetFPS(int fps){
    _FPS = fps;
}

void LibEric::UserSettings::SetMusicVolume(float volume) {
    _MusicVolume = volume;
}

void LibEric::UserSettings::SetEffectVolume(float volume) {
    _EffectVolume = volume;
}

bool LibEric::UserSettings::GetFullScreen() {
    return _Fullscreen;
}

bool LibEric::UserSettings::GetCollisionBoxes() {
    return _CollisionBoxes;
}

int LibEric::UserSettings::GetWindowWidth() {
    return _WindowedWidth;
}

int LibEric::UserSettings::GetWindowHeight() {
    return _WindowedHeight;
}

int LibEric::UserSettings::GetFPS(){
    return _FPS;
}
float LibEric::UserSettings::GetMusicVolume() {
    return _MusicVolume;
}

float LibEric::UserSettings::GetEffectVolume() {
    return _EffectVolume;
}

int LibEric::UserSettings::GetFSHeight(){
    return GetMonitorHeight(GetCurrentMonitor());
}

int LibEric::UserSettings::GetFSWidth(){
    return GetMonitorWidth(GetCurrentMonitor());
}
