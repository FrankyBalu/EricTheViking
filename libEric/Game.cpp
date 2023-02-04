//
// Created by frank on 27.01.23.
//

#include <libEric/Game.hpp>
#include <libEric/Log.hpp>
#include <Config.hpp>
#include <libEric/UserSettings.hpp>
#include <libEric/LibEricSettings.hpp>
#include <libEric/GameStateMaschine.hpp>
#include <libEric/Dialog.hpp>
#include <libEric/Input.hpp>
#include <raylib.h>

#define RAYLIB_PHYSFS_IMPLEMENTATION

#include "../Extra/raylib-physfs.h"

LibEric::Game *LibEric::Game::_Instance = nullptr;

LibEric::Game *LibEric::Game::Instance() {
    if (_Instance == nullptr)
        _Instance = new Game();
    return _Instance;
}

//FIXME _FONTSIZE muss noch in die config datei
LibEric::Game::Game() : _IsReady(false), _Running(false), _AppName(), _AppDir(), _FontSize(25), UseGamepad(0) {
}

bool LibEric::Game::Init(const std::string &appName) {
    _AppName = appName;
#ifdef __linux__
    _AppDir = std::string(INSTALL_PREFIX) + std::string("/share/") + std::string(_AppName);
#else
    _AppDir = "data\\";
#endif

    //Dies dient nur die Meldungen von Raylib zu unterdrücken, auser Fehler
    SetTraceLogLevel(4);

#ifdef __linux__
    InitPhysFSEx(_AppDir.c_str(), "system");
    MountPhysFS(GetPerfDirectory(" ", _AppName.c_str()), "user");
#else
    InitPhysFSEx(_AppDir.c_str(), "system");
    MountPhysFS(GetPerfDirectory(" ", _AppName.c_str()), "user");
#endif
    if (!LibEricSettings::Instance()->Load()) {
        return false;
    }
    if (!UserSettings::Instance()->Load()) {
        return false;
    }
    Log::Instance()->SetLogLevel(LibEricSettings::Instance()->GetLogLevel());
    Log::Instance()->SetLogLevel(LibEric::LOG_DEBUG);
    SetTargetFPS(UserSettings::Instance()->GetFPS());




    //Configflags für Raylib
    if (UserSettings::Instance()->GetFullScreen() && LibEricSettings::Instance()->GetMSAA()) {
        SetConfigFlags(FLAG_VSYNC_HINT | FLAG_FULLSCREEN_MODE |
                       FLAG_MSAA_4X_HINT);
    } else if (UserSettings::Instance()->GetFullScreen()) {
        SetConfigFlags(FLAG_VSYNC_HINT | FLAG_FULLSCREEN_MODE);
    } else if (LibEricSettings::Instance()->GetMSAA()) {
        SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    } else {
        SetConfigFlags(FLAG_VSYNC_HINT);
    }

    if (UserSettings::Instance()->GetFullScreen()) {
        int display = GetCurrentMonitor();
        InitWindow(GetMonitorWidth(display), GetMonitorHeight(display), _AppName.c_str());
    } else {
        InitWindow(UserSettings::Instance()->GetWindowWidth(), UserSettings::Instance()->GetWindowHeight(),
                   appName.c_str());
    }
    if (!IsWindowReady()) {
        return false;
    }

    _Font = LoadFontFromPhysFS(std::string(std::string("/system/") + LibEricSettings::Instance()->GetFont()).c_str(),
                               _FontSize, NULL, 0);

    InitAudioDevice();

    SetExitKey(LibEricSettings::Instance()->GetExitKey());
    _IsReady = true;
    _Running = true;
    return true;
}

std::string LibEric::Game::GetUserDir() {
    return GetPerfDirectory(" ", _AppName.c_str());
}

void LibEric::Game::Run() {
    while (!WindowShouldClose() && _Running) {
        HandleEvents();
        Update();
        Render();
    }
}

bool LibEric::Game::IsReady() {
    return _IsReady;
}

void LibEric::Game::Render() {
    BeginDrawing();
    ClearBackground(Color{(unsigned char) LibEricSettings::Instance()->GetBGCRed(),
                          (unsigned char) LibEricSettings::Instance()->GetBGCGreen(),
                          (unsigned char) LibEricSettings::Instance()->GetBGCBlue(),
                          (unsigned char) LibEricSettings::Instance()->GetBGCAlpha()});
    GameStateMaschine::Instance()->Render();
    if (Dialog::Instance()->Exist()) {
        Dialog::Instance()->DrawDialog();
    }

    EndDrawing();
}

void LibEric::Game::Update() {
    if (!Dialog::Instance()->Exist()) {
        GameStateMaschine::Instance()->Update();
    } else {
        Dialog::Instance()->Update();
    }

}

void LibEric::Game::HandleEvents() {
    if (IsKeyPressed(KEY_F)) {
        ToggleFullscreen();
        Resize();
    }
    if (!Dialog::Instance()->Exist()) {
        GameStateMaschine::Instance()->HandleEvents();
    }
}

void LibEric::Game::Quit() {
    _Running = false;
}

int LibEric::Game::GetWindowWidth() {
    int width;
    if (IsWindowFullscreen()) {
        width = GetMonitorWidth(GetCurrentMonitor());
    } else {
        width = GetScreenWidth();
    }
    return width;
}

int LibEric::Game::GetWindowHeight() {
    int height;
    if (IsWindowFullscreen()) {
        height = GetMonitorHeight(GetCurrentMonitor());
    } else {
        height = GetScreenHeight();
    }
    return height;
}

void LibEric::Game::Resize() {
    GameStateMaschine::Instance()->Resize();
}

Font LibEric::Game::GetDefaultFont() {
    return _Font;
}