/*
 * Eric The Viking
 * Copyright (C) 2022  Frank Kartheuser <frank.kartheuser1988@gmail.com>
 * Copyright (C) 2022  Frank Kartheuser <frank.kartheuser1988@gmail.com>
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

#ifndef ERIC_SPRITE_HPP
#define ERIC_SPRITE_HPP

#include <libEric/libEric.hpp>
#include <libEric/GameObject_Interface.hpp>
#include <string>
#include <raylib.h>

namespace LibEric {

    extern "C" {

    class Sprite : public GameObject_Interface {
    public:

        //! Neues Sprite erstellen
        /*!
         * Erstellt ein neues Sprite mit größe 0,0 an posittion 0,0
         * @param textureID Der Name der zu verwendenden Texture
         */
        explicit Sprite(const std::string &textureID = "n/a");

        //! Neues Sprite erstellen
        /*!
         * Erstellt ein neues Sprite mit den angegebenen Parametern
         * @param textureID Name der Texture
         * @param position Position des Sprites auf dem Bildschirm
         * @param size Größe des Sprites auf dem Bildschirm
         */
        Sprite(const std::string &textureID, Vector2 position, Vector2 size);

        //! Zeichnet das Sprite auf den Bildschirm
        /*!
         *
         */
        void Draw() override;

        //! Wird für Sprites nicht gebraucht
        void Update() override;

        //! Speicher wird aufgeräumt
        /*!
         *
         */
        void Clean() override;

        //! Wird nicht benötigt
        void Load([[maybe_unused]]std::string scriptfile) override;


        //! Gibt die ID der Texture zurück, die verwendet wird
        /*!
         *
         * @return ID der verwendeten Texture
         */
        std::string GetID() override;

        //! Gibt die Fläche für Collisionen zurück
        /*!
         * Sprites haben nur ein Collisionrect.
         * @return vector des Collisionrects
         */
        std::vector<CollisionRectangle> GetRects() override;

        //! Für CollisionsManager, wird im Sprite Ignoriert
        /*!
         *
         * @param IDofCollisionObject
         * @param data
         */
        void Collision(std::string IDofCollisionObject, void *data) override;

        //! Setzen der Größe fur das Zeichnen
        /*!
         * Die Größe, mit der das Sprite auf dem Bildschirm gezeichnet wird, wird gesetzt
         * @param size Die neue größe zum Zeichnen
         */
        void SetDrawSize(Vector2 size);

        //! Setzen die Position fur das Zeichnen
        /*!
         * Die Position, an der das Sprite auf dem Bildschirm gezeichnet wird, wird gesetzt
         * @param size Die neue Position zum Zeichnen
         */
        void SetDrawPosition(Vector2 pos);

        //! Setzen der Größe fur der Texture
        /*!
         * Setzt die Größe der Eigentlichen Texture.
         * Wird benötigt, wenn sich mehrere Sprites in einer Texture befinden
         * @sa SetTexturePosition
         * @param size Die neue größe der Texture
         */
        void SetTextureSize(Vector2 size);

        //! Setzen die Position innerhalb der Texture
        /*!
         * Setzt die Position in der Texture, ab w
         * @param size Die neue größe zum Zeichnen
         */
        void SetTexturePosition(Vector2 pos);

        Vector2 GetDrawSize();

        Vector2 GetDrawPosition();

        Vector2 GetTextureSize();

        Vector2 GetTexturePosition();

        void SetTextureID(std::string id);

        bool Moveable() override;


    private:
        Vector2 pDrawPosition;
        Vector2 pDrawSize;
        Vector2 pTexturePosition;
        Vector2 pTextureSize;

    };

    }//extern "C"

} // LibEric

#endif //ERIC_SPRITE_HPP
