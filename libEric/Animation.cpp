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

bool LibEric::Animation::Load (std::string file){
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
    lua.script_file(EricDir + file);
    Sprite::SetTextureID(_TextureIDs[0]);
/*    LOGI ("Animation geladen: ");
    LOGI("_TextureID: ", _TextureID);
    LOGI("_TextureSize: x = ", _TextureSize.x);
    LOGI("_TextureSize: y = ", _TextureSize.y);
    LOGI("_TextureSize: w = ", _TextureSize.width);
    LOGI("_TextureSize: h = ", _TextureSize.height);
    LOGI("_DrawSize: x = ", _DrawSize.x);
    LOGI("_DrawSize: y = ", _DrawSize.y);
    LOGI("_DrawSize: w = ", _DrawSize.width);
    LOGI("_DrawSize: h = ", _DrawSize.height);*/
    return true;
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
    int PlayFrames = LibEric::UserSettings::Instance()->GetFPS() * _Duration;

    if (_CurrentFrame > PlayFrames)
        return;

    int FramesPerTexture = PlayFrames / (_TextureIDs.size() - 1);

    _CurrentTexture = _CurrentFrame / FramesPerTexture;
    Sprite::SetTextureID(_TextureIDs[_CurrentTexture]);
}

void LibEric::Animation::AddTexture(std::string path, std::string newTex){
    LOGW("add New Texture to animation: ", newTex);
    RenderManager::Instance()->LoadTextureFromFile(newTex, path  + newTex);
    _TextureIDs.push_back(newTex);
}

void LibEric::Animation::SetDrawRect(float x, float y, float w, float h) {
    Sprite::SetPosition({x,y});
    Sprite::SetSize({w,h});
}

void LibEric::Animation::SetTextureRect(float x, float y, float w, float h) {
    _TextureSize.x = x;
    _TextureSize.y = y;
    _TextureSize.width = w;
    _TextureSize.height = h;
}

void LibEric::Animation::SetPosition(float x, float y) {
    Sprite::SetPosition({x,y});
}

void LibEric::Animation::Draw() {
    Sprite::Draw();
}