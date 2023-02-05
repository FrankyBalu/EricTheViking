/*
 * Eric The Viking
 * Copyright (C) 2022  Frank Kartheuser <frank.kartheuser1988@gmail.com>
 * Copyright (C) 2022  Frank Kartheuser <frank.kartheuser1988@gmail.com>
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


#include <libEric/Sprite.hpp>
#include <libEric/RenderManager.hpp>
#include <libEric/Log.hpp>
#include <utility>

LibEric::Sprite::Sprite(const std::string& textureID): pDrawPosition({0.0f, 0.0f}),pDrawSize({0.0f, 0.0f}),
                                                pTexturePosition({0.0f, 0.0f}),pTextureSize({LibEric::RenderManager::Instance()->TextureRect(textureID).width, LibEric::RenderManager::Instance()->TextureRect(textureID).height})
                                                {
    pID = textureID;

}

LibEric::Sprite::Sprite(const std::string& textureID, Vector2 position, Vector2 size): pDrawPosition(position), pDrawSize(size),
                                                                                pTexturePosition({0.0f, 0.0f}),pTextureSize({LibEric::RenderManager::Instance()->TextureRect(textureID).width, LibEric::RenderManager::Instance()->TextureRect(textureID).height})
                                                                                {
    pID = textureID;
}

void LibEric::Sprite::Draw() {
    RenderManager::Instance()->DrawEx(pID, {pTexturePosition.x, pTexturePosition.y, pTextureSize.x, pTextureSize.y},
                                      {pDrawPosition.x, pDrawPosition.y, pDrawSize.x, pDrawSize.y});
}

void LibEric::Sprite::Update() {

}

void LibEric::Sprite::Clean() {
    LOGW("Sprite::Clean Funktion muss noch erstellt werden!");
}

void LibEric::Sprite::Load(const std::string scriptFile){

}

std::string LibEric::Sprite::GetID() {
    return pID;
}

std::vector<LibEric::CollisionRectangle> LibEric::Sprite::GetRects() {
    return pCollisionRects;
}

void LibEric::Sprite::Collision(std::string IDofCollisionObject, void *data) {

}

void LibEric::Sprite::SetDrawSize(Vector2 size) {
    pDrawSize = size;
}

void LibEric::Sprite::SetDrawPosition(Vector2 pos) {
    pDrawPosition = pos;
}

void LibEric::Sprite::SetTextureSize(Vector2 size) {
    pTextureSize = size;
}

void LibEric::Sprite::SetTexturePosition(Vector2 pos) {
    pTexturePosition = pos;
}

Vector2 LibEric::Sprite::GetDrawSize() {
    return pDrawSize;
}

Vector2  LibEric::Sprite::GetDrawPosition() {
    return pDrawPosition;
}

Vector2 LibEric::Sprite::GetTextureSize() {
    return pTextureSize;
}

Vector2  LibEric::Sprite::GetTexturePosition() {
    return pTexturePosition;
}

void LibEric::Sprite::SetTextureID(std::string id) {
    pID = std::move(id);
}

bool LibEric::Sprite::Moveable() {
    return pMoveable;
}