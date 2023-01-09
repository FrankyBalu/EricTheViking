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

#include "GraphicGameObject.hpp"
#include "TextureManager.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "UserSettings.hpp"

LibEric::GraphicGameObject::GraphicGameObject()
    :GameObject(), _Position{0,0},_Velocity{0,0}, _Acceleration{0,0} {
}



void LibEric::GraphicGameObject::Load(const std::string script){
}


void LibEric::GraphicGameObject::Draw()
{
    //Es Wird nur angezeigt, wenn die lebensenergie größer 0 ist
    if (!_Visable)
         return;
    PLOGV << "Draw Texture : " << _TextureID;
    PLOGV << "     Position: " << _Position.x << " x " << _Position.y;
    PLOGV << "     Breite  : " << _Width;
    PLOGV << "     Höhe    : " << _Height;
    PLOGV << "     Spalte  : " << _CurrentFrame;
    PLOGV << "     Zeile   : " << _CurrentRow;
    TextureManager::Instance()->DrawFrame(_TextureID, (int)_Position.x, (int)_Position.y, _Width, _Height, _CurrentFrame, _CurrentRow);
    if (UserSettings::Instance()->GetCollisionBoxes()) {
        DrawRectangleLines(_ObjectCollision.x, _ObjectCollision.y, _ObjectCollision.width, _ObjectCollision.height, RED );
        DrawRectangleLines(_NorthCollision.x, _NorthCollision.y, _NorthCollision.width, _NorthCollision.height, BLUE );
        DrawRectangleLines(_EastCollision.x, _EastCollision.y, _EastCollision.width, _EastCollision.height, BLUE );
        DrawRectangleLines(_SouthCollision.x, _SouthCollision.y, _SouthCollision.width, _SouthCollision.height, BLUE );
        DrawRectangleLines(_WestCollision.x, _WestCollision.y, _WestCollision.width, _WestCollision.height, BLUE );
    }
}

void LibEric::GraphicGameObject::Clean()
{
}

void LibEric::GraphicGameObject::Update()
{
    if (_Visable)
        return;
}

Vector2  LibEric::GraphicGameObject::GetPosition()
{
    return _Position;
}

int LibEric::GraphicGameObject::GetWidth()
{
    return _Width;
}


int LibEric::GraphicGameObject::GetHeight()
{
    return _Height;
}

void LibEric::GraphicGameObject::SetName(std::string name) {
    _Name = name;
}

std::string LibEric::GraphicGameObject::GetName() {
    return _Name;
}

void LibEric::GraphicGameObject::SetActivCollision(int activ) {
    if (activ >= 0 && activ <=4) {
        _ActivCollision = activ;
    }
}

int LibEric::GraphicGameObject::GetActivCollision() {
    return _ActivCollision;
}

void LibEric::GraphicGameObject::SetObject(Rectangle object) {
    _ObjectCollision = object;
}

Rectangle LibEric::GraphicGameObject::GetObject() {
    return _ObjectCollision;
}

void LibEric::GraphicGameObject::SetNorth(Rectangle north) {
    _NorthCollision = north;
}

Rectangle LibEric::GraphicGameObject::GetNorth() {
    return _NorthCollision;
}

void LibEric::GraphicGameObject::SetEast(Rectangle east) {
    _EastCollision = east;
}

Rectangle LibEric::GraphicGameObject::GetEast() {
    return _EastCollision;
}

void LibEric::GraphicGameObject::SetSouth(Rectangle south) {
    _SouthCollision = south;
}

Rectangle LibEric::GraphicGameObject::GetSouth() {
    return _SouthCollision;
}

void LibEric::GraphicGameObject::SetWest(Rectangle west) {
    _WestCollision = west;
}

Rectangle LibEric::GraphicGameObject::GetWest() {
    return _WestCollision;
}

bool LibEric::GraphicGameObject::CollisionDetect([[maybe_unused]] GraphicGameObject* obj) {
    return false;
}

void LibEric::GraphicGameObject::SetPosition(float x, float y){
    _Position.x = x;
    _Position.y = y;
}

void LibEric::GraphicGameObject::SetHeight(float h){
    _Height = h;
}

void LibEric::GraphicGameObject::SetWidth(float w){
    _Width = w;
}


