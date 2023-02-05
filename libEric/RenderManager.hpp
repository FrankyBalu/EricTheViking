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

#ifndef ERIC_RENDERMANAGER_HPP
#define ERIC_RENDERMANAGER_HPP

#include <libEric/libEric.hpp>
#include <string>
#include <map>
#include <raylib.h>

namespace LibEric {

    extern "C" {

    LIBERIC_API class RenderManager {
    public:
        //! Gibt einen Zeiger auf eine Klassen Instance
        static RenderManager *Instance();

        //! Läd eine Texture aus einer Bilddatei
        /*!
         * Läd eine Texture von einer Bilddatei, die Datei wird im Systemordner gesucht
         * Es werden alle Datentypen unterstützt, die Raylib unterstützt.
         * Ist die ID schon vorhanden, wird nix geladen
         *
         * @param fileName name der Datei
         * @param id ID der Texture
         */
        bool LoadTextureFromFile(const std::string &id, const std::string &fileName);

        //! Zeichnet eine Texture auf dn Bildschirm
        /*!
         * Zeichnet die Texture mit der angegebenen id, an der angegebenen stelle auf den Bildschirm.
         *
         * @param id ID der Texture
         * @param x X-Position der Texture
         * @param y Y-Position der Texture
         * @return false, falls keine Texture mit dem Namen vorhanden ist
         */
        bool DrawTextureSimple(const std::string &id, int x, int y);

        //! Zeichnet einen Frame aus einer Texture
        /*!
         * Eine Texture wird in Einzelbilder (Frames) zerlegt.
         * Es wird bei Null angefangen zu zählen.
         * Frame 1 ist <0 + width>
         * Frame 2 ist <0 + (width *2) und so weiter.
         * Zeilen (row) wird genauso behandelt wie Frames
         * So können zum Beispiel mehrere Animationen in einer Datei gespeichert werden
         *
         * Es wird überprüft ob die Frame/Row kombination überhaupt vorhanden ist
         *
         * @param id ID der Texture
         * @param x X-Position an der der Frame gezeichnet werden soll
         * @param y Y-Position an der der Frame gezeichnet werden soll
         * @param width Breite eines Frames
         * @param height Höhe eines Frames
         * @param frame Der Frame der gezeichnet werden soll
         * @param row Die Zeile in der sich der Frame befindet
         * @return false Wenn id nicht existiert oder Frame/Row nicht möglich ist mit der Texture
         */
        bool DrawFrame(const std::string &id, float x, float y, float width, float height, int frame, int row);

        //!Zeichnet einen Frame aus einer Texture
        /*!
         * Eine Teil einer Texture (src) wird auf Fläche <dest> gezeichnet,
         * Über rotate kann die Texture gedreht werden
         *
         * @param id Die ID der Texture
         * @param src Die Fläche innerhalb der Texture
         * @param dest Die Fläche auf dem Bildschirm
         * @param rotate Drehung der Texture
         * @return false Wenn die Texture nicht existiert
         */
        bool DrawEx(const std::string &id, Rectangle src, Rectangle dest, float rotate = 0.0f);

        //! Zeichnet ein Tile aus einer Tilemap
        /*!
         * Ähnlich wie DrawFrame Zeichnet diese Funktion nur einen Teil aus Einer Texture, aber das Prinzip \n
         * wie der Teil berechnet wird ist etwas anders, so das es besser zu einer Tilemap passt.
         * Es werden nur Tilemaps unterstützt, die keinen offset besitzen
         *
         * @param id Die Texture ID
         * @param x Die X-Position auf dem Bildschirm
         * @param y Die Y-Position auf dem Bildschirm
         * @param width Die Breite eines Tiles
         * @param height Die Höhe eines Tiles
         * @param currentRow Die Zeile in der sich das Tile befindet
         * @param currentFrame Die Spalte in der sich das Tile befindet
         * @return false, wenn keine Texture mit der ID vorhanden
         */
        bool
        DrawTile(const std::string &id, float x, float y, float width, float height, int currentRow, int currentFrame);


        //! Gibt den Speicher einer Texture wieder frei
        /*!
         * Gibt den reservierten Speicher wieder frei und löscht die referenz auf die Texture
         *
         * @param id Die ID der zu löschenden Texture
         * @return false, Wenn die Texture nicht gefunden wird
         */
        bool FreeTexture(const std::string &id);

        void ClearRenderManager();


        Rectangle TextureRect(const std::string &id);

    private:

        static RenderManager *pInstance;

        RenderManager();

        ~RenderManager();

        std::map<std::string, Texture2D> pTextureMap;
    };

    }//extern "C"

} // LibEric

#endif //ERIC_RENDERMANAGER_HPP
