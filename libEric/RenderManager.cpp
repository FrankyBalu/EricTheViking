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

#include <libEric/RenderManager.hpp>
#include <libEric/Log.hpp>
#include <libEric/Game.hpp>
#include <Extra/raylib-physfs.h>

LibEric::RenderManager *LibEric::RenderManager::_Instance = nullptr;

LibEric::RenderManager *LibEric::RenderManager::Instance() {
    if (_Instance == nullptr)
        _Instance = new RenderManager();
    return _Instance;
}

LibEric::RenderManager::RenderManager() {

}

LibEric::RenderManager::~RenderManager() {
    //FIXME Der obereteil wird laut ausgabe auf der Konsole mehrfach ausgeführt, aber keine ahnung warum
    LOGD ("Lösche die Instanz vom RenderManager!");
    RenderManager *tmp = _Instance;
    _Instance = nullptr;
    delete tmp;
    LOGD ("Lösche alle Texturen aus dem RenderManager:");
    for (auto it = _TextureMap.cbegin(); it != _TextureMap.cend(); ++it) {
        LOGD ("\t\t", (*it).first);
        UnloadTexture((*it).second);
        _TextureMap.erase((*it).first);
    }
}

void LibEric::RenderManager::ClearRenderManager() {
    this->~RenderManager();
}

bool LibEric::RenderManager::LoadTextureFromFile(std::string id, std::string fileName) {
    if (!Game::Instance()->IsReady()) {
        LOGE("Kein Rendercontext vorhanden");
        return false;
    }
    if (_TextureMap.count(id) == 0) {
        LOGD("Lade Texture ", id, " aus Datei: ", fileName);
        if (!FileExistsInPhysFS(std::string("system/" + fileName).c_str())) {
            LOGI ("Datei existiert nicht");
            return false;
        }
        Texture2D tmpTexture = LoadTextureFromPhysFS(std::string("system/" + fileName).c_str());

        if (tmpTexture.id <= 0) {
            LOGE ("\t\tKonnte Texture nicht laden");
            return false;
        }

        _TextureMap[id] = tmpTexture;
        return true;
    } else {
        LOGW ("Texture mit ID <", id, "> existiert bereits!");
        return false;
    }
}

bool LibEric::RenderManager::DrawTextureSimple(std::string id, int x, int y) {
    if (!Game::Instance()->IsReady()) {
        LOGE("Kein Rendercontext vorhanden");
        return false;
    }
    if (_TextureMap.count(id) != 0) {
        DrawTexture(_TextureMap[id], x, y, WHITE);
        return true;
    } else {
        LOGE("Texture mit ID <", id, "> nicht vorhanden!");
        return false;
    }
}

//FIXME größe überprüfen, ist der Frame innerhalb der Texture
bool LibEric::RenderManager::DrawFrame(std::string id, float x, float y, float width, float height, int frame,
                                       int row) {
    if (!Game::Instance()->IsReady()) {
        LOGE("Kein Rendercontext vorhanden");
        return false;
    }
    if (_TextureMap.count(id) != 0) {
        Rectangle frameRect = {0.0f, 0.0f, width, height};
        Rectangle destRect = {x, y, width, height};
        frameRect.x = width * frame;
        frameRect.y = height * row;
        DrawEx(id, frameRect, destRect, 0.0f);
        return true;
    } else {
        LOGE("Texture mit ID <", id, "> nicht vorhanden!");
        return false;
    }
}

bool LibEric::RenderManager::DrawEx(std::string id, Rectangle src, Rectangle dest, float rotate) {
    if (!Game::Instance()->IsReady()) {
        LOGE("Kein Rendercontext vorhanden");
        return false;
    }
    if (_TextureMap.count(id) != 0) {
        DrawTexturePro(_TextureMap[id], src, dest, Vector2{0.0f, 0.0f}, rotate, WHITE);
        return true;
    } else {
        LOGE("Texture mit ID <", id, "> existiert nicht");
        return false;
    }

}

bool LibEric::RenderManager::DrawTile(std::string id, float x, float y, float width, float height, int currentRow,
                                      int currentFrame) {
    if (!Game::Instance()->IsReady()) {
        LOGE("Kein Rendercontext vorhanden");
        return false;
    }
    if (_TextureMap.count(id) != 0) {
        Rectangle frame = {width * currentFrame, height * currentRow, width, height};
        DrawTextureRec(_TextureMap[id], frame, Vector2{x, y}, WHITE);
        return true;
    } else {
        LOGE ("Texture mit ID <", id, "> existiert nicht");
        return false;
    }
}

bool LibEric::RenderManager::FreeTexture(std::string id) {
    if (_TextureMap.count(id) != 0) {
        LOGD("Lösche Texture <", id, ">");
        UnloadTexture(_TextureMap[id]);
        _TextureMap.erase(id);
        return true;
    } else {
        LOGE("Konnte Texture mit ID <", id, "> nicht löschen, da nicht gefunden");
        return false;
    }
}

Rectangle LibEric::RenderManager::TextureRect(std::string id) {
    if (_TextureMap.count(id) == 0){
        return {0.0f, 0.0f, 0.0f, 0.0f};
    }

    Rectangle rect;
    rect.x = rect.y = 0;
    rect.width = _TextureMap[id].width;
    rect.height = _TextureMap[id].height;
    return rect;
}