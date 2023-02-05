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


#ifndef ERIC_GAMESTATEMASCHINE_HPP
#define ERIC_GAMESTATEMASCHINE_HPP

#include <libEric/libEric.hpp>
#include <libEric/GameState.hpp>
#include <string>
#include <vector>

namespace LibEric {

    extern "C" {

    LIBERIC_API class GameStateMaschine {
    public:
        //! Zeiger auf die Instace der Klasse
        static GameStateMaschine *Instance();

        //! Fügt einen neuen Gamestate hinzu
        /*! Es wird ein neue State hinzugefügt und direkt zu diesem gewechselt.\n
            Der Vorhergehende State bleibt erhalten, so das man zurück wechseln kann.
            Der neue State wird komplett neu erstellt, ist schon ein State des Types\n
            vorhanden, wird dieser nicht überschrieben sondern ein neuer erstellt.

            \param stateID ID des States, zu dem gewechselt werden soll.
            \param file Das Script, das dem State übergeben wird, muss nicht angegeben werden\n
                        wenn der State kein lua-Script unterstützt.
        */
        bool PushState(std::string stateID, std::string file = "");

        //! Fügt einen neuen Gamestate hinzu
        /*! Es wird ein neue State hinzugefügt und direkt zu diesem gewechselt.\n
            Der Vorhergehende State wird gelöscht.
            Der neue State wird komplett neu erstellt, ist schon ein State des Types\n
            vorhanden, wird dieser nicht überschrieben sondern ein neuer erstellt.

            \param stateID ID des States, zu dem gewechselt werden soll.
            \param file Das Script, das dem State übergeben wird, muss nicht angegeben werden\n
                        wenn der State kein lua-Script unterstützt.
        */
        bool ChangeState(std::string stateID, std::string file = "");

        //!Entfernt Game den aktuellen Gamestate
        /*! Der aktuelle Gamestate wird beendet und gelöscht und zu dem Vorhergehenden\n
         *  gewechselt.
         *  Ist kein State mehr vorhanden, ist das verhalten undefiniert.
            \todo Wenn alle States beendet sind, das Programm beenden.
        */
        bool PopState();

        //! State Update
        /*! Ruft die Update-Funktion des States auf.
        */
        void Update();

        //! State Update
        /*! Ruft die Render-Funktion des States auf.
        */
        void Render();

        //! State Update
        /*! Ruft die HandleEvents-Funktion des States auf.
        */
        void HandleEvents();

        //! Auflösung wurde geändert
        /*!
         * Wenn die Auflösung geändert wird, wird diese Funktion aufgerufen.
         * Im gegegensatz zu \sa Render \sa Update und \sa HandlerEvents wird diese Funktion bei allen geladenen Gamestates aufgerufen
         */
        void Resize();

        //! State ID
        /*! Git die Id des aktuellen States zurück
         *
         * \return aktuelle StateID
        */
        std::string GetCurrentStateID();

    private:
        static GameStateMaschine *_Instance;

        GameStateMaschine() : _GameStates() {}

        std::vector<GameState *> _GameStates;
    };

    }//extern "C"

} // LibEric

#endif //ERIC_GAMESTATEMASCHINE_HPP
