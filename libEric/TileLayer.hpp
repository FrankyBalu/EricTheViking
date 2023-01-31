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


#ifndef __TILELAYER
#define __TILELAYER

#include <vector>
#include <string>
#include "GameObject_Interface.hpp"
#include "Layer.hpp"
#include "Map.hpp"
#include <raylib.h>

namespace LibEric {

    class TileLayer : public Layer {
    public:
        TileLayer(int tileSize, int mapWidth, int mapHeight, const std::vector<Tileset> &tilestes);

        virtual void Update() override;

        virtual void Render() override;

        void SetTileIDs(const std::vector<std::vector<int>> &data) {
            _TileIDs = data;
        }

        std::vector<std::vector<int>> GetTileIDs() {
            return _TileIDs;
        }

        void SetTileSize(int tileSize) {
            _TileSize = tileSize;
        }

        Tileset GetTilesetByID(int tileID);


        std::string GetName() {
            return _Name;
        }

        void SetName(std::string name) {
            _Name = name;
        }

        bool CheckCollision(GameObject_Interface *object);

        int GetWidth() {
            return _NumColumns * _TileSize;
        }

        int GetHeight() {
            return _NumRows * _TileSize;
        }

    private:
        int _NumColumns;
        int _NumRows;
        int _TileSize;

        Vector2 _Position;
        Vector2 _Velocity;

        std::string _Name;

        const std::vector<Tileset> _Tilesets;
        std::vector<std::vector<int>> _TileIDs;
    };

}; //namespace LibEric
#endif //__TILELAYER
