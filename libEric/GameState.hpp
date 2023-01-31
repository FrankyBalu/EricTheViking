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

#ifndef ERIC_GAMESTATE_HPP
#define ERIC_GAMESTATE_HPP

#include <string>

namespace LibEric {

    class GameState {
    public:
        //! Benutzer eingaben verarbeiten
        /*! Diese Funktion dient dazu die eingaben, die vom Benutzer kommen zu verarbeiten
        */
        virtual void HandleEvents() = 0;

        //! Logik updaten
        /*! Hier wird die ganze Logik berechnet
        */
        virtual void Update() = 0;

        //! Rendern
        /*! Hier wird alles auf den Bildschirm gezeichnet
        */
        virtual void Render() = 0;

        //! Init den State
        /*! Der Gamestate wird Initialisiert, es werden alle benötigten Daten geladen,\n
         *  so das die Logik des States arbeiten kann.
         *
         * \param scriptFile sollte der GameState über ein lua-Script gesteuert werden, kann dieses hier angegeben werden.
         *
         * \return true wenn alles geklappt hat\n
         *         false wenn etwas nicht geklappt hat und der State nicht gestartet werden konnte
        */
        virtual bool OnEnter([[maybe_unused]] std::string scriptFile = "") = 0;

        //! Bildschirmauflösung hat sich geändert
        /*!
         * Wird immer aufgerufen, wenn die Bildschirm auflösung sich ändert oder von Vollbild auf Fenster oder umgedreht gewechselt wird
         */
        virtual void Resize() = 0;

        //! Aufräumen
        /*! Wenn der State beendet werden soll, muss hier noch Speicher freigegeben werde\n
         *  den man reserviert hat.
         *
         * \return true wenn alles passt
        */
        virtual bool OnExit() = 0;

        //! Name des States
        /*! Gibt des Namen des States zurück
        */
        virtual std::string GetStateID() const = 0;

        virtual ~GameState() {}

    };

} // LibEric

#endif //ERIC_GAMESTATE_HPP
