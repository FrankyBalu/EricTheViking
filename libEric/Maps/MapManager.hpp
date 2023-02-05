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

#ifndef LIBERIC_MAPMANAGER_HPP
#define LIBERIC_MAPMANAGER_HPP

#include <string>
#include <libEric/Maps/Map.hpp>
#include <map>

namespace LibEric {

    class MapManager {
    public:

        static MapManager *Instance();

        //Läd eine neue Karte aus der datei fileName mid der ID id
        bool LoadMap(std::string fileName, std::string id);

        //Setzt eine Karte als Activ
        bool ChangeCurrentMap(std::string id);

        //Zeichnet die current-Karte
        //Die Spielfigur wird dabei nach der Kollisionsebene, vor der Himmels ebene gezeichnet
        void Draw();

        //Updatet alle Objecte einer MapManager
        void Update();

        //Prüft ob eine Map mit der id schon existiert
        bool Exist(std::string id);

        //Löscht eine Karte aus dem Speicher
        bool RemoveMap(std::string id);

        //Kartengröße
        int GetWidth();

        int GetHeight();


        Layer *GetObjectLayer();

        //FIXME muss noch in eigene Kollisionslogik
        std::vector<Rectangle> GetCollisionRects();

    private:

        std::map<std::string, Map *> _Maps;

        Map *_CurrentMap;

        static MapManager *_Instance;

        MapManager();

        ~MapManager();
    };

}; //namespace LibEric
#endif //LIBERIC_MAPMANAGER_HPP
