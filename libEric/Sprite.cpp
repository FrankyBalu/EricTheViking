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

#include <libEric/RenderManager.hpp>
#include "Sprite.hpp"
#include <libEric/Log.hpp>

LibEric::Sprite::Sprite(std::string textureID): _Position({0.0f,0.0f}),_TextureID(textureID),
                                                _DrawSize({0.0f,0.0f,0.0f,0.0f}),_SpriteID(textureID),_TextureSize(LibEric::RenderManager::Instance()->TextureRect(textureID)){


}

void LibEric::Sprite::SetPosition(Vector2 pos) {
    _DrawSize.x = pos.x;
    _DrawSize.y = pos.y;
    _Position = pos;
}

void LibEric::Sprite::SetSize(Vector2 size) {
    _DrawSize.width = size.x;
    _DrawSize.height = size.y;
}

Vector2 LibEric::Sprite::Position() {
    return _Position;
}

Vector2 LibEric::Sprite::Size() {
    return {_DrawSize.width, _DrawSize.height};
}

void LibEric::Sprite::Draw() {
    /*LOGI("_TextureID: ", _TextureID);
    LOGI("_TextureSize: x = ", _TextureSize.x);
    LOGI("_TextureSize: y = ", _TextureSize.y);
    LOGI("_TextureSize: w = ", _TextureSize.width);
    LOGI("_TextureSize: h = ", _TextureSize.height);
    LOGI("_DrawSize: x = ", _DrawSize.x);
    LOGI("_DrawSize: y = ", _DrawSize.y);
    LOGI("_DrawSize: w = ", _DrawSize.width);
    LOGI("_DrawSize: h = ", _DrawSize.height);*/
    RenderManager::Instance()->DrawEx(_TextureID, _TextureSize, _DrawSize);
}

void LibEric::Sprite::SetTextureID(std::string id) {
    _TextureID = id;
}