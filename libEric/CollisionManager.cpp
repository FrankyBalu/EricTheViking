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

#include "CollisionManager.hpp"
#include <libEric/MapManager.hpp>
#include <libEric/Log.hpp>

void LibEric::CollisionManager::AddObject(GameObject_Interface *object) {
    ObjectType *obj = new ObjectType ;
    obj->obj = object;
    obj->rects = object->GetRects();
    if (object->Moveable()){
        _MoveableObjects.push_back(obj);
    }
    else{
        _StaticObjects.push_back(obj);
    }
}

void LibEric::CollisionManager::Update() {
    // Check Map Collision
    for (long int i = 0; i < _MoveableObjects.size(); i++){
        std::vector<CollisionRectangle> objRects = _MoveableObjects[i]->obj->GetRects();
        for (long int j = 0; j < objRects.size(); j++){
            if (objRects[j].type == std::string ("WORLDCOLISION")){
                Rectangle rectangle;
                rectangle.x = objRects[j].x;
                rectangle.y = objRects[j].y;
                rectangle.width = objRects[j].width;
                rectangle.height = objRects[j].height;
                LOGW("PlayerRect: ", rectangle.x, "  ", rectangle.y, "   ", rectangle.width, "   ", rectangle.height);

                std::vector<Rectangle> mapRects = MapManager::Instance()->GetCollisionRects();
                for (long int e = 0; e < mapRects.size(); e++){
                    if (CheckCollisionRecs(mapRects[e], rectangle)){
                        _MoveableObjects[i]->obj->Collision("MapCollision", nullptr);
                    }
                }
            }
        }
    }
}