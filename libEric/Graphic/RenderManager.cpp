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

#include <libEric/Graphic/RenderManager.hpp>
#include <libEric/Core/Log.hpp>
#include <libEric/Core/LibEricApp.hpp>
#include <Extra/raylib-physfs.h>

LibEric::RenderManager *LibEric::RenderManager::pInstance = nullptr;

LibEric::RenderManager *LibEric::RenderManager::Instance() {
    if (pInstance == nullptr)
        pInstance = new RenderManager();
    return pInstance;
}

LibEric::RenderManager::RenderManager() = default;

LibEric::RenderManager::~RenderManager() {
    //FIXME Funktioniert scheinbar noch nicht richtig
    LOGD ("Lösche die Instanz vom RenderManager!");
    //RenderManager *tmp = pInstance;
    //pInstance = nullptr;
    //delete tmp;
    LOGD ("Lösche alle Texturen aus dem RenderManager:");
    for (auto it = pTextureMap.cbegin(); it != pTextureMap.cend(); ++it) {
        LOGD ("\t\t", (*it).first);
        UnloadTexture((*it).second);
        pTextureMap.erase((*it).first);
    }
    delete pInstance;
}

void LibEric::RenderManager::ClearRenderManager() {
    this->~RenderManager();
}

bool LibEric::RenderManager::LoadTextureFromFile(const std::string& id, const std::string& fileName) {
    if (!LibEricApp::Instance()->IsReady()) {
        LOGE("Kein Rendercontext vorhanden");
        return false;
    }
    if (pTextureMap.count(id) == 0) {
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

        pTextureMap[id] = tmpTexture;
        return true;
    } else {
        LOGW ("Texture mit ID <", id, "> existiert bereits!");
        return false;
    }
}

bool LibEric::RenderManager::DrawTextureSimple(const std::string& id, int x, int y) {
    if (!LibEricApp::Instance()->IsReady()) {
        LOGE("Kein Rendercontext vorhanden");
        return false;
    }
    if (pTextureMap.count(id) != 0) {
        DrawTexture(pTextureMap[id], x, y, WHITE);
        return true;
    } else {
        LOGE("Texture mit ID <", id, "> nicht vorhanden!");
        return false;
    }
}

//FIXME größe überprüfen, ist der Frame innerhalb der Texture
bool LibEric::RenderManager::DrawFrame(const std::string& id, float x, float y, float width, float height, int frame,
                                       int row) {
    if (!LibEricApp::Instance()->IsReady()) {
        LOGE("Kein Rendercontext vorhanden");
        return false;
    }
    if (pTextureMap.count(id) != 0) {
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

bool LibEric::RenderManager::DrawEx(const std::string& id, Rectangle src, Rectangle dest, float rotate) {
    if (!LibEricApp::Instance()->IsReady()) {
        LOGE("Kein Rendercontext vorhanden");
        return false;
    }
    if (pTextureMap.count(id) != 0) {
        DrawTexturePro(pTextureMap[id], src, dest, Vector2{0.0f, 0.0f}, rotate, WHITE);
        return true;
    } else {
        LOGE("Texture mit ID <", id, "> existiert nicht");
        return false;
    }

}

bool LibEric::RenderManager::DrawTile(const std::string& id, float x, float y, float width, float height, int currentRow,
                                      int currentFrame) {
    if (!LibEricApp::Instance()->IsReady()) {
        LOGE("Kein Rendercontext vorhanden");
        return false;
    }
    if (pTextureMap.count(id) != 0) {
        Rectangle frame = {width * currentFrame, height * currentRow, width, height};
        DrawTextureRec(pTextureMap[id], frame, Vector2{x, y}, WHITE);
        return true;
    } else {
        LOGE ("Texture mit ID <", id, "> existiert nicht");
        return false;
    }
}

bool LibEric::RenderManager::FreeTexture(const std::string& id) {
    if (pTextureMap.count(id) != 0) {
        LOGD("Lösche Texture <", id, ">");
        UnloadTexture(pTextureMap[id]);
        pTextureMap.erase(id);
        return true;
    } else {
        LOGE("Konnte Texture mit ID <", id, "> nicht löschen, da nicht gefunden");
        return false;
    }
}

Rectangle LibEric::RenderManager::TextureRect(const std::string& id) {
    if (pTextureMap.count(id) == 0){
        return {0.0f, 0.0f, 0.0f, 0.0f};
    }

    Rectangle rect;
    rect.x = rect.y = 0;
    rect.width = pTextureMap[id].width;
    rect.height = pTextureMap[id].height;
    return rect;
}