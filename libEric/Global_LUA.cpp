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

#include "Game.hpp"
#include "GameStateMaschine.hpp"
#include "Global_LUA.hpp"
#include "MapManager.hpp"
#include "UserSettings.hpp"
#include "StoryNode.hpp"
#include "Dialog.hpp"

void LibEric::LuaSetup (sol::state *state){
    state->new_usertype<UserSettings>("UserSettings",
        "new", sol::no_constructor,
        "Instance", &UserSettings::Instance,
        "GetFullscreen", &UserSettings::GetFullScreen,
        "GetWindowWidth", &UserSettings::GetWindowWidth,
        "GetWindowHeight", &UserSettings::GetWindowHeight,
        "GetFSHeight", &UserSettings::GetFSHeight,
        "GetFSWidth", &UserSettings::GetFSWidth,
        "GetFPS", &UserSettings::GetFPS,
        "GetCollisionBoxes", &UserSettings::GetCollisionBoxes,
        "GetMusicVolume", &UserSettings::GetMusicVolume,
        "GetEffectVolume", &UserSettings::GetEffectVolume,
        "SetFullscreen", &UserSettings::SetFullscreen,
        "SetWindowWidth", &UserSettings::SetWindowWidth,
        "SetWindowHeight", &UserSettings::SetWindowHeight,
        "SetFPS", &UserSettings::SetFPS,
        "SetCollisionBoxes", &UserSettings::SetCollisionBoxes,
        "SetMusicVolume", &UserSettings::SetMusicVolume,
        "SetEffectVolume", &UserSettings::SetEffectVolume,
        "Save", &UserSettings::Save
        );

    state->new_usertype<Game>("Game",
        "new", sol::no_constructor,
        "Instance", &Game::Instance,
        "IsFS", &Game::IsFS,
        "ToggleFullscreen", &Game::ToggleFS,
        "Quit", &Game::Quit
        );



    state->new_usertype<GameStateMaschine>("StateMaschine",
        "new", sol::no_constructor,
        "Instance", &GameStateMaschine::Instance,
        "PushState", &GameStateMaschine::PushState,
        "ChangeState", &GameStateMaschine::ChangeState,
        "PopState", &GameStateMaschine::PopState
        );
    state->new_usertype<StoryNode>("StoryNode",
        "new", sol::no_constructor,
        "Instance", &StoryNode::Instance,
        "NewNode", &StoryNode::NewNode,
        "IsFinished", &StoryNode::NodeFinished
        );



    state->new_usertype<MapManager>("MapManager",
        "new", sol::no_constructor,
        "Instance", &MapManager::Instance,
        "ChanceToMap", &MapManager::ChangeCurrentMap
        );

    state->new_usertype<Dialog>("Dialog",
                                    "new", sol::no_constructor,
                                    "Instance", &Dialog::Instance,
                                    "Msg", &Dialog::SetMSG
    );

}
