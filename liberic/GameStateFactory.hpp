/*
 * LibEric
 * Copyright (C) 2021  Frank Kartheuser <frank.kartheuser1988@gmail.com>
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


#ifndef __GAMESTATEFACTORY
#define __GAMESTATEFACTORY

#include <string>
#include <map>
#include "GameState.hpp"

namespace LibEric {

//!  StateCreator
/*!
  Basis Klasse, mit ihr müssen alle StateCreators erstellt werden,\n
  Damit sie zum Spielhinzugefügt werden können
*/
class StateBaseCreator
{
public:
    //! Neuen State erstellen
    /*! Es wird ein neue Gamestate zurückgegeben
        \return den neuen Gamestate, wenn alles geklappt hat,\n
                sondt nullptr.
    */
    virtual GameState* CreateState() const = 0;
    virtual ~StateBaseCreator() {}
};

//!  Das eigentliche Spiel.
/*!
  Theoretisch die einzige Klasse die vom eigentlichen Spiel aufgerufen werden muss.
*/
class GameStateFactory
{
public:

    //! Neuen StateType Regestrieren
    /*! Es wird ein neues Gamestate (creator) registriert
    */
    bool RegisterType(std::string typeID, StateBaseCreator* creator);

    //! Gamestate erstellen
    /*! Es wird ein neuer GameState von der angegebenen Id zurück gegeben
     *
     * \param typeID Id des Gamestates, den man erstellen möchte
     *
     * \return nullptr wenn Id unbekannt oder sonst etwas schief läuft,\n
     *         sonst einen Pointer auf den neuen Gamestate.
    */
    GameState* Create(std::string typeID);

    //! Neuen State erstellen
    /*! Es wird ein neue Gamestate zurückgegeben
        \return den neuen Gamestate, wenn alles geklappt hat,\n
                sondt nullptr.
    */
    static GameStateFactory* Instance()
    {
        if (_Instance == nullptr)
            _Instance = new GameStateFactory();
        return _Instance;
    }

private:


    GameStateFactory():_Creators() {}

    std::map<std::string, StateBaseCreator*> _Creators;

    static GameStateFactory *_Instance;
};

}; //namespace LibEric
#endif // __GAMESTATEFACTORY
