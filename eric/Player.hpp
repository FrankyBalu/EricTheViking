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

#ifndef __PLAYER
#define __PLAYER

#include <libEric/Graphic/GraphicGameObject.hpp>
#include <libEric/Graphic/Animation.hpp>
#include <raylib.h>

namespace Eric {

    enum PLAYER_DIRECTION {
        ANIM_NONE = -1,
        NORTH = 0,
        NORTHEAST = 1,
        EAST = 2,
        SOUTHEAST = 3,
        SOUTH = 5,
        SOUTHWEST = 4,
        WEST = 6,
        NORTHWEST = 7,
        DIRECTION_MAX
    };

    enum PLAYER_ANIMATION {
        NONE = 0,
        WALK = 1,
        RUNNING = 2,
        HIT =3 ,
        TIPPINGOVER = 4,
        ATTACK = 5,
        ANIMATION_MAX
    };


    class Player : public LibEric::GraphicGameObject {
    public:

        static Player *Instance();

        void Load(const std::string scriptFile);

        void Draw();

        void Update();

        void Clean();



        Vector2 GetPosition();

        void SetPosition(float x, float y);

        //! Ist das Objekt beweglich
        bool Moveable() override;

        //! Dise Funktion wird vom ColisionManager aufgerufen, wenn zwei Objekte sich berühren
        void Collision(std::string ownType, void *data) override;

        std::string GetID() { return std::string("Player"); }

        std::vector<LibEric::CollisionRectangle> GetRects();


    private:

        Player();

        void HandleInput();

        void PositionReset();

        PLAYER_ANIMATION pAnimationToPlay;
        PLAYER_DIRECTION pDirection;

        Vector2 pVelocity;

        Vector2 pOldPosition;

        LibEric::Animation pAnimation;

        Sound _SwordSound;
        static Player *pInstance;

    };


}; //namespace Eric
#endif // PLAYER_H
