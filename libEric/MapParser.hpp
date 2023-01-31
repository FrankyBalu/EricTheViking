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

#ifndef __LEVELPARSER
#define __LEVELPARSER

#include <tinyxml2.h>
#include "Map.hpp"
#include <string>

namespace LibEric {

    class MapParser {
    public:
        Map *ParseMap(std::string levelFile);

    private:

        void ParseTilesets(tinyxml2::XMLElement *tilesetRoot, std::vector<Tileset> *tilesets, std::string path);

        void ParseTileLayer(tinyxml2::XMLElement *tileElement, Map *rmap);

        void ParseObjectLayer(tinyxml2::XMLElement *pObjectElement, Map *level);


        int _TileSize;
        int _Width;
        int _Height;
    };

}; //namespace LibEric
#endif // __LEVELPARSER
