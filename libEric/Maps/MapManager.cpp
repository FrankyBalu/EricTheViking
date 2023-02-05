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

#include <string>
#include <raylib.h>
#include <libEric/Core/Log.hpp>
#include <libEric/Maps/MapManager.hpp>
#include <libEric/Maps/MapParser.hpp>

LibEric::MapManager *LibEric::MapManager::_Instance = 0;

bool LibEric::MapManager::LoadMap(std::string fileName, std::string id) {
    //Prüfen ob es schon eine Karte mit der id gibt
    if (Exist(id)) {
        LOGW  ("Karte mit ID ", id, " existiert bereits");
        return false;
    }

    //Karte aus Datei laden
    MapParser parser;
    Map *newMap = parser.ParseMap(fileName);

    //Prüfen ob Karte geladen wurde
    if (newMap == nullptr) {
        LOGE ("Karte ", id, " konnte nicht geladen werden");
        return false;
    }

    //Karte zum Stapel hinzufügen
    _Maps[id] = newMap;
    LOGI ("Karte erfolgreich geladen: ", id);
    return true;
}

void LibEric::MapManager::Draw() {
    _CurrentMap->Render();
}

bool LibEric::MapManager::ChangeCurrentMap(std::string id) {
    if (Exist(id)) {
        _CurrentMap = _Maps[id];
        return true;
    }
    LOGW ("Konnte nicht zur Karte: ", id, " wchseln: nicht vorhanden");
    return false;
}

bool LibEric::MapManager::RemoveMap(std::string id) {
    return false;
}

void LibEric::MapManager::Update() {
    _CurrentMap->Update();
}

LibEric::MapManager *LibEric::MapManager::Instance() {
    if (_Instance == nullptr) {
        _Instance = new MapManager();
    }
    return _Instance;
}

std::vector<Rectangle> LibEric::MapManager::GetCollisionRects() {
    return _CurrentMap->GetCollisonRects();
}

int LibEric::MapManager::GetWidth() {
    return _CurrentMap->GetWidth();
}

int LibEric::MapManager::GetHeight() {
    return _CurrentMap->GetHeight();
}


LibEric::MapManager::MapManager() {

}

LibEric::MapManager::~MapManager() {
}

bool LibEric::MapManager::Exist(std::string id) {
    if (_Maps.count(id) == 0)
        return false;
    else
        return true;
}

LibEric::Layer *LibEric::MapManager::GetObjectLayer() {
    return _CurrentMap->GetObjectLayer();
}


