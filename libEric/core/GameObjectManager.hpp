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

#ifndef ERIC_GAMEOBJECTMANAGER_HPP
#define ERIC_GAMEOBJECTMANAGER_HPP

#include "libEric/libEric_API.hpp"
#include <libEric/Core/GameObject_Interface.hpp>
#include <map>

namespace LibEric {

    extern "C" {

    LIBERIC_API class GameObjectManager {
        GameObjectManager();

        ~GameObjectManager();

        int AddObject(GameObject_Interface *obj);

        //bool RemoveObject(int id);
        GameObject_Interface *GetObject(int id);

        int GetNumObjects();

    private:
        std::map<int, GameObject_Interface *> _Objects;

        int _Counter;
    };

}//extern "C"

} // LibEric

#endif //ERIC_GAMEOBJECTMANAGER_HPP
