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
#include "../liberic/GameStateMaschine.hpp"
#include "../liberic/TextureManager.hpp"
#include "../liberic/PrivateSettings.hpp"
#include <raylib.h>
#include "../liberic/Log.hpp"

Eric::Player* Eric::Player::_Instance = nullptr;

Eric::Player * Eric::Player::Instance()
{
    if ( _Instance == nullptr ) {
        _Instance = new Player();
    }
    return _Instance;
}


Eric::Player::Player() :
    GraphicGameObject()
{
    _Position.x = 10;
    _Position.y = 10;
    _Frame = 0;
    _Life = 3.0;
    _IsAttack = false;
    _Visable = true;
}


void Eric::Player::Draw()
{
    int speed = GetFPS() / LibEric::PrivateSettings::Instance()->GetPlayerAnimationSpeed();
    if ( _AnimationToPlay != PLAYER_ANIMATION_TO_PLAY::NONE ) {
        if ( _Frame < speed *1 )
            _CurrentFrame = 0;
        else if ( _Frame < speed *2 )
            _CurrentFrame = 1;
        else if ( _Frame < speed * 3 )
            _CurrentFrame = 2;
        else if ( _Frame < speed * 4 )
            _CurrentFrame = 3;
        else {
            _AnimationToPlay = PLAYER_ANIMATION_TO_PLAY::NONE;
            _IsAttack = false;
            _Frame = 0;
        }
    } else {
        if ( _CurrentRow == 4 ) {
            _CurrentRow = 0;
            _Frame = 0;
        } else if ( _CurrentRow == 5 ) {
            _CurrentRow = 1;
            _Frame = 0;
        } else if ( _CurrentRow == 6 ) {
            _CurrentRow = 2;
            _Frame = 0;
        } else if ( _CurrentRow == 7 ) {
            _CurrentRow = 3;
            _Frame = 0;
        }
    }


    GraphicGameObject::Draw();
}

void Eric::Player::Update()
{
    if ( _Life <= 0.0 ) {
        LibEric::GameStateMaschine::Instance()->ChangeState ( "Menu", "GameOver.menu" );
    }
    _Velocity.x = 0;
    _Velocity.y = 0;


    HandleInput();

    if ( _Frame < GetFPS() )
        _Frame++;
    else
        _Frame = 0;

    _Position.x += _Velocity.x;
    _Position.y += _Velocity.y;


    _ObjectCollision.x = _Position.x + ( ( _Width - 10 ) /2 );
    _ObjectCollision.y = _Position.y + ( _Height-10 );
    _NorthCollision.x = _Position.x - 2;
    _NorthCollision.y = _Position.y - 1;
    _EastCollision.x = _Position.x + _Width - 2;
    _EastCollision.y = _Position.y - 1;
    _SouthCollision.x = _Position.x - 2;
    _SouthCollision.y = _Position.y + _Height - 2;
    _WestCollision.x = _Position.x - 2;
    _WestCollision.y = _Position.y - 1;


}

void Eric::Player::Clean()
{
    //  DLOG << "clean player\n";
}

void Eric::Player::HandleInput()
{
        if ( IsGamepadButtonDown ( 0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT ) ||IsKeyDown ( KEY_D ) ) {
            _Velocity.x = 0.9f;
            if ( _AnimationToPlay == PLAYER_ANIMATION_TO_PLAY::NONE ) {
                _AnimationToPlay = PLAYER_ANIMATION_TO_PLAY::WALK;
                _Frame = 0;
                _Direction = 2;
                _CurrentRow = WALK_RIGHT;
            }

        }
        if ( IsGamepadButtonDown ( 0, GAMEPAD_BUTTON_LEFT_FACE_LEFT ) ||IsKeyDown ( KEY_A ) ) {
            _Velocity.x = -0.9f;
            if ( _AnimationToPlay == PLAYER_ANIMATION_TO_PLAY::NONE ) {
                _AnimationToPlay = PLAYER_ANIMATION_TO_PLAY::WALK;
                _Frame = 0;
                _Direction = 4;
                _CurrentRow = WALK_LEFT;
            }
        }
        if ( IsGamepadButtonDown ( 0, GAMEPAD_BUTTON_LEFT_FACE_DOWN ) ||IsKeyDown ( KEY_S ) ) {
            _Velocity.y = 0.9f;
            if ( _AnimationToPlay == PLAYER_ANIMATION_TO_PLAY::NONE ) {
                _AnimationToPlay = PLAYER_ANIMATION_TO_PLAY::WALK;
                _Frame = 0;
                _Direction = 3;
                _CurrentRow = WALK_DOWN;
            }
        }
        if ( IsGamepadButtonDown ( 0, GAMEPAD_BUTTON_LEFT_FACE_UP ) ||IsKeyDown ( KEY_W ) ) {
            _Velocity.y = -0.9f;
            if ( _AnimationToPlay == PLAYER_ANIMATION_TO_PLAY::NONE ) {
                _AnimationToPlay = PLAYER_ANIMATION_TO_PLAY::WALK;
                _Frame = 0;
                _Direction = 1;
                _CurrentRow = WALK_UP;
            }
        }

    if ( IsGamepadButtonDown ( 0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT ) ||IsKeyDown ( KEY_RIGHT_SHIFT ) ) {
        _Velocity.x *= 4.0f;
        _Velocity.y *= 4.0f;
    }
    if ( !IsGamepadButtonDown ( 0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT ) ||!IsKeyDown ( KEY_RIGHT_SHIFT ) ) {
        _Acceleration.x = 0;
        _Acceleration.y = 0;
    }


    if ( IsGamepadButtonPressed ( 0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN ) ||IsKeyPressed ( KEY_DOWN ) ) {
        _AnimationToPlay = PLAYER_ANIMATION_TO_PLAY::SWORT;
        // PlaySound ( _SwordSound );
        _Frame = 0;
        _IsAttack = true;
        if ( _CurrentRow == WALK_UP )
            _CurrentRow = SWORT_UP;
        if ( _CurrentRow == WALK_DOWN )
            _CurrentRow = SWORT_DOWN;
        if ( _CurrentRow == WALK_LEFT )
            _CurrentRow = SWORT_LEFT;
        if ( _CurrentRow == WALK_RIGHT )
            _CurrentRow = SWORT_RIGHT;
    }
}

void Eric::Player::Load ( std::string scriptFile )
{
    GraphicGameObject::Load ( scriptFile );
    _Position.x = 50;
    _Position.y = 50;
    _Width = 18;
    _Height = 26;
    _TextureID = "player";
    _NumFrames = 5;
    _Frame = 0;
    _CurrentFrame = 0;
    _CurrentRow = 0;

    _ObjectCollision.x = _Position.x + ( ( _Width - 10 ) /2 );
    _ObjectCollision.y = _Position.y + ( _Height-10 );
    _ObjectCollision.width = 10;
    _ObjectCollision.height = 10;

    _NorthCollision.x = _Position.x-2;
    _NorthCollision.y = _Position.y-1;
    _NorthCollision.width = _Width+4;
    _NorthCollision.height = 5;

    _EastCollision.x = _Position.x + _Width - 2;
    _EastCollision.y = _Position.y - 1;
    _EastCollision.width = 5;
    _EastCollision.height = _Height + 4;

    _SouthCollision.x = _Position.x - 2;
    _SouthCollision.y = _Position.y + _Height - 2;
    _SouthCollision.width = _Width + 4;
    _SouthCollision.height = 5;

    _WestCollision.x = _Position.x - 2;
    _WestCollision.y = _Position.y - 1;
    _WestCollision.width = 4;
    _WestCollision.height = _Height + 2;

    _IsAttack = false;
    _Visable = true;


    // TextureManager::Instance()->Load ( std::string(std::string(DATAPATH)+std::string("Heart.png")), "heart" );
    // _SwordSound =  LoadSound (std::string(std::string(DATAPATH)+std::string("Sword.wav")).c_str());
}

bool Eric::Player::CollisionDetect ( GraphicGameObject* obj )
{

    if ( CheckCollisionRecs ( _ObjectCollision, obj->GetObject() ) ) {
        return true;
    }
    if ( CheckCollisionRecs ( _NorthCollision, obj->GetSouth() ) ) {
        PLOGW << "North CollisionDetect";
        if ( _IsAttack && _Direction == 1 ) {
// // //             obj->MinusHP();
            _IsAttack = false;
            return true;
        } //else
//             MinusHP();
    }
    if ( CheckCollisionRecs ( _SouthCollision, obj->GetNorth() ) ) {
        PLOGW << "South CollisionDetect";
        if ( _IsAttack && _Direction == 3 ) {
//             obj->MinusHP();
            _IsAttack = false;
            return true;
        } //else
//             MinusHP();
    }
    if ( CheckCollisionRecs ( _EastCollision, obj->GetWest() ) ) {
        PLOGW << "East CollisionDetect";
        if ( _IsAttack && _Direction == 2 ) {
//             obj->MinusHP();
            _IsAttack = false;
            return true;
        } //else
//             MinusHP();
    }
    if ( CheckCollisionRecs ( _WestCollision, obj->GetEast() ) ) {
        PLOGW << "West CollisionDetect";
        if ( _IsAttack && _Direction == 4 ) {
//             obj->MinusHP();
            _IsAttack = false;
            return true;
        } //else
//             MinusHP();
    }

    return false;
}

void Eric::Player::SetPosition(float x, float y) {
    _Position.x = x;
    _Position.y = y;
}

Rectangle Eric::Player::GetActionRect(){
    return _ObjectCollision;
}

Rectangle Eric::Player::GetCollisionRect(){
    return _ObjectCollision;
}
