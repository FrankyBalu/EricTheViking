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

#ifndef ERIC_LUA_HPP
#define ERIC_LUA_HPP


#define SOL_ALL_SAFETIES_ON 1

#include <sol.hpp>

namespace LibEric {

    //! Erzeugt einen Lua-Context mit allem was für libEric im Allgemeinen nötig ist
    /*!
     * Es wird aber nicht hinzugefügt, was für spezielle Gamestates oder GameObjekte nötig ist
     * @param state  Zeiger auf den Lua-Context, der erstellt werden soll
     */
    void LuaSetup(sol::state *state);

} // LibEric

#endif //ERIC_LUA_HPP
