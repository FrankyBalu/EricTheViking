/*
 * libEric
 * Copyright (C) 2022   Frank Kartheuser <frank.kartheuser1988@gmail.com>
 * Copyright (C) 2023   Frank Kartheuser <frank.kartheuser1988@gmail.com>
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

#ifndef __GAME
#define __GAME


namespace LibEric {

//!  Das eigentliche Spiel.
/*!
  Theoretisch die einzige Klasse die vom eigentlichen Spiel aufgerufen werden muss.
*/
class Game {
public:

    //! Spiel bzw. Framework initialisieren
    /*! Alle einstellungen werden geladen und ein Fenster erstellt.\n
        Es wird der Gamestate geladen, der in den FrameworkSettings\n als erster state angebenist.

        \param title Der Name des Spiels, der in der Fensterdekoratin angeziegt wird.
        \return true wenn alles geklappt hat.\n
                false wenn etwas schiefgegangen ist.
    */
    bool Init(const char* title);

    //! Rendern
    /*! Es wird der Spielstate Gerendert.
        Der Bildschirm wird gelöscht und mit der in den FrameworkSettings\n angegebenen Farbe gefüllt

    */
    void Render();

    //! Update
    /*! Es wird die (logik)Updatefunktion des Gamestates ausgeführt.
        Auserdem wird überprüft ob der Benutzer das Fenster schließen möchte.
    */
    void Update();

    //! Benutzer eingaben werden verarbeitet
    /*! Es werden die eingaben per Tastatur, Maus und Gamepad verarbeitet
    */
    void HandleEvents();

    //! Aufräumen
    /*! Der Speicher wird aufgeräumt, Dateien entladen, so das man das Programm schließen kann
    */
    void Clean();

    //! Läuft das Spiel?
    /*! Gibt zurück ob das Spiel noch läuft oder nicht
     *
     * \return true wenn das Fenster noch geöffnet ist und der MainLoop noch läuft\n
     *         false wenn der MainLoop nicht mehr läuft.
    */
    bool Running();

    //! Beendet das Programm bzw den MainLoop
    /*! Der MainLoop wird beendet
    */
    void Quit();

    //! Zwischen Vollbild und Fenster wechseln
    /*! Es wird zwischen Vollbildmodus und Fenstermodus gewechselt
    */
    void ToggleFS();

    //! Abfragen ob wir im Vollbild sind
    /*! True wenn wir im FUllscreen sind
    */
    bool IsFS();

    static Game* Instance();
    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

private:

    Game();
    ~Game();



    static Game* _Instance;



    bool _Running;
};

}; //namespace LibEric
#endif //__GAME
