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


#ifndef ERIC_USERSETTINGS_HPP
#define ERIC_USERSETTINGS_HPP

namespace LibEric {

    class UserSettings {
    public:
        //!Gibt einen Zeiger auf die Instance der Klasse
        static UserSettings *Instance();

        /* Es wird erst versucht eine settings-Datei unter $HOME/.local/share/{anwendungsname}/ zu finden \n
         * ist dort keine, wird es unter /usr/share/{anwendungsname]/ versucht \n
         * @return true wenn eine Datei gefunden wurde und geladen werden konnte, sonst false
         */
        bool Load();

        float GetMusicVolume();

        float GetEffectVolume();

        bool GetFullScreen();

        bool GetCollisionBoxes();

        int GetWindowWidth();

        int GetWindowHeight();

        int GetFPS();

        void SetMusicVolume(float vol);

        void SetEffectVolume(float vol);

        void SetFullScreen(bool val);

        void SetCollisionBoxes(bool val);

        void SetWindowWidth(int width);

        void SetWindowHeight(int height);

        void SetFPS(int fps);

        UserSettings(const UserSettings &) = delete;

        UserSettings(UserSettings &&) = delete;

        UserSettings &operator=(const UserSettings &) = delete;

        UserSettings &operator=(UserSettings &&) = delete;

    private:
        UserSettings();

        static UserSettings *_Instance;

        float _MusicVolume;    /*!< Musiklautstärke */
        float _EffectVolume;   /*!< Effektlautstärke */
        bool _Fullscreen;      /*!< Vollbild Variable */
        bool _CollisionBoxes;  /*!< Kollisionsboxen Variable */
        int _WindowWidth;    /*!< Fensterbreite */
        int _WindowHeight;   /*!< Fensterhöhe */
        int _FPS;              /*!< Bilder pro Sekunde */
    };

} // LibEric

#endif //ERIC_USERSETTINGS_HPP
