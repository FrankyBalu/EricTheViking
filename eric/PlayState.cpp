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


#include "PlayState.hpp"
#include "Player.hpp"
#include <libEric/UserSettings.hpp>
#include <libEric/GameStateMaschine.hpp>
#include <libEric/RenderManager.hpp>
#include <libEric/Input.hpp>
#include <libEric/MapManager.hpp>
#include <libEric/Log.hpp>
#include <raylib.h>

const std::string Eric::PlayState::_PlayID = "PLAY";

bool warenInPause;

void Eric::PlayState::Update() {

    UpdateMusicStream(_BackgroundMusic);
    if (LibEric::Button_Menu()) {
        warenInPause = true;
        LibEric::GameStateMaschine::Instance()->PushState("Menu", "PauseMenu.lua");
    }

    if (warenInPause){
        SetMusicVolume (_BackgroundMusic, LibEric::UserSettings::Instance()->GetMusicVolume());
        warenInPause = false;
    }

    Vector2 oldPlayerPosition =  Player::Instance()->GetPosition();

    Player::Instance()->Update();
    LibEric::MapManager::Instance()->Update();
    //position geht von den orginal pixeln aus, nicht von denen des bildschirms
    float x = Player::Instance()->GetPosition().x - 224;
    float y = Player::Instance()->GetPosition().y - 128;

    if (x < 0.0f )
        x = 0.0f;
    if (y < 0.0f)
        y = 0.0f;

    //FIXME Mapgröße automatisch ermitteln

    _Camera.target = { x, y };
    if (IsWindowFullscreen()) {
        _Camera.zoom = 4;
    }
    else {
        _Camera.zoom = 2;
    }

    if (!IsMusicStreamPlaying(_BackgroundMusic)) {
        PlayMusicStream(_BackgroundMusic);
    }
}

void Eric::PlayState::Render() {
    BeginMode2D(_Camera);

    LibEric::MapManager::Instance()->Draw();
    Player::Instance()->Draw();

    EndMode2D();

}

Eric::PlayState::PlayState(){
}


bool Eric::PlayState::OnEnter([[maybe_unused]] std::string file) {

    std::string blueKnight (std::string("/assets/BlueKnight.png"));
    std::string npc (std::string("/assets/NPC.png"));
    std::string hero (std::string("/assets/Hero.png"));
    std::string bgMusic (std::string("/assets/BackgroundmusicDemo.ogg"));

    /*if(!LibEric::TextureManager::Instance()->Load(blueKnight, "BlueKnight")) {
        PLOGW << "Can't load player sprite";
    }
    if(!LibEric::TextureManager::Instance()->Load(npc, "NPC")) {
        PLOGW << "Can't load player sprite";
    }*/
    LibEric::RenderManager::Instance()->LoadTextureFromFile("player", hero);/* {
        PLOGW << "Can't load player sprite";
    }*/
    _BackgroundMusic =  LoadMusicStream(bgMusic.c_str());
    PlayMusicStream(_BackgroundMusic);
    SetMusicVolume (_BackgroundMusic, LibEric::UserSettings::Instance()->GetMusicVolume());

    //FIXME: MapManager um zwischen verschiedenen Karten zu wechseln
    LibEric::MapManager::Instance()->LoadMap(std::string ("/home/frank/Projekte/bin/share/EricTheViking") + std::string("/Maps/MainWorld.tmx"), "World");
    // LibEric::MapManager::Instance()->LoadMap(EricDir + std::string("/assets/House.tmx"), "House1");
    // LibEric::MapManager::Instance()->LoadMap(EricDir + std::string("/assets/House2.tmx"), "House2");
    LibEric::MapManager::Instance()->ChangeCurrentMap("World");

    LOGE ("Sind raus");
    LibEric::GameObject_Interface *player = Player::Instance();
    player->Load("n/a");

    // Player::Instance()->GetPosition().GetX() + GetScreenWidth()/4, Player::Instance()->GetPosition().GetY() + GetScreenHeight()/4
    Vector2 d = {Player::Instance()->GetPosition().x + GetScreenWidth()/4, Player::Instance()->GetPosition().y + GetScreenHeight()/4 };
    Vector2 f = { 0.0f, 0.0f};
    _Camera.target = d;
    _Camera.offset = f;
    _Camera.rotation = 0.0f;
    _Camera.zoom = 4.0f;

    //LibEric::Dialog::Instance()->SetMSG("Hallo und Willkommen zu dieser Demo.\nSie dient nur zum Testen.\nWirklichen Spieleinhalt, wie z.B eine\nSuper tolle geschichte wirst du hier\nvergebens suchen\ndennoch viel Spaß beim spielen");
    return true;
}

bool Eric::PlayState::OnExit() {
    for (unsigned long i = 0; i < _Objects.size(); i++) {
        _Objects[i]->Clean();
    }
    return true;
}

std::string Eric::PlayState::GetStateID() const {
    return _PlayID;
}


