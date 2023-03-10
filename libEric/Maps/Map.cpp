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



#include <libEric/Maps/Map.hpp>
#include <libEric/Maps/TileLayer.hpp>
#include <libEric/Maps/Layer.hpp>

void LibEric::Map::Render() {
    _BackgroundLayer->Render();
    _RoadLayer->Render();
    _WaterLayer->Render();
    _CollisionLayer->Render();
    _ObjectLayer->Render();
    _SkyLayer->Render();
}

void LibEric::Map::Update() {
    _ObjectLayer->Update();
}

std::vector<LibEric::Tileset> *LibEric::Map::GetTilesets() {
    return &_Tileset;
}

std::vector<LibEric::Layer *> *LibEric::Map::GetLayers() {
    return &_Layers;
}


std::vector<Rectangle> LibEric::Map::GetCollisonRects() {
   // return dynamic_cast<TileLayer *>(_CollisionLayer)->CheckCollision(object);
   return dynamic_cast<TileLayer *>(_CollisionLayer)->GetCollisionRects();
}

LibEric::Layer *LibEric::Map::GetObjectLayer() {
    return _ObjectLayer;
}
