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

#ifndef ERIC_GAMESTATEFACTORY_HPP
#define ERIC_GAMESTATEFACTORY_HPP

#include <libEric/libEric_API.hpp>
#include <libEric/Core/GameState.hpp>
#include <string>
#include <map>

namespace LibEric {

    extern "C" {

    //! StateCreator
    /*!
     * Basisklasse, die die Schnittstelle beschreibt, die ein StateCreator einhalten muss
     */
    LIBERIC_API class StateBaseCreator {
    public:

        //! Erstellt den neuen State
        /*!
         * Gibt einen neuen Gamestate zurück, wird nicht direkt aufgerufen, sondern sollte nur von GameStateFactory verwendet werden
         * @return nullptr, wenn der State nicht erstellt werden konnte
         */
        virtual GameState *CreateState() const = 0;

        virtual ~StateBaseCreator() {}
    };

    //! Die Klasse, die neue Gamestates erstellt
    LIBERIC_API class GameStateFactory {
    public:
        //! Zeiger auf die Instance der Klasse
        static GameStateFactory *Instance();

        //! Neue State wird Registriert
        /*!
         * Registriert einen neuen BaseCreator, damit eine instance des Gamestates erstellt werden kann.
         *
         * @param typeID ID unter der der neue State angesprochen wird
         * @param creator Der StateBaseCreator des Gamestates
         * @return false, wenn schon ein State mit der ID existiert
         */
        bool RegisterType(std::string typeID, StateBaseCreator *creator);

        //! Erstellt einen neuen Gamestate
        /*!
         * Hier wird der neue Gamestate erstellt
         * @param typeID ID des zu erstellenden States
         * @return false, wenn die ID nicht vorhanden ist oder kein State erstellt werden konnte
         */
        GameState *Create(std::string typeID);

    private:
        static GameStateFactory *_Instance;

        GameStateFactory() : _Creators() {}

        std::map<std::string, StateBaseCreator *> _Creators;
    };

    }//extern "C"

} // LibEric

#endif //ERIC_GAMESTATEFACTORY_HPP
