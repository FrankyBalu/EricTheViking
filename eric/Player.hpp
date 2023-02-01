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
#include <raylib.h>

namespace Eric {

    enum PLAYER_ANIMATIONS {
        ANIM_NONE = -1,
        WALK_UP = 1,
        WALK_DOWN = 0,
        WALK_LEFT = 2,
        WALK_RIGHT = 3,
        SWORT_UP = 5,
        SWORT_DOWN = 4,
        SWORT_LEFT = 6,
        SWORT_RIGHT = 7
    };

    enum class PLAYER_ANIMATION_TO_PLAY {
        NONE = 0,
        WALK = 1,
        SWORT = 2
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

        PLAYER_ANIMATIONS _Animation;
        PLAYER_ANIMATION_TO_PLAY _AnimationToPlay;
        bool _PlayAnimation;
        int _Frame;

        float _Life;

        Vector2 _Velocity;
        Vector2 _Acceleration;
        int _Direction;
        int _NumFrames;

        Vector2 oldPosition;

        Sound _SwordSound;
        static Player *_Instance;

    };


}; //namespace Eric
#endif // PLAYER_H
