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


#ifndef LIBERIC_TILELAYER_HPP
#define LIBERIC_TILELAYER_HPP

#include <libEric/libEric_API.hpp>
#include <libEric/Core/GameObject_Interface.hpp>
#include <libEric/Maps/Layer.hpp>
#include <libEric/Maps/Map.hpp>

#include <utility>
#include <vector>
#include <string>
#include <raylib.h>

namespace LibEric {

    extern "C" {

    LIBERIC_API class TileLayer : public Layer {
    public:
        TileLayer(int tileSize, int mapWidth, int mapHeight, const std::vector<Tileset> &tilestes);

        void Update() override;

        void Render() override;

        void SetTileIDs(const std::vector<std::vector<int>> &data) {
            pTileIDs = data;
        }

        std::vector<std::vector<int>> GetTileIDs() {
            return pTileIDs;
        }

        void SetTileSize(int tileSize) {
            pTileSize = tileSize;
        }

        Tileset GetTilesetByID(int tileID);


        std::string GetName() {
            return pName;
        }

        void SetName(std::string name) {
            pName = std::move(name);
        }

        std::vector<Rectangle> GetCollisionRects();

        [[nodiscard]] int GetWidth() const {
            return pNumColumns * pTileSize;
        }

        [[nodiscard]] int GetHeight() const {
            return pNumRows * pTileSize;
        }

    private:
        int pNumColumns;
        int pNumRows;
        int pTileSize;

        Vector2 pPosition;
        Vector2 pVelocity;

        std::string pName;

        const std::vector<Tileset> pTilesets;
        std::vector<std::vector<int>> pTileIDs;
    };

    }//extern "C"

}; //namespace LibEric
#endif //__TILELAYER
