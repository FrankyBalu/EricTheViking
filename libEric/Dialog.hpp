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


#ifndef DIALOG_H
#define DIALOG_H

#include <raylib.h>
#include <string>
#include <vector>

namespace LibEric{

//! Zeigt ein Textbox/Dialogbox in der Text angezeigt wird
/*! Am besten ZeilenUmbrüche("\n") direkt in den Text setzen, da noch keine automatischen Zeilenumbrüche unterstützt wereden

 */
class Dialog
{
public:
    //! Gibt einen Zeiger auf die DialogInstance
    /*! Es gibt immer nur eine instance in einer Anwendung
    */
    static Dialog* Instance();

    //! SetMSG
    /*! Der Text wird festgelegt und die Box im anschluss angezeigt
    */
    void NewDialog (std::string msg);

    //! Blendet eine Auswahlmöglichkeit ein
    void NewSelectDialog(std::string msg, std::string option1, std::string option2, int default_answer);

    //! Gibt die zuletzt gewählte Option zurück
    int GetAnswer();

    //! Update
    /*! Es wird auf benutzer eingaben reagiert
    */
    void Update();

    //! Existiert eine Text zum Anzeigen?
    /*! true wenn ein Text vorhanden ist
    */
    bool Exist();

    //! Zeichnet den Dialog
    /*! Der Dialog wird angezeigt
    */
    void DrawDialog ();

private:

    static Dialog *_Instance; //!< Zeiger auf die Dialog-Instance
    bool _DialogAvaible; //!< Ist ein Dialog verfügbar
    bool _SelectDialogAvaible;
    std::string _Answer1;
    std::string _Answer2;
    int _SelectedAnswer;
    int _FinalAnswer;
    std::vector<std::string> _MSG;
    int _LinePos;
    int _FontSize;
    Dialog();
};
};//namespace LibEric
#endif // DIALOG_H
