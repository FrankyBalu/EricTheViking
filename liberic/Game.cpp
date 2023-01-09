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
#include "UserSettings.hpp"
#include "PrivateSettings.hpp"
#include "GameStateMaschine.hpp"
#include "Dialog.hpp"
#include <Config.hpp>
#include <raylib.h>
#include "Log.hpp"

//FIXME Vollbild muss noch verbessert werden
int TOFS = 0;

LibEric::Game* LibEric::Game::_Instance = nullptr;

LibEric::Game::Game() :
    _Running(false){
}



bool LibEric::Game::Init(const char* title) {
    //Als erstes Loggingsystem Initialisieren
    InitLog(plog::debug);
    SetTraceLogLevel(8);
    PLOGI << "Initialisiere Erik The Game";

    PLOGD << "\tLade LibEricsettings";
    PrivateSettings::Instance()->Load();
    PLOGD << "\t\tErfolgreich";
    PLOGD << "\tLade UserSettings";
    UserSettings::Instance()->Load();
    PLOGD << "\t\tErfolgreich";
    PLOGD << "\tSetze LogLevel auf: " << PrivateSettings::Instance()->GetLogLevel();
    SetTraceLogLevel(PrivateSettings::Instance()->GetLogLevel());
    PLOGD << "\t\tErfolgreich";

    int display = GetCurrentMonitor();
    //Fenster erstellen
    PLOGD << "\tErstelle Fenster";
    if (UserSettings::Instance()->GetFullScreen()){
        SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_FULLSCREEN_MODE);
        InitWindow(GetMonitorWidth(display), GetMonitorHeight(display), title);
        if (IsWindowReady()){
            PLOGD << "\t\tVollbild Erfolgreich";
        }
        else {
            PLOGD << "\t\tVollbild Fehlgeschlagen";
            return false;
        }
    }
    else{
        InitWindow(UserSettings::Instance()->GetWindowWidth(), UserSettings::Instance()->GetWindowHeight(), title);
        if (IsWindowReady()){
            PLOGD << "\t\tFenstermodus Erfolgreich";
        }
        else {
            PLOGD << "\t\tFenstermodus Fehlgeschlagen";
            return false;
        }
    }

    //Bilder pro Sekunde setzen
    PLOGD << "\tSetze Bildwiederholrate auf " << UserSettings::Instance()->GetFPS() << "fps";
    SetTargetFPS(UserSettings::Instance()->GetFPS());
    PLOGD << "\t\tErfolgreich";
    //Audiogerät initialisieren
    PLOGD << "\tInitialisiere Audiogerät";
    InitAudioDevice();
    if (IsAudioDeviceReady()){
        PLOGD << "\t\tErfolgreich";
    }
    else {
        PLOGD << "\t\tFehlgeschlagen";
    }

    // Maus sollte so aus dem sichtfeld verschwinden, keine ahnung ob es so geht
    //TODO Prüfen ob es so geht
    SetMousePosition(0, 0);

    //Muss noch in PrivateSettings überführt werden
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetExitKey(KEY_F4);

    //bis jetzt war alles gut, also läuft das spiel
    _Running = true;
    PLOGI << "\tErfolgreich Initialisier";
    return _Running;
}

void LibEric::Game::Render() {
    if (TOFS > 0){
        TOFS--;
        if (TOFS == 0)
            ToggleFullscreen();
    }
    PLOGV << "Starte Rendering";
    BeginDrawing();
    PLOGV << "\tClear Hintergrund";
    ClearBackground(PrivateSettings::Instance()->GetBackgroundColor());
    PLOGV << "\tRender GameState";
    GameStateMaschine::Instance()->Render();
    if (Dialog::Instance()->Exist()){
        PLOGV << "\tRender Dialog";
        Dialog::Instance()->DrawDialog();
    }
    PLOGV << "Rendern Beenden";
    EndDrawing();
}

void LibEric::Game::HandleEvents() {
    if (IsKeyPressed(KEY_F))
    {
        ToggleFullscreen();
    }
}

void LibEric::Game::Clean() {
    PLOGD << "Räume Spiel auf";
}

void LibEric::Game::Quit() {
    PLOGI << "Spiel wird beendet";
    _Running = false;
}


void LibEric::Game::Update() {
    PLOGV << "Update Mainloop";
    if (WindowShouldClose()){
        PLOGI << "Beende Spiel";
        _Running = false;
    }
    if (Dialog::Instance()->Exist()){
        PLOGV << "Update Dialog";
        Dialog::Instance()->Update();
    }
    else{
        PLOGV << "Update GameState";
        GameStateMaschine::Instance()->Update();
    }
}

LibEric::Game* LibEric::Game::Instance() {
    if (_Instance == nullptr) {
        _Instance = new Game();
    }
    return _Instance;
}


bool LibEric::Game::Running() {
    return _Running;
}

void LibEric::Game::ToggleFS() {
    PLOGD << "Wechsel Vollbild";
    int display = GetCurrentMonitor();
    if (!IsWindowFullscreen()){
        PLOGD << "\tvon Fenster (" << UserSettings::Instance()->GetWindowWidth() << "x" << UserSettings::Instance()->GetWindowHeight() << ") zu Vollbild(" << GetMonitorWidth(display) << "+" <<  GetMonitorHeight(display) << ")";
        SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
        TOFS = 3;
        UserSettings::Instance()->SetFullscreen(true);
    }
    else{
        PLOGD << "\tvon Vollbild zu Fenster";
        ToggleFullscreen();
        SetWindowSize(UserSettings::Instance()->GetWindowWidth(), UserSettings::Instance()->GetWindowHeight());
        UserSettings::Instance()->SetFullscreen(false);
    }
}

bool LibEric::Game::IsFS(){
    if (IsWindowFullscreen())
        return true;
    else
        return false;
}


