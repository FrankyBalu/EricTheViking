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

#ifndef ERIC_INPUT_HPP
#define ERIC_INPUT_HPP

#include <raylib.h>

namespace LibEric {


    bool Button_Up ();
    bool Button_Right ();
    bool Button_Down ();
    bool Button_Left ();
    bool Button_A ();
    bool Button_B ();
    bool Button_X ();
    bool Button_Y ();
    bool Button_Menu ();
    bool Button_Back ();
    bool Button_Home ();
    bool Button_Left_Stick ();
    bool Button_Right_Stick ();
    bool Button_Left_Trigger_1();
    bool Button_Right_Trigger_1();
    bool Button_Left_Trigger_2();
    bool Button_Right_Trigger_2();

    bool Button_Up_Down ();
    bool Button_Right_Down ();
    bool Button_Down_Down ();
    bool Button_Left_Down ();
    bool Button_A_Down ();
    bool Button_B_Down ();
    bool Button_X_Down ();
    bool Button_Y_Down ();
    bool Button_Menu_Down ();
    bool Button_Back_Down ();
    bool Button_Home_Down ();
    bool Button_Left_Stick_Down ();
    bool Button_Right_Stick_Down ();
    bool Button_Left_Trigger_1_Down();
    bool Button_Right_Trigger_1_Down();
    bool Button_Left_Trigger_2_Down();
    bool Button_Right_Trigger_2_Down();



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

} // LibEric

#endif //ERIC_INPUT_HPP
