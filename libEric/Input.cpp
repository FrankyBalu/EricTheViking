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

#include <libEric/Input.hpp>
#include <libEric/Game.hpp>
#include <raylib.h>


int Button_Up_Key = KEY_W;
int Button_Right_Key = KEY_D;
int Button_Down_Key = KEY_S;
int Button_Left_Key = KEY_A;
int Button_A_Key = KEY_DOWN;
int Button_B_Key = KEY_RIGHT;
int Button_X_Key = KEY_LEFT;
int Button_Y_Key = KEY_UP;
int Button_Menu_Key = KEY_E;
int Button_Back_Key = KEY_Q;
int Button_Home_Key = KEY_X;
int Button_Left_Stick_Key = KEY_Z;
int Button_Right_Stick_Key = KEY_H;
int Button_Left_Trigger_1_Key = KEY_U;
int Button_Left_Trigger_2_Key = KEY_J;
int Button_Right_Trigger_1_Key = KEY_I;
int Button_Right_Trigger_2_Key = KEY_K;


bool LibEric::Button_Up() {
    bool ret = false;
    if (IsGamepadButtonPressed(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_LEFT_FACE_UP)) {
        ret = true;
    }
    if (IsKeyPressed(Button_Up_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_Right() {
    bool ret = false;
    if (IsGamepadButtonPressed(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) {
        ret = true;
    }
    if (IsKeyPressed(Button_Right_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_Down() {
    bool ret = false;
    if (IsGamepadButtonPressed(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_LEFT_FACE_DOWN)) {
        ret = true;
    }
    if (IsKeyPressed(Button_Down_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_Left() {
    bool ret = false;
    if (IsGamepadButtonPressed(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_LEFT_FACE_LEFT)) {
        ret = true;
    }
    if (IsKeyPressed(Button_Left_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_A() {
    bool ret = false;
    if (IsGamepadButtonPressed(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
        ret = true;
    }
    if (IsKeyPressed(Button_A_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_B() {
    bool ret = false;
    if (IsGamepadButtonPressed(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) {
        ret = true;
    }
    if (IsKeyPressed(Button_B_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_X() {
    bool ret = false;
    if (IsGamepadButtonPressed(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_RIGHT_FACE_LEFT)) {
        ret = true;
    }
    if (IsKeyPressed(Button_X_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_Y() {
    bool ret = false;
    if (IsGamepadButtonPressed(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_RIGHT_FACE_UP)) {
        ret = true;
    }
    if (IsKeyPressed(Button_Y_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_Menu() {
    bool ret = false;
    if (IsGamepadButtonPressed(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_MIDDLE_RIGHT)) {
        ret = true;
    }
    if (IsKeyPressed(Button_Menu_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_Back() {
    bool ret = false;
    if (IsGamepadButtonPressed(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_MIDDLE_LEFT)) {
        ret = true;
    }
    if (IsKeyPressed(Button_Back_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_Home() {
    bool ret = false;
    if (IsGamepadButtonPressed(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_MIDDLE)) {
        ret = true;
    }
    if (IsKeyPressed(Button_Home_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_Left_Stick() {
    bool ret = false;
    if (IsGamepadButtonPressed(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_LEFT_THUMB)) {
        ret = true;
    }
    if (IsKeyPressed(Button_Left_Stick_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_Right_Stick() {
    bool ret = false;
    if (IsGamepadButtonPressed(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_RIGHT_THUMB)) {
        ret = true;
    }
    if (IsKeyPressed(Button_Right_Stick_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_Left_Trigger_1() {
    bool ret = false;
    if (IsGamepadButtonPressed(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_LEFT_TRIGGER_1)) {
        ret = true;
    }
    if (IsKeyPressed(Button_Left_Trigger_1_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_Right_Trigger_1() {
    bool ret = false;
    if (IsGamepadButtonPressed(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_RIGHT_TRIGGER_1)) {
        ret = true;
    }
    if (IsKeyPressed(Button_Right_Trigger_1_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_Left_Trigger_2() {
    bool ret = false;
    if (IsGamepadButtonPressed(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_LEFT_TRIGGER_2)) {
        ret = true;
    }
    if (IsKeyPressed(Button_Left_Trigger_2_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_Right_Trigger_2() {
    bool ret = false;
    if (IsGamepadButtonPressed(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_RIGHT_TRIGGER_2)) {
        ret = true;
    }
    if (IsKeyPressed(Button_Right_Trigger_2_Key)) {
        ret = true;
    }
    return ret;
}


bool LibEric::Button_Up_Down() {
    bool ret = false;
    if (IsGamepadButtonDown(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_LEFT_FACE_UP)) {
        ret = true;
    }
    if (IsKeyDown(Button_Up_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_Right_Down() {
    bool ret = false;
    if (IsGamepadButtonDown(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) {
        ret = true;
    }
    if (IsKeyDown(Button_Right_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_Down_Down() {
    bool ret = false;
    if (IsGamepadButtonDown(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_LEFT_FACE_DOWN)) {
        ret = true;
    }
    if (IsKeyDown(Button_Down_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_Left_Down() {
    bool ret = false;
    if (IsGamepadButtonDown(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_LEFT_FACE_LEFT)) {
        ret = true;
    }
    if (IsKeyDown(Button_Left_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_A_Down() {
    bool ret = false;
    if (IsGamepadButtonDown(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
        ret = true;
    }
    if (IsKeyDown(Button_A_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_B_Down() {
    bool ret = false;
    if (IsGamepadButtonDown(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) {
        ret = true;
    }
    if (IsKeyDown(Button_B_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_X_Down() {
    bool ret = false;
    if (IsGamepadButtonDown(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_RIGHT_FACE_LEFT)) {
        ret = true;
    }
    if (IsKeyDown(Button_X_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_Y_Down() {
    bool ret = false;
    if (IsGamepadButtonDown(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_RIGHT_FACE_UP)) {
        ret = true;
    }
    if (IsKeyDown(Button_Y_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_Menu_Down() {
    bool ret = false;
    if (IsGamepadButtonDown(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_MIDDLE_RIGHT)) {
        ret = true;
    }
    if (IsKeyDown(Button_Menu_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_Back_Down() {
    bool ret = false;
    if (IsGamepadButtonDown(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_MIDDLE_LEFT)) {
        ret = true;
    }
    if (IsKeyDown(Button_Back_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_Home_Down() {
    bool ret = false;
    if (IsGamepadButtonDown(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_MIDDLE)) {
        ret = true;
    }
    if (IsKeyDown(Button_Home_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_Left_Stick_Down() {
    bool ret = false;
    if (IsGamepadButtonDown(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_LEFT_THUMB)) {
        ret = true;
    }
    if (IsKeyDown(Button_Left_Stick_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_Right_Stick_Down() {
    bool ret = false;
    if (IsGamepadButtonDown(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_RIGHT_THUMB)) {
        ret = true;
    }
    if (IsKeyDown(Button_Right_Stick_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_Left_Trigger_1_Down() {
    bool ret = false;
    if (IsGamepadButtonDown(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_LEFT_TRIGGER_1)) {
        ret = true;
    }
    if (IsKeyDown(Button_Left_Trigger_1_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_Right_Trigger_1_Down() {
    bool ret = false;
    if (IsGamepadButtonDown(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_RIGHT_TRIGGER_1)) {
        ret = true;
    }
    if (IsKeyDown(Button_Right_Trigger_1_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_Left_Trigger_2_Down() {
    bool ret = false;
    if (IsGamepadButtonDown(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_LEFT_TRIGGER_2)) {
        ret = true;
    }
    if (IsKeyDown(Button_Left_Trigger_2_Key)) {
        ret = true;
    }
    return ret;
}

bool LibEric::Button_Right_Trigger_2_Down() {
    bool ret = false;
    if (IsGamepadButtonDown(Game::Instance()->GetGamepad(), GAMEPAD_BUTTON_RIGHT_TRIGGER_2)) {
        ret = true;
    }
    if (IsKeyDown(Button_Right_Trigger_2_Key)) {
        ret = true;
    }
    return ret;
}

void Set_Button_Up_Key(int scancode);

void Set_Button_Right_Key(int scancode);

void Set_Button_Down_Key(int scancode);

void Set_Button_Left_Key(int scancode);

void Set_Button_A_Key(int scancode);

void Set_Button_B_Key(int scancode);

void Set_Button_X_Key(int scancode);

void Set_Button_Y_Key(int scancode);

void Set_Button_Menu_Key(int scancode);

void Set_Button_Back_Key(int scancode);

void Set_Button_Home_Key(int scancode);

void Set_Button_Left_Stick_Key(int scancode);

void Set_Button_Right_Stick_Key(int scancode);

void Set_Button_Left_Trigger_1_Key(int scancode);

void Set_Button_Left_Trigger_2_Key(int scancode);

void Set_Button_Right_Trigger_1_Key(int scancode);

void Set_Button_Right_Trigger_2_Key(int scancode);