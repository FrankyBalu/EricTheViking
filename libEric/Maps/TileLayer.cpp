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



#include <libEric/Maps/TileLayer.hpp>
#include <libEric/Graphic/RenderManager.hpp>
#include <libEric/Core/LibEricApp.hpp>
#include <libEric/Core/UserSettings.hpp>
#include <libEric/Core/Log.hpp>
#include <raylib.h>


LibEric::TileLayer::TileLayer(int tileSize, int mapWidth, int mapHeight, const std::vector<Tileset> &tilesets)
        : pNumColumns(mapWidth), pNumRows(mapHeight), pTileSize(tileSize), pPosition{0, 0}, pVelocity{0, 0}, pName(),
          pTilesets(tilesets), pTileIDs() {

}

void LibEric::TileLayer::Update() {
    pPosition.x += pVelocity.x;
    pPosition.y += pVelocity.y;
}

void LibEric::TileLayer::Render() {
    float x;

    x = pPosition.x / pTileSize;

    for (int i = 0; i < pNumRows; i++) {
        for (int j = 0; j < pNumColumns; j++) {
            int id = pTileIDs[i][j + x];

            if (id == 0) {
                continue;
            }
            Tileset tileset = GetTilesetByID(id);
            id--;

            RenderManager::Instance()->DrawTile(tileset.name, j * pTileSize, i * pTileSize, pTileSize, pTileSize,
                                                (id - (tileset.firstGridID - 1)) / tileset.numColumns,
                                                (id - (tileset.firstGridID - 1)) % tileset.numColumns);
            if (pName == std::string("Collision") && UserSettings::Instance()->GetCollisionBoxes()) {
                DrawRectangleLines(j * pTileSize, i * pTileSize, pTileSize, pTileSize, RED);
            }
        }
    }
}

std::vector<Rectangle> LibEric::TileLayer::GetCollisionRects() {
    std::vector<Rectangle> _rects;
    Rectangle tileRect;
    for (int i = 0; i < pNumRows; i++) {
        for (int j = 0; j < pNumColumns; j++) {
            int id = pTileIDs[i][j];
            if (id == 0) {
                continue;
            }
            tileRect.x = j * pTileSize;
            tileRect.y = i * pTileSize;
            tileRect.height = pTileSize;
            tileRect.width = pTileSize;

            _rects.push_back(tileRect);
        }
    }
    return _rects;
}


LibEric::Tileset LibEric::TileLayer::GetTilesetByID(int tileID) {
    for (unsigned long i = 0; i < pTilesets.size(); i++) {
        if (i + 1 <= pTilesets.size() - 1) {
            if (tileID >= pTilesets[i].firstGridID && tileID < pTilesets[i + 1].firstGridID) {
                return pTilesets[i];
            }
        } else {
            return pTilesets[i];
        }
    }
    LOGE ("Konnte kein Tileset finden: ", tileID);
    Tileset t;
    return t;
}
