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

#ifndef __PRIVATESETTINGS
#define __PRIVATESETTINGS

#include <string>
#include <raylib.h>

namespace LibEric {

class PrivateSettings {
public:
    //! Zugriff auf das Objekt der Klasse
    /*! Damit immer auf die gleichen Daten zugegriffen wird, sorgen wir dafür, das es nur ein Klassenobjekt gibt. */
    static PrivateSettings* Instance();

     //! Einstellungen laden
    /*! Läd Einstellungen aus einer Datei. Im Benutzerverzeichnis oder unter /usr/share/erik.\n
        Ist im Homeverzeichnis keine Datei vorhanden, wird eine mit default-Werten erstellt.
        \todo Datei Speicherort angeben
    */
    void Load ();

    //! Einstellungen speichern
    /*! Speichert Einstellungen aus einer Datei. Im Benutzerverzeichnis $USERHOME/.erik/PrivateSettings.lua .\n
        Ist im Homeverzeichnis keine Datei vorhanden, wird eine mit default-Werten erstellt.
        \todo Datei Speicherort angeben
    */
    void Save ();

    //! Der Gamestate, der als erstes geladen werden soll
    /*! Gibt den Gamestate zurück, mit dem das Spiel startet.
     *
     * \return Die ID des Gamestates mit dem gestartet werden soll.
     *
     * \sa Erik_FW::Gamestate
    */
    std::string GetFirstState();

    //! Version in Menus Anzeigen
    /*! Gibt an, ob die Version des Frameworks in den Menüs eingeblendet wird
     *
     * \return true Wenn die Version angezeigt werden soll
     *         false Wenn die Version nicht angezeigt werden soll
    */
    bool GetShowVersion();

    //! Wie schnell die Animationen des Spielers ablaufen
    /*! Gibt an, wieviele Frames pro Sekunde abgespielt werden.
     *
     * \return Anzahl der Bilder pro Sekunde, bei Animationen.
    */
    int GetPlayerAnimationSpeed();

    //! Gibt die default Hintergrundfarbe zurück
    /*!
     * \return Die Hintergrundfarbe
    */
    Color GetBackgroundColor();

    //! Gibt das LogLevel zurück
    /*!
     * \return Das LogLevel
    */
    int GetLogLevel();


    PrivateSettings(const PrivateSettings&) = delete;
    PrivateSettings(PrivateSettings&&) = delete;
    PrivateSettings& operator=(const PrivateSettings&) = delete;
    PrivateSettings& operator=(PrivateSettings&&) = delete;

private:
    static PrivateSettings* _Instance;
    PrivateSettings();
    std::string _FirstState;
    bool _ShowVersion;
    int _PlayerAnimationSpeed;
    int _BackgroundColorRed;
    int _BackgroundColorGreen;
    int _BackgroundColorBlue;
    int _BackgroundColorAlpha;

    int _LogLevel;

};//class PrivateSettings
}; //namespace LibEric
#endif // __PRIVATESETTINGS
