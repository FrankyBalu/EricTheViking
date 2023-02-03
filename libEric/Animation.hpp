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

#ifndef ERIC_ANIMATION_HPP
#define ERIC_ANIMATION_HPP

#include <libEric/Sprite.hpp>
#include <vector>
#include <map>
#include <sol/sol.hpp>

namespace LibEric {

    typedef struct as{
        std::vector<std::string> TextureIDs;
        Rectangle TextureRect;
        int NumFrames;
    } as;
    class Animation : public Sprite{
    public:
        Animation();


        void Load(const std::string scriptFile);

        void Play ();

        void SetTextureRect(std::string id, float x, float y, float w, float h);

        void SetDrawRect(float x, float y, float w, float h);

        void SetPosition(float x, float y);

        void Stop ();

        void Reset();

        void Update();

        void Draw();

        void SetAnimationToID (std::string id);

        void AddTexture(std::string animationID, std::string path, std::string);
    private:
        std::map<std::string,as> _AnimationsStruct;

        std::string _CurrentAnimationID;

        float _Duration;
        int _CurrentFrame;
        int _CurrentTexture;
        std::string _CurrentTextureID;


        sol::state lua;

        bool play;
    };

} // LibEric

#endif //ERIC_ANIMATION_HPP
