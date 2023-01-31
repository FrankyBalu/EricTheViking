/*
 * LibEric
 * Copyright (C) 2022  Frank Kartheuser <frank.kartheuser1988@gmail.com>
 * Copyright (C) 2023  Frank Kartheuser <frank.kartheuser1988@gmail.com>
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


#include <libEric/GameStateMaschine.hpp>
#include <libEric/GameStateFactory.hpp>
#include <libEric/Log.hpp>

LibEric::GameStateMaschine *LibEric::GameStateMaschine::_Instance = nullptr;

LibEric::GameStateMaschine *LibEric::GameStateMaschine::Instance() {
    if (_Instance == nullptr)
        _Instance = new GameStateMaschine();
    return _Instance;
}

bool LibEric::GameStateMaschine::PushState(std::string stateID, std::string file) {
    GameState *newState = nullptr;
    newState = GameStateFactory::Instance()->Create(stateID);
    if (newState == nullptr) {
        return false;
    }
    _GameStates.push_back(newState);
    _GameStates.back()->OnEnter(file);
    LOGD ("Neuen GameState <", _GameStates.back()->GetStateID(), "> zur Statemaschine hinzugefügt");
    return true;
}

bool LibEric::GameStateMaschine::PopState() {
    if (_GameStates.empty()) {
        LOGE("Kann keinen Gamestate entfernen: Keine States vorhanden");
        return false;
    }
    std::string currentState = _GameStates.back()->GetStateID();
    if (_GameStates.back()->OnExit()) {
        _GameStates.pop_back();
        LOGD("Gamestate <", currentState, "> beendet");
        LOGD("Zu Gamestate <", _GameStates.back()->GetStateID(), "> gewechselt");
        return true;
    } else {
        _GameStates.pop_back();
        LOGD("Fehler beim beenden von Gamestate <", currentState, ">");
        LOGD("Zu Gamestate <", _GameStates.back()->GetStateID(), "> gewechselt");
        return true;
    }
}

bool LibEric::GameStateMaschine::ChangeState(std::string stateID, std::string file) {
    std::string currentState;
    GameState *newSate = nullptr;
    newSate = GameStateFactory::Instance()->Create(stateID);
    if (newSate == nullptr) {
        return false;
    }
    if (_GameStates.empty()) {
        _GameStates.push_back(newSate);
        _GameStates.back()->OnEnter(file);
        LOGD("Zu Gamestate <", _GameStates.back()->GetStateID(), "> gewechselt");
        return true;
    } else {
        currentState = _GameStates.back()->GetStateID();
        _GameStates.push_back(newSate);
        _GameStates.back()->OnEnter(file);
        LOGD("Von Gamestate <", currentState, "> zu <", _GameStates.back()->GetStateID(), "> gewechselt");
        return true;
    }
}

std::string LibEric::GameStateMaschine::GetCurrentStateID() {
    return _GameStates.back()->GetStateID();
}

void LibEric::GameStateMaschine::Render() {
    if (_GameStates.empty()) {
        LOGE("Kann Gamestate nicht Rendern: Keine Gamestates vorhanden");
        return;
    }
    _GameStates.back()->Render();
}

void LibEric::GameStateMaschine::Update() {
    if (_GameStates.empty()) {
        LOGE("Kann Gamestate nicht Updaten: Keine Gamestates vorhanden");
        return;
    }
    _GameStates.back()->Update();
}

void LibEric::GameStateMaschine::HandleEvents() {
    if (_GameStates.empty()) {
        LOGE("Kann Gamestate Events nicht Updaten: Keine Gamestates vorhanden");
        return;
    }
    _GameStates.back()->HandleEvents();
}

void LibEric::GameStateMaschine::Resize() {
    for (auto itr = _GameStates.cbegin(); itr != _GameStates.cend(); itr++) {
        (*itr)->Resize();
    }
}