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

#include <libEric/Core/Lua.hpp>
#include <libEric/Core/LibEricApp.hpp>
#include <libEric/Core/GameStateMaschine.hpp>
#include <libEric/Core/UserSettings.hpp>
#include <libEric/Graphic/Dialog.hpp>


void LibEric::LuaSetup(sol::state *state) {
    state->new_usertype<UserSettings>("UserSettings",
                                      "new", sol::no_constructor,
                                      "Instance", &UserSettings::Instance,
                                      "GetFullscreen", &UserSettings::GetFullScreen,
                                      "GetWindowWidth", &UserSettings::GetWindowWidth,
                                      "GetWindowHeight", &UserSettings::GetWindowHeight,
                                      "GetFPS", &UserSettings::GetFPS,
                                      "GetCollisionBoxes", &UserSettings::GetCollisionBoxes,
                                      "GetMusicVolume", &UserSettings::GetMusicVolume,
                                      "GetEffectVolume", &UserSettings::GetEffectVolume,
                                      "SetFullscreen", &UserSettings::SetFullScreen,
                                      "SetWindowWidth", &UserSettings::SetWindowWidth,
                                      "SetWindowHeight", &UserSettings::SetWindowHeight,
                                      "SetFPS", &UserSettings::SetFPS,
                                      "SetCollisionBoxes", &UserSettings::SetCollisionBoxes,
                                      "SetMusicVolume", &UserSettings::SetMusicVolume,
                                      "SetEffectVolume", &UserSettings::SetEffectVolume/*,
                                      "Save", &UserSettings::Save*/
    );

    state->new_usertype<LibEricApp>("LibEricApp",
                                    "new", sol::no_constructor,
                                    "Instance", &LibEricApp::Instance,
                                    "GetWindowWidth", &LibEricApp::GetWindowWidth,
                                    "GetWindowHeight", &LibEricApp::GetWindowHeight,
                                    "Quit", &LibEricApp::Quit
    );


    state->new_usertype<GameStateMaschine>("StateMaschine",
                                           "new", sol::no_constructor,
                                           "Instance", &GameStateMaschine::Instance,
                                           "PushState", &GameStateMaschine::PushState,
                                           "ChangeState", &GameStateMaschine::ChangeState,
                                           "PopState", &GameStateMaschine::PopState
    );

    state->new_usertype<Dialog>("Dialog",
                                "new", sol::no_constructor,
                                "Instance", &Dialog::Instance,
                                "NewDialog", &Dialog::NewDialog,
                                "NewSelectDialog", &Dialog::NewSelectDialog,
                                "GetAnswer", &Dialog::GetAnswer
    );
}

