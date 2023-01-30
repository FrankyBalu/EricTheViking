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
    _Visable = true;
}


void Eric::Player::Draw()
{
    int speed = GetFPS() / 4;
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
}

void Eric::Player::Clean()
{
    //  DLOG << "clean player\n";
}

void Eric::Player::HandleInput()
{
        if ( LibEric::Button_Right() ) {
            _Velocity.x = 0.5f;
            if ( _AnimationToPlay == PLAYER_ANIMATION_TO_PLAY::NONE ) {
                _AnimationToPlay = PLAYER_ANIMATION_TO_PLAY::WALK;
                _Frame = 0;
                _Direction = 2;
                _CurrentRow = WALK_RIGHT;
            }

        }
        if ( LibEric::Button_Left() ) {
            _Velocity.x = -0.5f;
            if ( _AnimationToPlay == PLAYER_ANIMATION_TO_PLAY::NONE ) {
                _AnimationToPlay = PLAYER_ANIMATION_TO_PLAY::WALK;
                _Frame = 0;
                _Direction = 4;
                _CurrentRow = WALK_LEFT;
            }
        }
        if ( LibEric::Button_Down() ) {
            _Velocity.y = 0.5f;
            if ( _AnimationToPlay == PLAYER_ANIMATION_TO_PLAY::NONE ) {
                _AnimationToPlay = PLAYER_ANIMATION_TO_PLAY::WALK;
                _Frame = 0;
                _Direction = 3;
                _CurrentRow = WALK_DOWN;
            }
        }
        if ( LibEric::Button_Up() ) {
            _Velocity.y = -0.5f;
            if ( _AnimationToPlay == PLAYER_ANIMATION_TO_PLAY::NONE ) {
                _AnimationToPlay = PLAYER_ANIMATION_TO_PLAY::WALK;
                _Frame = 0;
                _Direction = 1;
                _CurrentRow = WALK_UP;
            }
        }

    if ( LibEric::Button_Right_Down() ) {
        _Velocity.x = 1.0;
        if ( _AnimationToPlay == PLAYER_ANIMATION_TO_PLAY::NONE ) {
            _AnimationToPlay = PLAYER_ANIMATION_TO_PLAY::WALK;
            _Frame = 0;
            _Direction = 2;
            _CurrentRow = WALK_RIGHT;
        }

    }
    if ( LibEric::Button_Left_Down() ) {
        _Velocity.x = -0.5f;
        if ( _AnimationToPlay == PLAYER_ANIMATION_TO_PLAY::NONE ) {
            _AnimationToPlay = PLAYER_ANIMATION_TO_PLAY::WALK;
            _Frame = 0;
            _Direction = 4;
            _CurrentRow = WALK_LEFT;
        }
    }
    if ( LibEric::Button_Down_Down() ) {
        _Velocity.y = 0.5f;
        if ( _AnimationToPlay == PLAYER_ANIMATION_TO_PLAY::NONE ) {
            _AnimationToPlay = PLAYER_ANIMATION_TO_PLAY::WALK;
            _Frame = 0;
            _Direction = 3;
            _CurrentRow = WALK_DOWN;
        }
    }
    if ( LibEric::Button_Up_Down() ) {
        _Velocity.y = -0.5f;
        if ( _AnimationToPlay == PLAYER_ANIMATION_TO_PLAY::NONE ) {
            _AnimationToPlay = PLAYER_ANIMATION_TO_PLAY::WALK;
            _Frame = 0;
            _Direction = 1;
            _CurrentRow = WALK_UP;
        }
    }

    if ( LibEric::Button_X() ) {
        _Velocity.x *= 4.0f;
        _Velocity.y *= 4.0f;
    }
    if ( !LibEric::Button_X() ) {
        _Acceleration.x = 0;
        _Acceleration.y = 0;
    }


    if ( LibEric::Button_A() ) {
        _AnimationToPlay = PLAYER_ANIMATION_TO_PLAY::SWORT;
        // PlaySound ( _SwordSound );
        _Frame = 0;
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


    _Visable = true;


    // TextureManager::Instance()->Load ( std::string(std::string(DATAPATH)+std::string("Heart.png")), "heart" );
    // _SwordSound =  LoadSound (std::string(std::string(DATAPATH)+std::string("Sword.wav")).c_str());
}

void Eric::Player::SetPosition(float x, float y) {
    _Position.x = x;
    _Position.y = y;
}

