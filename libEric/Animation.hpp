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

#ifndef ERIC_ANIMATION_HPP
#define ERIC_ANIMATION_HPP

#include <libEric/libEric.hpp>
#include <libEric/Sprite.hpp>
#include <map>

namespace sol{class state;};

namespace LibEric {

    extern "C" {

    typedef struct AnimationStruct {
        std::vector<std::string> TextureIDs;
        Rectangle TextureRect;
        int NumFrames;
        float Duration;
    } AnimationStruct;

    LIBERIC_API class Animation : public Sprite {
    public:
        //! Constructor
        Animation();

        //! Läd eine Animation aus einer Datei
        void Load(const std::string scriptFile);

        //! Zeichnet die Animation auf den Bildschirm
        /*!
         *
         */
        void Draw();

        //! Updated interne Variablen
        /*!
         * Updated FrameCounter und setzt die TextureID neu, wenn notwendig
         */
        void Update();

        //! Löscht den reservierten Speicher
        /*
         *
         */
        void Clean();

        //! Gibt die ID der aktuellen Animation zurück
        /*!
         * Es wird die ID der Animation zurückgegeben, nicht die des Sprites
         * @return Animations ID
         */
        std::string GetID();

        //! Hiermit wird die Animation gestartet
        void Play();

        //! Animation wird angehalten und resetet
        void Stop();

        //! FrameCounter und Frames werden auf 0 gesetzt
        void Reset();

        //! Setzt die Animations ID, die abgespielt werden soll
        /*!
         *
         * @param id Die neue ID
         * @return false, wenn die ID nicht vorhanden ist
         */
        bool SetAnimationToID(std::string id);

        //! Eine neue Texture wird zur Animation hinzugefügt
        /*!
         * Fügt der Animation mit animationsID eine neue Texture hinzu, wenn path
         * leer ist, wird keine neue Texture geladen, sondern nur die ID(file) zur Animation hinzugefügt.
         * @param animationID ID der Animation
         * @param path Dateipfad, wo die Texture liegt
         * @param file Dateiname udn ID der Texture
         */
        void AddTexture(std::string animationID, std::string path, std::string file);

        //! Setzt die abspieldauer
        /*!
         * Setzt die abspiel dauer für eine bestimmte Animation
         * @param animationID ID der Animation
         * @param duration Die abspielzeit (0.5 = eine halbe Minute, 1.0 = 1 Minute, 2.0 = 2 Minute, ...
         * @return false, wenn animationID nicht vorhanden.
         */
        bool SetDuration(std::string animationID, float duration);

        //! Setzt das Rect der Texture
        void SetTextureRect(std::string id, float x, float y, float w, float h);

    private:
        std::map<std::string, AnimationStruct> pAnimationStruct;
        std::string pCurrentAnimationID;
        int pFrameCounter;
        int pCurrentTexture;
        std::string pCurrentTextureID;
        bool play;
        sol::state *lua;
    };

    }//extern "C"

} // LibEric

#endif //ERIC_ANIMATION_HPP
