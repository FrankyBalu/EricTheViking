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


#include <libEric/Core/UserSettings.hpp>
#include <libEric/Core/Log.hpp>

#include <fstream>

#include <raylib.h>
#include <raylib-physfs.h>
#include <physfs.h>
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

LibEric::UserSettings *LibEric::UserSettings::pInstance = nullptr;

LibEric::UserSettings::UserSettings()
        : pMusicVolume(0.5), pEffectVolume(0.5), pFullscreen(false), pCollisionBoxes(true),
          pWindowWidth(800), pWindowHeight(600), pFPS(60) {

}

LibEric::UserSettings *LibEric::UserSettings::Instance() {
    if (pInstance == nullptr)
        pInstance = new UserSettings();
    return pInstance;
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

    if (return_value) {
        lua.script(script_file.c_str());
        pMusicVolume = lua.get<float>("MusicVolume");
        pEffectVolume = lua.get<float>("EffectVolume");
        pFullscreen = lua.get<bool>("Fullscreen");
        pCollisionBoxes = lua.get<bool>("CollisionsBox");
        pWindowWidth = lua.get<int>("Screen_Width");
        pWindowHeight = lua.get<int>("Screen_Height");
        pFPS = lua.get<int>("FPS");
    }

    LOGD("\t_MusicVolume : ", pMusicVolume);
    LOGD("\t_EffectVolume: ", pEffectVolume);
    LOGD("\t_Fullscreen  : ", pFullscreen);
    LOGD("\t_CollisionBox: ", pCollisionBoxes);
    LOGD("\t_WindowWidth : ", pWindowWidth);
    LOGD("\t_WindowHeight: ", pWindowHeight);
    LOGD("\t_FPS         : ", pFPS);
    return return_value;
}

float LibEric::UserSettings::GetMusicVolume() const {
    return pMusicVolume;
}

float LibEric::UserSettings::GetEffectVolume() const {
    return pEffectVolume;
}

bool LibEric::UserSettings::GetFullScreen() const {
    return pFullscreen;
}

bool LibEric::UserSettings::GetCollisionBoxes() const {
    return pCollisionBoxes;
}

int LibEric::UserSettings::GetWindowWidth() const {
    return pWindowWidth;
}

int LibEric::UserSettings::GetWindowHeight() const {
    return pWindowHeight;
}

int LibEric::UserSettings::GetFPS() const {
    return pFPS;
}

void LibEric::UserSettings::SetMusicVolume(float vol) {
    pMusicVolume = vol;
    Save();
}

void LibEric::UserSettings::SetEffectVolume(float vol) {
    pEffectVolume = vol;
    Save();
}

void LibEric::UserSettings::SetFPS(int fps) {
    pFPS = fps;
    Save();
}

void LibEric::UserSettings::SetFullScreen([[maybe_unused]] bool val) {
    LOGW("Fixme: Change Fullscreen");
    Save();
}

void LibEric::UserSettings::SetWindowWidth([[maybe_unused]]int width) {
    LOGW("Fixme: Change Window Width");
    Save();
}

void LibEric::UserSettings::SetWindowHeight([[maybe_unused]]int height) {
    LOGW("Fixme: Change Window Height");
    Save();
}

void LibEric::UserSettings::SetCollisionBoxes(bool val) {
    pCollisionBoxes = val;
    Save();
}

void LibEric::UserSettings::Save() const {
    std::string realpath;
#ifdef __linux__
        realpath = PHYSFS_getRealDir("system");
#elifdef _WIN64
        realpath = "data\\";
#endif
    std::string saveFile = realpath + PHYSFS_getDirSeparator() + "main.settings";

    std::ofstream file;
    file.open(saveFile);
    file << "MusicVolume = " << pMusicVolume << "\n";
    file << "EffectVolume = " << pEffectVolume << "\n";
    file << "Screen_Width = " << pWindowWidth  << "\n";
    file << "Screen_Height = " << pWindowHeight << "\n";
    file << "FPS = " << pFPS << "\n";
    if (pFullscreen){
        file << "Fullscreen = true\n";
    }
    else{
        file << "Fullscreen = false\n";
    }
    if (pCollisionBoxes){
        file << "CollisionsBox = true\n";
    }
    else{
        file << "CollisionsBox = false\n";
    }
}