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

#ifndef ERIC_LIBERICSETTINGS_HPP
#define ERIC_LIBERICSETTINGS_HPP

#include <string>

namespace LibEric {

    //! Einstellungen für libEric, die nicht zur Laufzeit verändert werden können
    class LibEricSettings {
    public:
        //! Gibt einen Zeiger auf die Instance der Klasse
        /*!
         * Von LibEricSettings gibt es immer nur eine Instance
         * @return Zeiger auf die Instance
         */
        static LibEricSettings *Instance();

        /* Es wird erst versucht eine settings-Datei unter $HOME/.local/share/{anwendungsname}/ zu finden \n
         * ist dort keine, wird es unter /usr/share/{anwendungsname]/ versucht \n
         * @return true wenn eine Datei gefunden wurde und geladen werden konnte, sonst false
         */
        bool Load();

        //! Der Gamestate der als erstes Geladen werden soll
        /*!
         * Wird eventuell noch entfernt, bin mir nicht sicher ob es benötigt wird
         * @return Name des ertsen Gamestates
         */
        std::string GetFirstState();

        //! Soll die Version angezeigt werden
        /*!
         * Gibt an, ob die Version von libEric in der unteren linken Bildschirmecke angezeigt wird
         * @return true wenn die Version angezeigt werden soll
         */
        bool GetShowVersion();

        //! Gibt den Rot-Wert für den Hintergrund an
        /*!
         * Gibt den Rot-Wert an, mit dem der Bildschirm gecleart wird
         * @return Rot
         */
        int GetBGCRed();

        //! Gibt den Grün-Wert für den Hintergrund an
        /*!
         * Gibt den Grün-Wert an, mit dem der Bildschirm gecleart wird
         * @return Grün
         */
        int GetBGCGreen();

        //! Gibt den Blau-Wert für den Hintergrund an
        /*!
         * Gibt den Blau-Wert an, mit dem der Bildschirm gecleart wird
         * @return Blau
         */
        int GetBGCBlue();

        //! Gibt den Alpha-Wert für den Hintergrund an
        /*!
         * Gibt den Alpha-Wert an, mit dem der Bildschirm gecleart wird
         * @return Alpha
         */
        int GetBGCAlpha();

        //! Gibt die Breite der Dialogboxen im Spiel an
        /*!
         * Gibt die Breite der Dialogboxen an, der Wert muss zwischen 0 und 1 liegen.
         * Bei 0.5 wäre die Box halb so breit wie der Bildschirm/das Fenster.
         * @return Die Breite der Dialogbox
         */
        float GetDialogBoxWidth();

        //! Gibt die Höhe der Dialogboxen im Spiel an
        /*!
         * Gibt die Höhe der Dialogboxen an, der Wert muss zwischen 0 und 1 liegen.
         * Bei 0.5 wäre die Box halb so hoch wie der Bildschirm/das Fenster.
         * @return Die Höhe der Dialogbox
         */
        float GetDialogBoxHeight();

        //! Gibt das Loglevel an
        /*!
         * Legt fest, was auf der Konsole gelogt wird
         * @return LogLevel
         */
        int GetLogLevel();

        //! Gibt an, ob MSAA aktiviert wird
        /*!
         * return true wenn aktiviert
         */
        bool GetMSAA();

        //! Taste, die das Programm beendet
        /*!
         * @return scan_code der Taste
         */
        int GetExitKey();

        //! Gibt den Dateinamen für den default Font zurück
        std::string GetFont();


        LibEricSettings(const LibEricSettings &) = delete;

        LibEricSettings(LibEricSettings &&) = delete;

        LibEricSettings &operator=(const LibEricSettings &) = delete;

        LibEricSettings &operator=(LibEricSettings &&) = delete;

    private:
        static LibEricSettings *_Instance;//!< Zeiger auf das zur Klasse gehörende Objekt
        LibEricSettings(); //!< Konstructor

        std::string _FirstState; //!< Der erste Gamestate der aufgerufen wird, meist sicherlich main.menu oder splash

        float _DialogBoxWidth; //!< Breite der DialogBoxen im Spiel
        float _DialogBoxHeight; //!< Höhe der Dialogboxen im Spiel
        bool _ShowVersion; //!< Blendet Dauerhaft die Version von libEric in der Linken untern
        bool _EnableMSAA; //!< Wenn true, wird MSAA angeschalten
        int _BackgroundColorRed; //!< Hintergrundfarbe
        int _BackgroundColorGreen; //!< Hintergrundfarbe
        int _BackgroundColorBlue; //!< Hintergrundfarbe
        int _BackgroundColorAlpha; //!< Hintergrundfarbe
        int _LogLevel; //!< Loglevel, @LibEric::Log
        int _ExitKey; //!< Taste mit der das Programm direkt beendet wird FIXME: in UserSettings verschieben, so wie ale tasten
        std::string _Font;
    };

} // LibEric

#endif //ERIC_LIBERICSETTINGS_HPP
