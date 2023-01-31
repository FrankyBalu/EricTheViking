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


#ifndef __LEVEL
#define __LEVEL

#include <string>
#include <vector>
#include "GameObject_Interface.hpp"
#include "Layer.hpp"

class TileLayer;

namespace LibEric {

    struct Tileset {
        int firstGridID;
        int tileWidth;
        int tileHeight;
        int spacing;
        int margin;
        int width;
        int height;
        int numColumns;
        std::string name;
    };

    class Map {
    public:
        ~Map() {}

        void Update();

        void Render();

        std::vector<Tileset> *GetTilesets();

        std::vector<Layer *> *GetLayers();

        Layer *GetObjectLayer();

        int GetWidth() {
            return _Width;
        }

        int GetHeight() {
            return _Height;
        }

        bool Collison(GameObject_Interface *object);

    private:
        friend class MapParser;

        Map() : _Tileset(), _Layers() {}

        int _Width;
        int _Height;

        std::vector<Tileset> _Tileset;
        std::vector<Layer *> _Layers;
        Layer *_BackgroundLayer;
        Layer *_RoadLayer;
        Layer *_WaterLayer;
        Layer *_CollisionLayer;
        Layer *_SkyLayer;
        Layer *_ObjectLayer;
    };

}; //namespace LibEric
#endif //__LEVEL
