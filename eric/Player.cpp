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

#include "Player.hpp"
#include <libEric/Core/GameStateMaschine.hpp>
#include <libEric/Graphic/RenderManager.hpp>
#include <libEric/Core/LibEricSettings.hpp>
#include <raylib.h>
#include <libEric/Core/Log.hpp>
#include <libEric/Core/Input.hpp>
#include <libEric/Core/UserSettings.hpp>

Eric::Player *Eric::Player::pInstance = nullptr;

Eric::Player *Eric::Player::Instance() {
    if (pInstance == nullptr) {
        pInstance = new Player();
    }
    return pInstance;
}


Eric::Player::Player() :
    GraphicGameObject() {
    _Position.x = 10;
    _Position.y = 10;
    _Visable = true;
    _TypeID = "Player";
}

void Eric::Player::Load(std::string scriptFile) {
    GraphicGameObject::Load(scriptFile);
    _Position.x = 50;
    _Position.y = 50;
    _Width = 0;
    _Height = 0;
    //Collisionsrect setzen
    pCollisionRects.push_back({75, 90, 14, 14, "WORLDCOLISION" });
    _TextureID = "player";

    //Lade Animationen
    pAnimation.Load("assets/Player/Animation/Animation.lua");
    pAnimation.SetAnimationToID("PlayerMaleWalkingSouth");
    pAnimation.SetDrawSize({64,64});
    _Visable = true;

    // _SwordSound =  LoadSound (std::string(std::string(DATAPATH)+std::string("Sword.wav")).c_str());
}

void Eric::Player::Draw() {
    pAnimation.Draw();
    GraphicGameObject::Draw();
}

void Eric::Player::HandleInput() {
    bool move = false;
    bool attack = false;
    if (LibEric::Button_Up_Down() && LibEric::Button_Right_Down()){
        pDirection = NORTHEAST;
        pAnimationToPlay = WALK;
        pAnimation.Play();
        move = true;
    }
    else if (LibEric::Button_Up_Down() && LibEric::Button_Left_Down()){
        pDirection = NORTHWEST;
        pAnimationToPlay = WALK;
        pAnimation.Play();
        move = true;
    }
    else if (LibEric::Button_Down_Down() && LibEric::Button_Right_Down()){
        pDirection = SOUTHEAST;
        pAnimationToPlay = WALK;
        pAnimation.Play();
        move = true;
    }
    else if (LibEric::Button_Down_Down() && LibEric::Button_Left_Down()){
        pDirection = SOUTHWEST;
        pAnimationToPlay = WALK;
        pAnimation.Play();
        move = true;
    }
    else if (LibEric::Button_Up_Down()){
        pDirection = NORTH;
        pAnimationToPlay = WALK;
        pAnimation.Play();
        move = true;
    }
    else if (LibEric::Button_Down_Down()){
        pDirection = SOUTH;
        pAnimationToPlay = WALK;
        pAnimation.Play();
        move = true;
    }
    else if (LibEric::Button_Right_Down()){
        pDirection = EAST;
        pAnimationToPlay = WALK;
        pAnimation.Play();
        move = true;
    }
    else if (LibEric::Button_Left_Down()){
        pDirection = WEST;
        pAnimationToPlay = WALK;
        pAnimation.Play();
        move = true;
    }

    if (LibEric::Button_X_Down()){
        pAnimationToPlay = RUNNING;
    }

    if (LibEric::Button_A_Down()){
        pAnimationToPlay = ATTACK;
        pAnimation.Play();
        attack = true;
    }
    if (LibEric::Button_Y_Down()){
        pAnimationToPlay = HIT;
        pAnimation.Play();
        attack = true;
    }
    if (LibEric::Button_B_Down()){
        pAnimationToPlay = TIPPINGOVER;
        pAnimation.Play();
        attack = true;
    }

    if ( pAnimationToPlay == ATTACK){
        pVelocity = {0.0f, 0.0f};
        //return;
    }

    if (pAnimationToPlay == RUNNING){
        if (pDirection == NORTH){
            pVelocity = {0.0f, -2.0f};
        }
        if (pDirection == SOUTH){
            pVelocity = {0.0f, 2.0f};
        }
        if (pDirection == EAST){
            pVelocity = {2.0f, 0.0f};
        }
        if (pDirection == WEST){
            pVelocity = {-2.0f, 0.0f};
        }
        if (pDirection == NORTHWEST){
            pVelocity = {-2.0f, -2.0f};
        }
        if (pDirection == SOUTHWEST){
            pVelocity = {-2.0f, 2.0f};
        }
        if (pDirection == NORTHEAST){
            pVelocity = {2.0f, -2.0f};
        }
        if (pDirection == SOUTHEAST){
            pVelocity = {2.0f, 2.0f};
        }
        //return;
    }
    if (pAnimationToPlay == WALK){
        if (pDirection == NORTH){
            pVelocity = {0.0f, -0.5f};
        }
        if (pDirection == SOUTH){
            pVelocity = {0.0f, 0.5f};
        }
        if (pDirection == EAST){
            pVelocity = {0.5f, 0.0f};
        }
        if (pDirection == WEST){
            pVelocity = {-0.5f, 0.0f};
        }
        if (pDirection == NORTHWEST){
            pVelocity = {-0.5f, -0.5f};
        }
        if (pDirection == SOUTHWEST){
            pVelocity = {-0.5f, 0.5f};
        }
        if (pDirection == NORTHEAST){
            pVelocity = {0.5f, -0.5f};
        }
        if (pDirection == SOUTHEAST){
            pVelocity = {0.5f, 0.5f};
        }
        //return;
    }
    if (!move) {
        pVelocity = {0, 0};
    }
    if (!move && !attack) {
        pAnimation.Stop();
    }
    return;
}

void Eric::Player::Update() {
    HandleInput();

    float oldx = _Position.x;
    float oldy = _Position.y;

    pOldPosition = _Position;
    _Position.x += pVelocity.x;
    _Position.y += pVelocity.y;

    pAnimation.SetDrawPosition({_Position.x, _Position.y});
    pAnimation.Update();

    if (pAnimationToPlay == ATTACK){
        switch (pDirection){
            case NORTH:
                pAnimation.SetAnimationToID("PlayerMaleAttackNorth");
                break;
            case NORTHEAST:
                pAnimation.SetAnimationToID("PlayerMaleAttackNortheast");
                break;
            case NORTHWEST:
                pAnimation.SetAnimationToID("PlayerMaleAttackNorthwest");
                break;
            case SOUTH:
                pAnimation.SetAnimationToID("PlayerMaleAttackSouth");
                break;
            case SOUTHEAST:
                pAnimation.SetAnimationToID("PlayerMaleAttackSoutheast");
                break;
            case SOUTHWEST:
                pAnimation.SetAnimationToID("PlayerMaleAttackSouthwest");
                break;
            case EAST:
                pAnimation.SetAnimationToID("PlayerMaleAttackEast");
                break;
            case WEST:
                pAnimation.SetAnimationToID("PlayerMaleAttackWest");
                break;
        }
    }
    if (pAnimationToPlay == RUNNING){
        switch (pDirection){
            case NORTH:
                pAnimation.SetAnimationToID("PlayerMaleRunningNorth");
                break;
            case NORTHEAST:
                pAnimation.SetAnimationToID("PlayerMaleRunningNortheast");
                break;
            case NORTHWEST:
                pAnimation.SetAnimationToID("PlayerMaleRunningNorthwest");
                break;
            case SOUTH:
                pAnimation.SetAnimationToID("PlayerMaleRunningSouth");
                break;
            case SOUTHEAST:
                pAnimation.SetAnimationToID("PlayerMaleRunningSoutheast");
                break;
            case SOUTHWEST:
                pAnimation.SetAnimationToID("PlayerMaleRunningSouthwest");
                break;
            case EAST:
                pAnimation.SetAnimationToID("PlayerMaleRunningEast");
                break;
            case WEST:
                pAnimation.SetAnimationToID("PlayerMaleRunningWest");
                break;
        }
    }
    if (pAnimationToPlay == WALK){
        switch (pDirection){
            case NORTH:
                pAnimation.SetAnimationToID("PlayerMaleWalkingNorth");
                break;
            case NORTHEAST:
                pAnimation.SetAnimationToID("PlayerMaleWalkingNortheast");
                break;
            case NORTHWEST:
                pAnimation.SetAnimationToID("PlayerMaleWalkingNorthwest");
                break;
            case SOUTH:
                pAnimation.SetAnimationToID("PlayerMaleWalkingSouth");
                break;
            case SOUTHEAST:
                pAnimation.SetAnimationToID("PlayerMaleWalkingSoutheast");
                break;
            case SOUTHWEST:
                pAnimation.SetAnimationToID("PlayerMaleWalkingSouthwest");
                break;
            case EAST:
                pAnimation.SetAnimationToID("PlayerMaleWalkingEast");
                break;
            case WEST:
                pAnimation.SetAnimationToID("PlayerMaleWalkingWest");
                break;
        }
    }
    if (pAnimationToPlay == TIPPINGOVER){
        switch (pDirection){
            case NORTH:
                pAnimation.SetAnimationToID("PlayerMaleTippingoverNorth");
                break;
            case NORTHEAST:
                pAnimation.SetAnimationToID("PlayerMaleTippingoverNortheast");
                break;
            case NORTHWEST:
                pAnimation.SetAnimationToID("PlayerMaleTippingoverNorthwest");
                break;
            case SOUTH:
                pAnimation.SetAnimationToID("PlayerMaleTippingoverSouth");
                break;
            case SOUTHEAST:
                pAnimation.SetAnimationToID("PlayerMaleTippingoverSoutheast");
                break;
            case SOUTHWEST:
                pAnimation.SetAnimationToID("PlayerMaleTippingoverSouthwest");
                break;
            case EAST:
                pAnimation.SetAnimationToID("PlayerMaleTippingoverEast");
                break;
            case WEST:
                pAnimation.SetAnimationToID("PlayerMaleTippingoverWest");
                break;
        }
    }
    if (pAnimationToPlay == HIT){
        switch (pDirection){
            case NORTH:
                pAnimation.SetAnimationToID("PlayerMaleHitNorth");
                break;
            case NORTHEAST:
                pAnimation.SetAnimationToID("PlayerMaleHitNortheast");
                break;
            case NORTHWEST:
                pAnimation.SetAnimationToID("PlayerMaleHitNorthwest");
                break;
            case SOUTH:
                pAnimation.SetAnimationToID("PlayerMaleHitSouth");
                break;
            case SOUTHEAST:
                pAnimation.SetAnimationToID("PlayerMaleHitSoutheast");
                break;
            case SOUTHWEST:
                pAnimation.SetAnimationToID("PlayerMaleHitSouthwest");
                break;
            case EAST:
                pAnimation.SetAnimationToID("PlayerMaleHitEast");
                break;
            case WEST:
                pAnimation.SetAnimationToID("PlayerMaleHitWest");
                break;
        }
    }
    float offsetx = _Position.x - oldx;
    float offsety = _Position.y -oldy;
    pCollisionRects[0].x += offsetx;
    pCollisionRects[0].y += offsety;
}

void Eric::Player::Clean() {
}


void Eric::Player::SetPosition(float x, float y) {
    float oldx = _Position.x;
    float oldy = _Position.y;

    _Position.x = x;
    _Position.y = y;
    pAnimation.SetDrawPosition({x,y});
    float offsetx = _Position.x - oldx;
    float offsety = _Position.y - oldy;
    pCollisionRects[0].x += offsetx;
    pCollisionRects[0].y += offsety;
}

//! Ist das Objekt beweglich
bool Eric::Player::Moveable(){
    return true;
}

void Eric::Player::PositionReset() {
    float oldx = _Position.x;
    float oldy = _Position.y;

    _Position.x = pOldPosition.x;
    _Position.y = pOldPosition.y;
    pAnimation.SetDrawPosition({_Position.x,_Position.y});
    float offsetx = _Position.x - oldx;
    float offsety = _Position.y - oldy;
    pCollisionRects[0].x += offsetx;
    pCollisionRects[0].y += offsety;
}

//! Dise Funktion wird vom ColisionManager aufgerufen, wenn zwei Objekte sich berühren
void Eric::Player::Collision(std::string Type, void *data){
    if (Type == "MapCollision"){
        PositionReset();
        LOGW("HIER");
    }
}

std::vector<LibEric::CollisionRectangle> Eric::Player::GetRects() {
    return pCollisionRects;
}

Vector2 Eric::Player::GetPosition() {
    return _Position;
}

