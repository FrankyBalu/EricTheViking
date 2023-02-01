/*
 * LibEric
 * Copyright (C) 2022  Frank Kartheuser <frank.kartheuser1988@gmail.com>
 * Copyright (C) 2023  Frank Kartheuser <frank.kartheuser1988@gmail.com>
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

#include <libEric/GraphicGameObject.hpp>
#include <libEric/RenderManager.hpp>
#include <libEric/Game.hpp>
#include <libEric/Log.hpp>
#include <libEric/UserSettings.hpp>


LibEric::GraphicGameObject::GraphicGameObject()
        : GameObject_Interface(), _Position{0, 0}, _CurrentFrame(0), _CurrentRow(0),
          _TextureID(), _TypeID(), _Visable(false) {
}


void LibEric::GraphicGameObject::Load(const std::string script) {
}


void LibEric::GraphicGameObject::Draw() {
    //Es Wird nur angezeigt, wenn die lebensenergie größer 0 ist
    if (!_Visable)
        return;
    LOGV ("Draw Texture : ", _TextureID);
    LOGV ("     Position: ", _Position.x, " x ", _Position.y);
    LOGV ("     Breite  : ", _Width);
    LOGV ("     Höhe    : ", _Height);
    LOGV ("     Spalte  : ", _CurrentFrame);
    LOGV ("     Zeile   : ", _CurrentRow);
    RenderManager::Instance()->DrawFrame(_TextureID, (int) _Position.x, (int) _Position.y, _Width, _Height,
                                         _CurrentFrame, _CurrentRow);
    if (LibEric::UserSettings::Instance()->GetCollisionBoxes()) {
        DrawRectangleLines((int) _Position.x, (int) _Position.y, _Width, _Height, BLUE);
    }
}

void LibEric::GraphicGameObject::Clean() {
}

void LibEric::GraphicGameObject::Update() {
    return;
}

Vector2 LibEric::GraphicGameObject::GetPosition() {
    return _Position;
}

int LibEric::GraphicGameObject::GetWidth() {
    return _Width;
}


int LibEric::GraphicGameObject::GetHeight() {
    return _Height;
}

void LibEric::GraphicGameObject::SetPosition(float x, float y) {
    _Position.x = x;
    _Position.y = y;
}

void LibEric::GraphicGameObject::SetHeight(float h) {
    _Height = h;
}

void LibEric::GraphicGameObject::SetWidth(float w) {
    _Width = w;
}


std::string LibEric::GraphicGameObject::GetID() {
    return std::string("UNKNOWN");
}

std::vector<LibEric::EricRect> LibEric::GraphicGameObject::GetRects() {
    EricRect rect;
    rect.x = _Position.x;
    rect.y = _Position.y;
    rect.height = _Height;
    rect.width = _Width;
    rect.type = "unknown";
    std::vector<EricRect> r;
    r.push_back(rect);
    return r;
}

//! Ist das Objekt beweglich
bool LibEric::GraphicGameObject::Moveable(){
    return false;
}

//! Dise Funktion wird vom ColisionManager aufgerufen, wenn zwei Objekte sich berühren
void LibEric::GraphicGameObject::ObjectCollision(std::string ownType, void *data){
    return;
}