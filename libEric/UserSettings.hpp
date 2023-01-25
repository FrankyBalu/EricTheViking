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

#ifndef __USERSETTINGS
#define __USERSETTINGS

namespace LibEric {

//!  Einstellungen mit Benutzer zugriff.
/*!
  Diese Einstellungen können vom Benutzer zur Laufzeit verändert werden.
*/
class UserSettings {
public:
    //! Zugriff auf das Objekt der Klasse
    /*! Damit immer auf die gleichen Daten zugegriffen wird, sorgen wir dafür, das es nur ein Klassenobjekt gibt. */
    static UserSettings* Instance();

    //! Einstellungen laden
    /*! Läd Einstellungen aus einer Datei. Im Benutzerverzeichnis oder unter /usr/share/erik.\n
        Ist im Homeverzeichnis keine Datei vorhanden, wird eine mit default-Werten erstellt.
        \todo Datei Speicherort angeben
    */
    bool Load ();

    //! Einstellungen speichern
    /*! Speichert Einstellungen aus einer Datei. Im Benutzerverzeichnis $USERHOME/.erik/Settings.lua .\n
        Ist im Homeverzeichnis keine Datei vorhanden, wird eine mit default-Werten erstellt.
        \todo Datei Speicherort angeben
    */
    void Save ();

    //! Vollbildmodus setzen
    /*! Setzt den Vollbildmodus, aber nur in den Einstellungen.
     *  Der Modus wird sofort gewechselt,
     *
     * \param fullscreen true, für Vollbild\n
     *                   false, für Fenstermodus
     *
     * \sa Erik_FW::Game::ToggleFS
    */
    void SetFullscreen(bool fullscreen);

    //! Fensterbreite setzen
    /*! Setzt die Fensterbreite, die neue Breite wird sofort übernommen.
     *
     * \param width Die neue Fensterbreite in Pixel
     *
     * \sa Erik_FW::Game::ChangeWindowSize
    */
    void SetWindowWidth(int width);

    //! Fensterhöhe setzen
    /*! Setzt die Fensterhöhe, die neue Höhe wird sofot übernommen.
     *
     * \param height Die neue Fensterhöhe in Pixel
     *
     * \sa Erik_FW::Game::ChangeWindowSize
    */
    void SetWindowHeight(int height);

    //! Setzt wieviele Bilder in der Sekunde angezeigt werden sollem.
    /*! Die einstellung wird direkt vom Framework übernommen
     *
     * \param fps Anzahl der Einzelbilder pro Sekunde
     *
    */
    void SetFPS(int fps);

    //! Hiermit wird gesetzt, ob die CollisionBoxes angezeigt werden
    /*! Wenn die Boxen angezeigt werden sollen, ist von jedem Object\n
     *  die Fläche farblich makiert, mit der man zusammenstöst und\n
     *  welche Flächen für bestimmte Aktionen wichtig sind.\n
     *  Nur für Debugzwecke wirklich nützlich
     *
     * \param boxes true, Die Flächen werden Angezeigt
     *              false, Die Flächen werden nicht Angezeigt
     *
    */
    void SetCollisionBoxes(bool boxes);

    //! Setzt die Lautstärke der Musik im Spiel und in den Menüs
    /*! Die lautstärke wird in einem Bereich von 0.0 (Stumm) bis 1.0 (lauteste)\n
     *  angegeben. Die Änderung wird sofort übernommen.
     *
     * \param volume Die neue Lautstärke
     *
    */
    void SetMusicVolume(float volume);

    //! Setzt die Lautstärke der Effekte im Spiel und in den Menüs
    /*! Die lautstärke wird in einem Bereich von 0.0 (Stumm) bis 1.0 (lauteste)\n
     *  angegeben. Die Änderung wird sofort übernommen.
     *
     * \param volume Die neue Lautstärke
     *
    */
    void SetEffectVolume(float volume);

    //! Vollbildmodus abfragen
    /*! Dient zum abfragen des Vollbildmoduses.
     *
     * \return true: Spiel läuft im Vollbildmodus.\n
     *         false: Spiel läuft im Fenstermodus.
     *
     * \sa Erik_FW::Settings::SetFullscreen
    */
    bool GetFullScreen();

    //! Fensterbreite abfragen
    /*! Gibt zurück wie breit das Fenster ist.
     *
     * \return Die aktuelle Fensterbreite
     *
     * \sa Erik_FW::Settings::SetWindowWidth
     * \sa Erik_FW::Settings::SetWindowHeight
     * \sa Erik_FW::Settings::GetWindowHeight
     *
    */
    int GetWindowWidth();

    //! Fensterhöhe abfragen
    /*! Gibt zurück wie hoch das Fenster ist.
     *
     * \return Die aktuelle Fensterhöhe
     *
     * \sa Erik_FW::Settings::SetWindowWidth
     * \sa Erik_FW::Settings::SetWindowHeight
     * \sa Erik_FW::Settings::GetWindowWidth
     *
    */
    int GetWindowHeight();

    //! FPS abfragen
    /*! Gibt die FPS zurück
     *
     * \return Die aktuellen Bilder je Sekunde
     *
     * \sa Erik_FW::Settings::SetFPS
     *
    */
    int GetFPS();

    //! Hiermit wird abgefragt, ob die CollisionBoxes angezeigt werden
    /*! Wenn die Boxen angezeigt werden sollen, ist von jedem Object\n
     *  die Fläche farblich makiert, mit der man zusammenstöst und\n
     *  welche Flächen für bestimmte Aktionen wichtig sind.\n
     *  Nur für Debugzwecke wirklich nützlich
     *
     * \return true: Boxen werden angezeigt\n
     *         false: Boxen werden nicht angezeigt
     *
     * \sa Erik_FW::Settings::SetCollisionBoxes
    */
    bool GetCollisionBoxes();

    //! Gibt die Aktuelle Musiklautstärke zurück
    /*! Die lautstärke wird in einem Bereich von 0.0 (Stumm) bis 1.0 (lauteste)\n
     *  angegeben.
     *
     * \return Die aktuelle Lautstärke
     *
     * \sa Erik_FW::Settings::SetMusicVolume
    */
    float GetMusicVolume();

    //! Gibt die Aktuelle Effektlautstärke zurück
    /*! Die lautstärke wird in einem Bereich von 0.0 (Stumm) bis 1.0 (lauteste)\n
     *  angegeben.
     *
     * \return Die aktuelle Effektstärke
     *
     * \sa Erik_FW::Settings::SetEffectVolume
    */
    float GetEffectVolume();

    int GetFSHeight();
    int GetFSWidth();


    UserSettings(const UserSettings&) = delete;
    UserSettings(UserSettings&&) = delete;
    UserSettings& operator=(const UserSettings&) = delete;
    UserSettings& operator=(UserSettings&&) = delete;
private:


    UserSettings();

    static UserSettings* _Instance; /*!< Zeiger auf die Instance der Klasse */
    
    bool _Fullscreen;      /*!< Vollbild Variable */
    bool _CollisionBoxes;  /*!< Kollisionsboxen Variable */
    int _WindowedWidth;    /*!< Fensterbreite */
    int _WindowedHeight;   /*!< Fensterhöhe */
    int _FPS;              /*!< Bilder pro Sekunde */
    float _MusicVolume;    /*!< Musiklautstärke */
    float _EffectVolume;   /*!< Effektlautstärke */
}; //class UserSettings
}; //namespace LibEric
#endif // __UserSettings
