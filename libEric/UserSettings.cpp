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


#include <libEric/UserSettings.hpp>
#include <libEric/Log.hpp>
#include <raylib.h>
#include <Extra/raylib-physfs.h>

#define SOL_ALL_SAFETIES_ON 1

#include <sol/sol.hpp>

LibEric::UserSettings *LibEric::UserSettings::_Instance = nullptr;

LibEric::UserSettings::UserSettings()
        : _MusicVolume(0.5), _EffectVolume(0.5), _Fullscreen(false), _CollisionBoxes(true),
          _WindowWidth(800), _WindowHeight(600), _FPS(60) {

}

LibEric::UserSettings *LibEric::UserSettings::Instance() {
    if (_Instance == nullptr)
        _Instance = new UserSettings();
    return _Instance;
}

bool LibEric::UserSettings::Load() {
    bool return_value = false;
    std::string script_file;

    sol::state lua;
    lua.open_libraries(sol::lib::base);
    lua.open_libraries(sol::lib::string);

    if (FileExistsInPhysFS("user/main.settings")) {
        return_value = true;
        script_file = LoadFileTextFromPhysFS("user/main.settings");
        LOGI ("Lade Settings aus Benutzerverzeichnis");
    } else if (FileExistsInPhysFS("system/main.settings")) {
        return_value = true;
        script_file = LoadFileTextFromPhysFS("system/main.settings");
        LOGI ("Lade Settings aus Systemverzeichnis");
    }

    if (return_value == true) {
        lua.script(script_file.c_str());
        _MusicVolume = lua.get<float>("MusicVolume");
        _EffectVolume = lua.get<float>("EffectVolume");
        _Fullscreen = lua.get<bool>("Fullscreen");
        _CollisionBoxes = lua.get<bool>("CollisionsBox");
        _WindowWidth = lua.get<int>("Screen_Width");
        _WindowHeight = lua.get<int>("Screen_Height");
        _FPS = lua.get<int>("FPS");
    }

    LOGD("\t_MusicVolume : ", _MusicVolume);
    LOGD("\t_EffectVolume: ", _EffectVolume);
    LOGD("\t_Fullscreen  : ", _Fullscreen);
    LOGD("\t_CollisionBox: ", _CollisionBoxes);
    LOGD("\t_WindowWidth : ", _WindowWidth);
    LOGD("\t_WindowHeight: ", _WindowHeight);
    LOGD("\t_FPS         : ", _FPS);
    return return_value;
}

float LibEric::UserSettings::GetMusicVolume() {
    return _MusicVolume;
}

float LibEric::UserSettings::GetEffectVolume() {
    return _EffectVolume;
}

bool LibEric::UserSettings::GetFullScreen() {
    return _Fullscreen;
}

bool LibEric::UserSettings::GetCollisionBoxes() {
    return _CollisionBoxes;
}

int LibEric::UserSettings::GetWindowWidth() {
    return _WindowWidth;
}

int LibEric::UserSettings::GetWindowHeight() {
    return _WindowHeight;
}

int LibEric::UserSettings::GetFPS() {
    return _FPS;
}

void LibEric::UserSettings::SetMusicVolume(float vol) {
    _MusicVolume = vol;
}

void LibEric::UserSettings::SetEffectVolume(float vol) {
    _EffectVolume = vol;
}

void LibEric::UserSettings::SetFPS(int fps) {
    _FPS = fps;
}

void LibEric::UserSettings::SetFullScreen(bool val) {
    LOGW("Fixme: Change Fullscreen");
}

void LibEric::UserSettings::SetWindowWidth(int width) {
    LOGW("Fixme: Change Window Width");
}

void LibEric::UserSettings::SetWindowHeight(int height) {
    LOGW("Fixme: Change Window Height");
}

void LibEric::UserSettings::SetCollisionBoxes(bool val) {
    _CollisionBoxes = val;
}