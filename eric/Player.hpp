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

#include <libEric/GraphicGameObject.hpp>
#include <libEric/Animation.hpp>
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


        virtual void Draw() override;

        virtual void Update() override;

        virtual void Clean() override;

        virtual void Load(const std::string scriptFile) override;


        Vector2 GetPosition() {
            return _Position;
        }

        void SetPosition(float x, float y);

        //! Ist das Objekt beweglich
        bool Moveable() override;

        //! Dise Funktion wird vom ColisionManager aufgerufen, wenn zwei Objekte sich berühren
        void ObjectCollision(std::string ownType, void *data) override;

        std::string GetID() { return std::string("Player"); }

        std::vector<LibEric::EricRect> GetRects() override {
            LibEric::EricRect rect;
            rect.x = _Position.x;
            rect.y = _Position.y;
            rect.height = _Height;
            rect.width = _Width;
            rect.type = "WORLDCOLISION";
            std::vector<LibEric::EricRect> r;
            r.push_back(rect);
            return r;
        }

    private:

        Player();

        void HandleInput();

        void PositionReset();

        PLAYER_ANIMATION _AnimationP;
        PLAYER_DIRECTION _Direction;

        Vector2 _Velocity;
        Vector2 _Acceleration;

        Rectangle _CollisionRect;
        Vector2 oldPosition;

        LibEric::Animation _Animation[DIRECTION_MAX][ANIMATION_MAX];
        LibEric::Animation *_CurrentAnimation;

        Sound _SwordSound;
        static Player *_Instance;

    };


}; //namespace Eric
#endif // PLAYER_H
