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

#include <libEric/libEric_API.hpp>

namespace LibEric {

    extern "C" {

    LIBERIC_API class UserSettings {
    public:
        //!Gibt einen Zeiger auf die Instance der Klasse
        static UserSettings *Instance();

        /* Es wird erst versucht eine settings-Datei unter $HOME/.local/share/{anwendungsname}/ zu finden \n
         * ist dort keine, wird es unter /usr/share/{anwendungsname]/ versucht \n
         * @return true wenn eine Datei gefunden wurde und geladen werden konnte, sonst false
         */
        bool Load();

        //! Gibt die Musiklautstärke zurück 0.0 = Mute 1.0 = das Lauteste
        [[nodiscard]] float GetMusicVolume() const;

        //! Gibt die Effektlautstärke zurück 0.0 = Mute 1.0 = das Lauteste
        [[nodiscard]] float GetEffectVolume() const;

        //!gibt an, ob in Vollbild gestartet werden soll
        [[nodiscard]] bool GetFullScreen() const;

        //! Gibt an, ob die KollisionsBoxen Angezeigt werden sollen
        [[nodiscard]] bool GetCollisionBoxes() const;

        //! Gibt die Fensterbreite an
        [[nodiscard]] int GetWindowWidth() const;

        //! Gibt die Fensterhöhe an
        [[nodiscard]] int GetWindowHeight() const;

        //! Gibt an, auf wie viel FPS im Vollbild gesetzt werden soll
        [[nodiscard]] int GetFPS() const;

        //! Setzt die Musiklautstärke
        void SetMusicVolume(float vol);

        //! Setzt die Effektlautstärke
        void SetEffectVolume(float vol);

        //! Setzt das zukünftig in Vollbildgestartet werden soll
        void SetFullScreen(bool val);

        //! Setzt ob Killionsboxen angezeigt werden sollen oder nicht
        void SetCollisionBoxes(bool val);

        //! Setzt die Fensterbreite
        void SetWindowWidth(int width);

        //! Setzt die Fensterhöhe
        void SetWindowHeight(int height);

        //! Setzt die FPS
        void SetFPS(int fps);

        //! Speichert die aktuellen Einstellungen in die Settingsdatei
        void Save() const;

        UserSettings(const UserSettings &) = delete;

        UserSettings(UserSettings &&) = delete;

        UserSettings &operator=(const UserSettings &) = delete;

        UserSettings &operator=(UserSettings &&) = delete;

    private:
        UserSettings();

        static UserSettings *pInstance;

        float pMusicVolume;    /*!< Musiklautstärke */
        float pEffectVolume;   /*!< Effektlautstärke */
        bool pFullscreen;      /*!< Vollbild Variable */
        bool pCollisionBoxes;  /*!< Kollisionsboxen Variable */
        int pWindowWidth;    /*!< Fensterbreite */
        int pWindowHeight;   /*!< Fensterhöhe */
        int pFPS;              /*!< Bilder pro Sekunde */
    };

    }//extern "C"

} // LibEric

#endif //ERIC_USERSETTINGS_HPP
