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

#ifndef ERIC_COLLISIONMANAGER_HPP
#define ERIC_COLLISIONMANAGER_HPP

#include <raylib.h>
#include <vector>
#include <libEric/GameObject_Interface.hpp>
#include <libEric/Rectangle.hpp>

namespace LibEric {

    typedef struct {
        std::vector<CollisionRectangle> rects;
        GameObject_Interface* obj;
    }ObjectType;

    class CollisionManager {
    public:
        //nicht final, nur zum testen
        void AddObject(GameObject_Interface *object);
        void Update();
    private:
        std::vector<ObjectType*> _MoveableObjects;
        std::vector<ObjectType *> _StaticObjects;
    };

} // LibEric

#endif //ERIC_COLLISIONMANAGER_HPP
