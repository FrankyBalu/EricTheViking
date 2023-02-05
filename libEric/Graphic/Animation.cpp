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

#include <libEric/Graphic/Animation.hpp>
#include <libEric/Core/UserSettings.hpp>
#include <libEric/Graphic/RenderManager.hpp>
#include <libEric/Core/Lua.hpp>
#include <libEric/Core/Log.hpp>
#include <physfs.h>

#define SOL_ALL_SAFETIES_ON 1
#include <sol.hpp>

LibEric::Animation::Animation(): Sprite("n/a"),pAnimationStruct(), pCurrentAnimationID(), pFrameCounter(0),
        pCurrentTexture(0), pCurrentTextureID(), play(false){

}

void LibEric::Animation::Load (std::string file){
    lua = new sol::state;
    lua->open_libraries(sol::lib::base);
    lua->open_libraries(sol::lib::string);

    LibEric::LuaSetup(lua);
#ifdef __linux__
    std::string EricDir = PHYSFS_getRealDir("/system/");
    EricDir += "/";
#else
    std::string EricDir = std::string("data\\");
#endif

    lua->set_function("AddTextureID", &Animation::AddTexture, this);
    lua->set_function("SetTextureRect", &Animation::SetTextureRect, this);
    lua->set_function("SetDrawRect", &Sprite::SetDrawSize, this);
    lua->set_function("SetAnimationID", &Animation::SetAnimationToID, this);
    lua->set_function("SetDuration", &Animation::SetDuration, this);
    lua->script_file(EricDir + file);

    return;
}

void LibEric::Animation::Draw() {
    Sprite::Draw();
}

void LibEric::Animation::Update() {
    if (!play)
        return;


    if (pFrameCounter < GetFPS())
        pFrameCounter++;
    else {
        Reset();
        return;
    }

    int durationFrames = GetFPS() * pAnimationStruct[pCurrentAnimationID].Duration;


    if (pFrameCounter > durationFrames)
        return;

    int FramesPerTexture = durationFrames / (pAnimationStruct[pCurrentAnimationID].NumFrames - 1);

    pCurrentTexture = pFrameCounter / FramesPerTexture;
    if (pCurrentTexture > pAnimationStruct[pCurrentAnimationID].NumFrames - 1)
        pCurrentTexture = pAnimationStruct[pCurrentAnimationID].NumFrames - 1;
    LOGV("Animationsdaten Update(): ", pCurrentAnimationID);
    LOGV("    CurrentFrame        : ", pFrameCounter);
    LOGV("    Animationslänge     : ", durationFrames);
    LOGV("    Frames pro Texture  : ", FramesPerTexture);
    LOGV("    CurrentTexture      : ", pCurrentTexture);
    Sprite::SetTextureID( pAnimationStruct[pCurrentAnimationID].TextureIDs[pCurrentTexture]);
}

void LibEric::Animation::Clean() {
    LOGW ("Funktion muss noch Inplementiert werden");
}

std::string LibEric::Animation::GetID() {
    return pCurrentAnimationID;
}

void LibEric::Animation::Play (){
    play = true;
}

void LibEric::Animation::Stop (){
    play = false;
    Reset();
}

void LibEric::Animation::Reset(){
    pFrameCounter = 0;
    pCurrentTexture = 0;
}

bool LibEric::Animation::SetAnimationToID(std::string id) {
    if (pCurrentAnimationID == id)
        return true;
    if (pAnimationStruct.count(id) == 0 ){
        LOGE("Animation mit ID <", id, "> nicht vorhanden!");
        return false;
    }
    LOGV("Wechsel von Animations ID <", pCurrentAnimationID, "> zu <", id, ">");
    pCurrentAnimationID = id;
    LOGW("AnimationsID: ", pCurrentAnimationID);
    LOGW("TextureID   : ", pAnimationStruct[id].TextureIDs[pCurrentTexture]);
    Sprite::SetTextureID(pAnimationStruct[id].TextureIDs[pCurrentTexture]);
    //Sprite::SetTexturePosition({0,0}); //FIXME Textureposition wenn mehrere Bilder in einer Datei sind?
    Sprite::SetTextureSize({pAnimationStruct[id].TextureRect.width, pAnimationStruct[id].TextureRect.height});
    return true;
}



void LibEric::Animation::AddTexture(std::string id, std::string path, std::string newTex){
    LOGV("Füge neue Texture <", newTex, "> zu Animation <", id, "> hinzu");
    if (!path.empty()) {
        if (!RenderManager::Instance()->LoadTextureFromFile(newTex, path + newTex)) {
            return;
        }
    }
    int tmpNumFrames = 0;
    if (pAnimationStruct.count(id) != 0) {
        pAnimationStruct[id].NumFrames++;
        pAnimationStruct[id].TextureIDs.push_back(newTex);
    }
    else{
        LOGV("     Neu angelegt");
        AnimationStruct t;
        t.TextureIDs.push_back(newTex);
        t.NumFrames = 1;
        pAnimationStruct[id] = t;
    }
    return;
}

bool LibEric::Animation::SetDuration(std::string animationID, float duration) {
    if (pAnimationStruct.count(animationID) == 0){
        LOGE("Animation mit ID <", animationID, "> existiert nicht");
        return false;
    }
    if (duration <= 0){
        LOGE("Animation mit laufzeit <= 0 nicht möglich");
        return false;
    }
    pAnimationStruct[animationID].Duration = duration;
    return true;
}

void LibEric::Animation::SetTextureRect(std::string id, float x, float y, float w, float h) {
    pAnimationStruct[id].TextureRect = {x, y, w, h};
}


