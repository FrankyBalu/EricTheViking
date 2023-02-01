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


#ifndef ERIC_GAMEOBJECT_INTERFACE_HPP
#define ERIC_GAMEOBJECT_INTERFACE_HPP

#include <libEric/Rectangle.hpp>
#include <string>
#include <vector>
#include <raylib.h>
#include <ostream>

namespace LibEric {

    class GameObject_Interface {
    public:

        //! Das Object auf dem Bildschirm darstellen
        /*!
         * Diese Funktion dient dazu das Objekt auf den Bildschirm dar zu stellen
         */
        virtual void Draw() = 0;

        //! Update der Logik/Physik/Benutzereingaben
        /*!
         * Hier soll alles was zur Logik des Objekts gehört abgearbeitet werden (z.B. Physik)
         */
        virtual void Update() = 0;

        //! Aufräumen des Speichers
        /*!
         * Alle Verweise des Objektes sollten hier gelöscht werden
         * Reservierter Speicher wird wieder frei gegeben
         */
        virtual void Clean() = 0;

        //! Läd das zum Object gehörende Lua-Script
        /*!
         * Das angegebene Script wird aus dem Datenordner geladen. \n
         * Die Datenordner werden in folgender Reihenfolge durchsucht: \n
         *      Anwendungsordner (Windows: data Linux: /usr/share/{Anwendungsname}/ \n
         *      Homeordner (Linux: ~/.{Anwendungsname}/ \n
         * @param script Name des zu ladenden Scripts (mit Ordnername, wenn nötig z.B. Menu/Main.menu
         */
        virtual void Load(const std::string script) = 0;

        //! Gibt die ID des Objektes zurück
        /*!
         *  Die ID wird unter anderem dazu verwendet, wenn Objekte miteineder Kollidieren, damit sie wissen mit wem sie es zu tun haben
         * @return ID des ObjeKtes
         */
        virtual std::string GetID() = 0;

        //! Gibt alle zu dem Objekt gehörenden Kollisionsrects zurück
        /*!
         * FIXME Doku
         * @return
         */
        virtual std::vector<EricRect> GetRects() = 0;

        //! Ist das Objekt beweglich
        virtual bool Moveable() = 0;

        //! Dise Funktion wird vom ColisionManager aufgerufen, wenn zwei Objekte sich berühren
        virtual void ObjectCollision(std::string ownType, void *data) = 0;

    protected:

        GameObject_Interface() {}

        virtual ~GameObject_Interface() {}

        std::vector<EricRect> _Rects;
    };

} // LibEric

#endif //ERIC_GAMEOBJECT_INTERFACE_HPP
