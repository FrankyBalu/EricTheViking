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

#include "Animation.hpp"
#include <libEric/UserSettings.hpp>
#include <libEric/RenderManager.hpp>
#include <libEric/Lua.hpp>
#include <libEric/Log.hpp>
#include <physfs.h>

LibEric::Animation::Animation(): Sprite("n/a"),_Duration(1.0f){

}

void LibEric::Animation::Load (std::string file){
    lua.open_libraries(sol::lib::base);
    lua.open_libraries(sol::lib::string);

    LibEric::LuaSetup(&lua);
#ifdef __linux__
    std::string EricDir = PHYSFS_getRealDir("/system/");
    EricDir += "/";
#else
    std::string EricDir = std::string("data\\scripts\\");
#endif

    lua.set_function("AddTextureID", &Animation::AddTexture, this);
    lua.set_function("SetTextureRect", &Animation::SetTextureRect, this);
    lua.set_function("SetDrawRect", &Animation::SetDrawRect, this);
    lua.set_function("SetAnimationID", &Animation::SetAnimationToID, this);
    lua.script_file(EricDir + file);

    return;
}

void LibEric::Animation::Play (){
    play = true;
}

void LibEric::Animation::Stop (){
    play = false;
    Reset();
}

void LibEric::Animation::Reset(){
    _CurrentFrame = 0;
    _CurrentTexture = 0;
}

void LibEric::Animation::Update() {
    if (!play)
        return;

    if (_CurrentFrame < LibEric::UserSettings::Instance()->GetFPS())
        _CurrentFrame++;
    else {
        Reset();
        return;
    }

    int PlayFrames = GetFPS() * _Duration;

    if (_CurrentFrame > PlayFrames)
        return;

    int FramesPerTexture = PlayFrames / (_AnimationsStruct[_CurrentAnimationID].NumFrames - 1);

    _CurrentTexture = _CurrentFrame / FramesPerTexture;
/*
    LOGW("PlayFrames: ", PlayFrames);
    LOGI("numFrames: ", _AnimationsStruct[_CurrentAnimationID].NumFrames);
    LOGI("FramesPerTexture: ", FramesPerTexture);
    LOGI(":CurrentTexture: ", FramesPerTexture);
    LOGI("CurrentFrame: ", _CurrentFrame);
*/

    Sprite::SetTextureID( _AnimationsStruct[_CurrentAnimationID].TextureIDs[_CurrentTexture]);

}

void LibEric::Animation::AddTexture(std::string id, std::string path, std::string newTex){
    LOGW("add New Texture to animation: ", newTex);
    RenderManager::Instance()->LoadTextureFromFile(newTex, path  + newTex);
    int tmpNumFrames = 0;
    if (_AnimationsStruct.count(id) != 0) {
        LOGI("ID <", id, "> existiert bereits");
        _AnimationsStruct[id].NumFrames += 1;
        _AnimationsStruct[id].TextureIDs.push_back(newTex);
    }
    else{
        LOGI("ID <", id, "> existiert noch nicht");
        as t;
        t.TextureIDs.push_back(newTex);
        t.NumFrames =1;
        _AnimationsStruct[id] = t;
    }
    return;
}

void LibEric::Animation::SetDrawRect(float x, float y, float w, float h) {
    Sprite::SetDrawPosition({x,y});
    Sprite::SetDrawSize({w,h});
}

void LibEric::Animation::SetTextureRect(std::string id, float x, float y, float w, float h) {
    _AnimationsStruct[id].TextureRect = {x, y, w, h};
}

void LibEric::Animation::SetPosition(float x, float y) {
    Sprite::SetDrawPosition({x,y});
}

void LibEric::Animation::Draw() {
    Sprite::Draw();
}

void LibEric::Animation::SetAnimationToID(std::string id) {
    _CurrentAnimationID = id;
    Sprite::SetTextureID(_AnimationsStruct[id].TextureIDs[0]);
    Rectangle rec = {0,0,_AnimationsStruct[id].TextureRect.width, _AnimationsStruct[id].TextureRect.height};
    Sprite::SetTexturePosition({0,0});
    Sprite::SetTextureSize({_AnimationsStruct[id].TextureRect.width, _AnimationsStruct[id].TextureRect.height});
    //Sprite::SetPosition({_AnimationsStruct[id].TextureRect.x, _AnimationsStruct[id].TextureRect.y});
}