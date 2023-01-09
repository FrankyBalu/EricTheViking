/*
 * libEric
 * Copyright (C) 2022   Frank Kartheuser <frank.kartheuser1988@gmail.com>
 * Copyright (C) 2023   Frank Kartheuser <frank.kartheuser1988@gmail.com>
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


#include "GameStateMaschine.hpp"
#include "GameStateFactory.hpp"
#include "Log.hpp"


LibEric::GameStateMaschine* LibEric::GameStateMaschine::_Instance = 0;

LibEric::GameStateMaschine * LibEric::GameStateMaschine::Instance(){
    if (_Instance == nullptr){
        _Instance = new GameStateMaschine();
    }
    return _Instance;
}



void LibEric::GameStateMaschine::PushState(std::string stateID, std::string file) {
    //Der neue Gamestate
    GameState *state = nullptr;
    //Testen welcher State Geladen werden soll
    state = GameStateFactory::Instance()->Create(stateID);

    if (state == nullptr){
        PLOGE << "Gamestate <" << stateID << "> konnte nicht erstellt werden";
        return;
    }
    _GameStates.push_back(state);
    _GameStates.back()->OnEnter(file);
    PLOGI << "Push neuen Gamestate: " << state->GetStateID();
}

void LibEric::GameStateMaschine::PopState() {
    if (!_GameStates.empty()) {
        PLOGI << "Entferne _GameStates: " << _GameStates.back()->GetStateID();
        if(_GameStates.back()->OnExit()) {
            _GameStates.pop_back();
            PLOGI << "\tZurück zu GameState: " << _GameStates.back()->GetStateID();
            return;
        }
        else {
            PLOGE << "\tKann GameStates nicht beenden";
        }
    }
    else{
        PLOGE << "\tKann GameState nicht wechseln: Keine GameState verfügbar";
    }
}

void LibEric::GameStateMaschine::ChangeState(std::string stateID, std::string file) {
    //Der neue Gamestate
    GameState *state;
    std::string oldID;

    state = GameStateFactory::Instance()->Create(stateID);

    if (state == nullptr){
        PLOGE << "Gamestate <" << stateID << "> konnte nicht erstellt werden";
        return;
    }

   if (!_GameStates.empty()) {
        if (_GameStates.back()->GetStateID() == state->GetStateID()) {
            return; // da der State schon aktiv ist, müssen wir nix wechseln
        }
        oldID = _GameStates.back()->GetStateID();
        if (_GameStates.back()->OnExit()) {
            _GameStates.pop_back();
        }
        else {

        }
     }
    _GameStates.push_back(state);
    _GameStates.back()->OnEnter(file);
    PLOGI << "Wechsel von GameState: " << oldID << " Zu GameState: "   << _GameStates.back()->GetStateID();
}

void LibEric::GameStateMaschine::Update() {
    if (!_GameStates.empty()) {
        _GameStates.back()->Update();
        return;
    }
    PLOGE << "Kein GameState geladen";
}

void LibEric::GameStateMaschine::Render() {
    if (!_GameStates.empty()) {
        _GameStates.back()->Render();
        return;
    }
    PLOGE << "Kein GameState geladen";
}
