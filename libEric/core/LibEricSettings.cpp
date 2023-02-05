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

#include <libEric/Core/LibEricSettings.hpp>
#include <libEric/Core/Log.hpp>
#include <raylib.h>
#include <Extra/raylib-physfs.h>

#define SOL_ALL_SAFETIES_ON 1

#include <sol.hpp>

LibEric::LibEricSettings *LibEric::LibEricSettings::_Instance = nullptr;

LibEric::LibEricSettings *LibEric::LibEricSettings::Instance() {
    if (_Instance == nullptr)
        _Instance = new LibEricSettings();
    return _Instance;
}

LibEric::LibEricSettings::LibEricSettings()
        : _FirstState("main.menu"), _DialogBoxWidth(0.8), _DialogBoxHeight(0.2),
          _ShowVersion(false), _EnableMSAA(true), _BackgroundColorRed(0), _BackgroundColorGreen(80),
          _BackgroundColorBlue(170), _BackgroundColorAlpha(255), _LogLevel(LOG_WARNING),
          _ExitKey(293), _Font("Font.ttf") {

}

bool LibEric::LibEricSettings::Load() {
    bool return_value = false;
    std::string script_file;

    sol::state lua;
    lua.open_libraries(sol::lib::base);
    lua.open_libraries(sol::lib::string);

    if (FileExistsInPhysFS("user/libEric.settings")) {
        return_value = true;
        script_file = LoadFileTextFromPhysFS("user/libEric.settings");
        LOGI ("Lade libEricSettings aus Benutzerverzeichnis");
    } else if (FileExistsInPhysFS("system/libEric.settings")) {
        return_value = true;
        script_file = LoadFileTextFromPhysFS("system/libEric.settings");
        LOGI ("Lade libEricSettings aus Systemverzeichnis");
    }

    if (return_value == true) {
        lua.script(script_file.c_str());
        _FirstState = lua.get<std::string>("FirstState");
        _ShowVersion = lua.get<bool>("ShowVersion");
        _BackgroundColorRed = lua.get<int>("BackgroundColorRed");
        _BackgroundColorGreen = lua.get<int>("BackgroundColorGreen");
        _BackgroundColorBlue = lua.get<int>("BackgroundColorBlue");
        _BackgroundColorAlpha = lua.get<int>("BackgroundColorAlpha");
        _DialogBoxWidth = lua.get<float>("DialogBoxWidth");
        _DialogBoxHeight = lua.get<float>("DialogBoxHeight");
        _LogLevel = lua.get<int>("LogLevel");
        _EnableMSAA = lua.get<bool>("MSAA");
        _ExitKey = lua.get<int>("ExitKey");
        _Font = lua.get<std::string>("Font");
    }

    LOGV("\t_FirstState          : ", _FirstState);
    LOGV("\t_ShowVersion         : ", _ShowVersion);
    LOGV("\t_BackgroundColorRed  : ", _BackgroundColorRed);
    LOGV("\t_BackgroundColorGreen: ", _BackgroundColorGreen);
    LOGV("\t_BackgroundColorBlue : ", _BackgroundColorBlue);
    LOGV("\t_BackgroundColorAlpha: ", _BackgroundColorAlpha);
    LOGV("\t_DialogBoxWidth      : ", _DialogBoxWidth);
    LOGV("\t_DialogBoxHeight     : ", _DialogBoxHeight);
    LOGV("\t_LogLevel            : ", _LogLevel);
    LOGV("\t_EnableMSAA          : ", _EnableMSAA);
    LOGV("\t_ExitKey             : ", _ExitKey);
    LOGV("\t_Font                : ", _Font);
    return return_value;
}

std::string LibEric::LibEricSettings::GetFirstState() {
    return _FirstState;
}

bool LibEric::LibEricSettings::GetShowVersion() {
    return _ShowVersion;
}

int LibEric::LibEricSettings::GetBGCRed() {
    return _BackgroundColorRed;
}

int LibEric::LibEricSettings::GetBGCGreen() {
    return _BackgroundColorGreen;
}

int LibEric::LibEricSettings::GetBGCBlue() {
    return _BackgroundColorBlue;
}

int LibEric::LibEricSettings::GetBGCAlpha() {
    return _BackgroundColorAlpha;
}

float LibEric::LibEricSettings::GetDialogBoxWidth() {
    return _DialogBoxWidth;
}

float LibEric::LibEricSettings::GetDialogBoxHeight() {
    return _DialogBoxHeight;
}

int LibEric::LibEricSettings::GetLogLevel() {
    return _LogLevel;
}

bool LibEric::LibEricSettings::GetMSAA() {
    return _EnableMSAA;
}

int LibEric::LibEricSettings::GetExitKey() {
    return _ExitKey;
}

std::string LibEric::LibEricSettings::GetFont() {
    return _Font;
}