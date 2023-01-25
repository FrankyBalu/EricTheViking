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



#include "TileLayer.hpp"
#include "TextureManager.hpp"
#include "Game.hpp"
#include "UserSettings.hpp"
#include "Log.hpp"



LibEric::TileLayer::TileLayer(int tileSize, int mapWidth, int mapHeight, const std::vector<Tileset> &tilesets)
    :_NumColumns(mapWidth), _NumRows(mapHeight), _TileSize(tileSize), _Position{0,0}, _Velocity{0,0}, _Name(), _Tilesets(tilesets), _TileIDs()
{

}

void LibEric::TileLayer::Update()
{
    _Position.x += _Velocity.x;
    _Position.y += _Velocity.y;
}

void LibEric::TileLayer::Render()
{
    int x;

    x = _Position.x / _TileSize;


    for (int i = 0; i < _NumRows; i++)
    {
        for (int j = 0; j < _NumColumns; j++)
        {
            int  id = _TileIDs[i][j+x];

            if (id==0)
            {
                continue;
            }

            Tileset tileset = GetTilesetByID(id);

            id--;


            TextureManager::Instance()->DrawTile(tileset.name,  j*_TileSize, i * _TileSize, _TileSize, _TileSize, (id - (tileset.firstGridID - 1)) / tileset.numColumns, (id - (tileset.firstGridID -1)) % tileset.numColumns);
//             LibEric::TextureManager::Instance()->DrawFrame(tileset.name,  j*_TileSize, i * _TileSize, _TileSize, _TileSize, (id - (tileset.firstGridID - 1)) / tileset.numColumns, (id - (tileset.firstGridID -1)) % tileset.numColumns);
            if (_Name == std::string("Collision")&&UserSettings::Instance()->GetCollisionBoxes()) {
                DrawRectangleLines(j*_TileSize, i * _TileSize, _TileSize, _TileSize, RED);
            }
        }
    }
}

bool LibEric::TileLayer::CheckCollision(GameObject *object) {
    Rectangle tileRect;

    for (int i = 0; i < _NumRows; i++)
    {
        for (int j = 0; j < _NumColumns; j++)
        {
            int  id = _TileIDs[i][j];
            if (id==0)
            {
                continue;
            }
            tileRect.x = j * _TileSize;
            tileRect.y = i * _TileSize;
            tileRect.height = _TileSize;
            tileRect.width = _TileSize;

            if (CheckCollisionRecs(object->GetCollisionRect(), tileRect)) {
                return true;
            }
        }
    }
    return false;
}


LibEric::Tileset LibEric::TileLayer::GetTilesetByID(int tileID)
{
    for(unsigned long i = 0; i < _Tilesets.size(); i++)
    {
        if( i + 1 <= _Tilesets.size() - 1)
        {
            if(tileID >= _Tilesets[i].firstGridID && tileID < _Tilesets[i + 1].firstGridID)
            {
                return _Tilesets[i];
            }
        }
        else
        {
            return _Tilesets[i];
        }
    }

    PLOGW << "Konnte kein Tileset finden";
    Tileset t;
    return t;
}