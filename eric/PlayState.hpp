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


#ifndef ERIC_PLAYSTATE_HPP
#define ERIC_PLAYSTATE_HPP

#include <libEric/Core/GameState.hpp>
#include <libEric/Core/GameStateFactory.hpp>
#include <libEric/Graphic/GraphicGameObject.hpp>
#include <libEric/Core/CollisionManager.hpp>
#include <libEric/Graphic/Animation.hpp>
#include <raylib.h>
#include <vector>

namespace Eric {

    class PlayState : public LibEric::GameState {
    public:
        PlayState();

        void HandleEvents() override {};

        virtual void Update() override;

        virtual void Render() override;

        virtual bool OnEnter(std::string file = "") override;

        virtual bool OnExit() override;

        virtual std::string GetStateID() const override;

        bool CheckCollision(LibEric::GraphicGameObject *obj1, LibEric::GraphicGameObject *obj2);

    private:

        static const std::string _PlayID;
        Camera2D _Camera;
        std::vector<LibEric::GameObject_Interface *> _Objects;

        Music _BackgroundMusic;
        LibEric::CollisionManager _CollisionManager;
        void Resize() {}
        LibEric::Animation animation;

    };

    class PlayCreator : public LibEric::StateBaseCreator {
    public:
        LibEric::GameState *CreateState() const {
            return new PlayState();
        }
    };

}; //namespace Eric
#endif // PLAYSTATE
