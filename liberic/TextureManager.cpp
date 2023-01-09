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


#include "TextureManager.hpp"
#include "Log.hpp"
#include <raylib.h>
#include <string>
#include <Config.hpp>
#define SOL_ALL_SAFETIES_ON 1
#include "../../Extra/sol/sol.hpp"


LibEric::TextureManager* LibEric::TextureManager::_Instance = 0;

bool LibEric::TextureManager::Load(std::string fileName, std::string id) {
    if (_TextureMap.count(id) == 0)
    {
        PLOGI << "Lade Texture aus Datei: " << fileName;
        Texture tmpTex = LoadTexture(fileName.c_str());

        if (tmpTex.id <= 0) {
            PLOGE << "Könnte Texture nicht laden: " << fileName;
            return false;
        }

        _TextureMap[id] = tmpTex;
        PLOGI << "Erfolgreich mit ID: " << id << " " << "geladen";
        return true;
    }
    else
    {
        PLOGW << "Texture mit ID: " << id << "Existiert bereits";
        return false;
    }
}

void LibEric::TextureManager::Draw ( std::string id, int x, int y) {
    DrawTexture(_TextureMap[id], x, y, WHITE);
}

void LibEric::TextureManager::DrawFrame ( std::string id, float x, float y, float width, float height, int currentFrame, int currentRow) {
    if (!Exist(id))
        return;

    Rectangle frameRect = {0.0f, 0.0f, width, height};
    Rectangle destRect = {x, y, width, height};
    frameRect.x = width * currentFrame;
    frameRect.y = height * currentRow;
    DrawFrameEx(id, frameRect, destRect, 0.0f);
}


void LibEric::TextureManager::DrawFrameEx(std::string id, float srcX, float srcY, float srcWidth, float srcHeight, float destX, float destY, float destWidth, float destHeight, int currentFrame, int currentRow) {
    if (!Exist(id))
        return;

    Rectangle frameRect = {srcX, srcY, srcWidth, srcHeight};
    Rectangle destRect = {destX, destY, destWidth, destHeight};
    frameRect.x = srcWidth * currentFrame;
    frameRect.y = srcHeight * currentRow;
    //TODO: teste ob id existiert
    DrawFrameEx(id, frameRect, destRect, 0.0f);
}

void LibEric::TextureManager::DrawFrameEx (std::string id, Rectangle src, Rectangle dest, float rotation) {
    if (!Exist(id))
        return;

    DrawTexturePro(_TextureMap[id], src, dest, Vector2{0.0f,0.0f}, rotation, WHITE);
}

void LibEric::TextureManager::ClearFromTextureMap(std::string id) {
    _TextureMap.erase(id);
}
LibEric::TextureManager *LibEric::TextureManager::Instance() {
    if (_Instance == nullptr) {
        _Instance = new TextureManager;
    }
    return _Instance;
}

LibEric::TextureManager::TextureManager() {

}

LibEric::TextureManager::~TextureManager()
{
}

bool LibEric::TextureManager::Exist(std::string id) {
    if (_TextureMap.count(id) == 0)
        return false;
    else
        return true;
}

void LibEric::TextureManager::DrawTile(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame) {
    Rectangle frameRect = {0.0f, 0.0f, (float)width, (float)height};
    frameRect.x = width * currentFrame;
    frameRect.y = height * currentRow;
    //TODO: teste ob id existiert
    DrawTextureRec(_TextureMap[id], frameRect, Vector2{(float)x,(float)y}, WHITE);
}

bool LibEric::TextureManager::LoadFromLua(std::string fileName){
    sol::state lua;
    lua.open_libraries(sol::lib::base);
    lua.open_libraries(sol::lib::string);

    lua.set_function("Load", &TextureManager::Load);
    lua.script_file (std::string (getenv("HOME")) + std::string ("/.Erik/assets/") + fileName);
    return true;
}


