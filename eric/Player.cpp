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
#include <libEric/GameStateMaschine.hpp>
#include <libEric/RenderManager.hpp>
#include <libEric/LibEricSettings.hpp>
#include <raylib.h>
#include <libEric/Log.hpp>
#include <libEric/Input.hpp>
#include <libEric/UserSettings.hpp>

Eric::Player *Eric::Player::_Instance = nullptr;

Eric::Player *Eric::Player::Instance() {
    if (_Instance == nullptr) {
        _Instance = new Player();
    }
    return _Instance;
}


Eric::Player::Player() :
        GraphicGameObject() {
    _Position.x = 10;
    _Position.y = 10;
    _Visable = true;
    _TypeID = "Player";
}


void Eric::Player::Draw() {

    _Animation.Draw();
    GraphicGameObject::Draw();
}

void Eric::Player::Update() {
    HandleInput();
    float oldx = _Position.x;
    float oldy = _Position.y;

    oldPosition = _Position;
    _Position.x += _Velocity.x;
    _Position.y += _Velocity.y;
    _Animation.SetPosition(_Position.x, _Position.y);
    _Animation.Update();

    float offsetx = oldx - _Position.x;
    float offsety = oldy - _Position.y;
    _CollisionRect.x += offsetx;
    _CollisionRect.y += offsety;
}

void Eric::Player::Clean() {
}

void Eric::Player::HandleInput() {
    //und runter und x (rennen)
    if ( LibEric::Button_Right_Down() && LibEric::Button_Down_Down()){
        if (LibEric::Button_X_Down()) {
            _Animation.SetAnimationToID("PlayerMaleRunningSoutheast");
            _Velocity.x = 2.0f;
            _Velocity.y = 2.0f;
        }
        else {
            _Animation.SetAnimationToID("PlayerMaleWalkingSoutheast");
            _Velocity.x = 0.5f;
            _Velocity.y = 0.5f;
        }
        _Animation.Play();
        return;
    }//nur runter
    else if (LibEric::Button_Right_Down() && LibEric::Button_Up_Down()){
        if (LibEric::Button_X_Down()) {
            _Animation.SetAnimationToID("PlayerMaleRunningNortheast");
            _Velocity.x = 2.0f;
            _Velocity.y = -2.0f;
        }
        else{
            _Animation.SetAnimationToID("PlayerMaleWalkingNortheast");
            _Velocity.x = 0.5f;
            _Velocity.y = -0.5f;
        }
        _Animation.Play();
        return;
    }
    //Nach rechst
    if (LibEric::Button_Right_Down()) {
        if (LibEric::Button_X_Down()){
            _Animation.SetAnimationToID("PlayerMaleRunningEast");
            _Velocity.x = 2.0f;
            _Velocity.y = 0.0f;
        }
        else {
            _Animation.SetAnimationToID("PlayerMaleWalkingEast");
            _Velocity.x = 0.5f;
            _Velocity.y = 0.0f;
        }
        _Animation.Play();
        return;
    }
    else if ( LibEric::Button_Left_Down() && LibEric::Button_Down_Down()){
        if (LibEric::Button_X_Down()) {
            _Animation.SetAnimationToID("PlayerMaleRunningSouthwest");
            _Velocity.x = -2.0f;
            _Velocity.y = 2.0f;
        }
        else {
            _Animation.SetAnimationToID("PlayerMaleWalkingSouthwest");
            _Velocity.x = -0.5f;
            _Velocity.y = 0.5f;
        }
        _Animation.Play();
        return;
    }//nur runter
    else if (LibEric::Button_Left_Down() && LibEric::Button_Up_Down()){
        if (LibEric::Button_X_Down()) {
            _Animation.SetAnimationToID("PlayerMaleRunningNorthwest");
            _Velocity.x = -2.0f;
            _Velocity.y = -2.0f;
        }
        else{
            _Animation.SetAnimationToID("PlayerMaleWalkingNorthwest");
            _Velocity.x = -0.5f;
            _Velocity.y = -0.5f;
        }
        _Animation.Play();
        return;
    }
    //Nach rechst
    if (LibEric::Button_Left_Down()) {
        if (LibEric::Button_X_Down()){
            _Animation.SetAnimationToID("PlayerMaleRunningWest");
            _Velocity.x = -2.0f;
            _Velocity.y = 0.0f;
        }
        else {
            _Animation.SetAnimationToID("PlayerMaleWalkingWest");
            _Velocity.x = -0.5f;
            _Velocity.y = 0.0f;
        }
        _Animation.Play();
        return;
    }
    else if (LibEric::Button_Up_Down()){
        if (LibEric::Button_X_Down()){
            _Animation.SetAnimationToID("PlayerMaleRunningNorth");
            _Velocity.x = 0.0f;
            _Velocity.y = -2.0f;
        }
        else {
            _Animation.SetAnimationToID("PlayerMaleWalkingNorth");
            _Velocity.x = 0.0f;
            _Velocity.y = -0.5f;
        }
        _Animation.Play();
        return;
    }
    else if (LibEric::Button_Down_Down()){
        if (LibEric::Button_X_Down()){
            _Animation.SetAnimationToID("PlayerMaleRunningSouth");
            _Velocity.x = 0.0f;
            _Velocity.y = 2.0f;
        }
        else {
            _Animation.SetAnimationToID("PlayerMaleWalkingSouth");
            _Velocity.x = 0.0f;
            _Velocity.y = 0.5f;
        }
        _Animation.Play();
        return;
    }
    else{
        _Animation.Stop();
        _Velocity = {0.0f,0.0f};
    }
    return;
}

void Eric::Player::Load(std::string scriptFile) {
    GraphicGameObject::Load(scriptFile);
    _Position.x = 50;
    _Position.y = 50;
    _Width = 64;
    _Height = 64;
    _TextureID = "player";
    _CurrentFrame = 0;
    _CurrentRow = 0;


    //Lade Animationen
    _Animation.Load("assets/Player/Animation/Animation.lua");
   /* _Animation[NORTH][WALK].Load("assets/Player/walking/north/Animation.lua");
    _Animation[NORTHEAST][WALK].Load("assets/Player/walking/northeast/Animation.lua");
    _Animation[NORTHWEST][WALK].Load("assets/Player/walking/northwest/Animation.lua");
    _Animation[SOUTH][WALK].Load("assets/Player/walking/south/Animation.lua");
    _Animation[SOUTHEAST][WALK].Load("assets/Player/walking/southeast/Animation.lua");
    _Animation[SOUTHWEST][WALK].Load("assets/Player/walking/southwest/Animation.lua");
    _Animation[WEST][WALK].Load("assets/Player/walking/west/Animation.lua");
    _Animation[EAST][RUNNING].Load("assets/Player/running/east/Animation.lua");
    _Animation[NORTH][RUNNING].Load("assets/Player/running/north/Animation.lua");
    _Animation[NORTHEAST][RUNNING].Load("assets/Player/running/northeast/Animation.lua");
    _Animation[NORTHWEST][RUNNING].Load("assets/Player/running/northwest/Animation.lua");
    _Animation[SOUTH][RUNNING].Load("assets/Player/running/south/Animation.lua");
    _Animation[SOUTHEAST][RUNNING].Load("assets/Player/running/southeast/Animation.lua");
    _Animation[SOUTHWEST][RUNNING].Load("assets/Player/running/southwest/Animation.lua");
    _Animation[WEST][RUNNING].Load("assets/Player/running/west/Animation.lua");
*/
   // _CurrentAnimation = &_Animation[SOUTH][WALK];
    _Visable = true;
    LOGI("hier");

    // TextureManager::Instance()->Load ( std::string(std::string(DATAPATH)+std::string("Heart.png")), "heart" );
    // _SwordSound =  LoadSound (std::string(std::string(DATAPATH)+std::string("Sword.wav")).c_str());
}

void Eric::Player::SetPosition(float x, float y) {
    _Position.x = x;
    _Position.y = y;
    _CurrentAnimation->SetPosition(x,y);
}

//! Ist das Objekt beweglich
bool Eric::Player::Moveable(){
    return true;
}

void Eric::Player::PositionReset() {
    _Position.x = oldPosition.x;
    _Position.y = oldPosition.y;
    _CurrentAnimation->SetPosition(_Position.x,_Position.y);
}

//! Dise Funktion wird vom ColisionManager aufgerufen, wenn zwei Objekte sich berühren
void Eric::Player::Collision(std::string Type, void *data){
    if (Type == "MapCollision"){
        PositionReset();
    }
}
