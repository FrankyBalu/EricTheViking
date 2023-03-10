//
// Created by frank on 27.01.23.
//

#ifndef ERIC_LIBERICAPP_HPP
#define ERIC_LIBERICAPP_HPP

#include "libEric/libEric_API.hpp"
#include <string>
#include <raylib.h>

namespace LibEric {

    extern "C" {

    LIBERIC_API class LibEricApp {
    public:
        //! Gibt einen Zeiger auf eine Klassen Instance
        static LibEricApp *Instance();

        //! Initialisiert das Object der Klasse LibEricApp
        /*!
         * Hier werden alle Einstellungen geladen und das Fenster erstellt, in dem gerendert wird.
         * Desweiteren werden alle GameStates und GameObjekte, die fest zu libEric gehören geladen.
         * Alle zu ladenden Dateien gehören in das Systemverzeichniss, das libEric vorgibt (meist /usr/share/{Anwendungsname}
         * @param appName Name der Anwendung, wichtig für das laden von Dateien.
         * @return false, wenn irgendwas nicht geklappt hat
         */
        bool Init(const std::string &appName);

        //! Ist libEric initialisiert?
        /*!
         * Einige Funktionen sind darauf angewissen, das der OpenGl context geladen ist bzw die Einstellungen \n
         * diese können das hiermit überprüfen.
         *
         * @return true Wenn die Init-Funktion erfolgreich aufgerufen wurde
         */
        bool IsReady();

        //! Sorgt dafür das die Renderfunktion des aktuellen States aufgerufen wird
        /*!
         * Löscht den Bildschirminhalt und Rendert den aktuellen State, wenn Overlays vorhanden sind \n
         * werden diese nach dem State gerendert (z.B. Dialoge, InGameMenu (Itemmenu, CharakterMenu.....)
         */
        void Render();

        //! Update der Logik
        /*!
         * Die Updatefunktion des aktuellen States wird aufgerufen.
         * Hier sollte die Programmlogik/Ki-Funktionen abgearbeitet werden
         */
        void Update();

        //! Auf eingaben reagieren
        /*!
         * Die HandleEvents-Funktion des aktuellen States wird aufgerufen
         * Hier soll auf benutzer eingaben reagiert werden
         */
        void HandleEvents();

        //! Auflösung wurde geändert
        void Resize();

        //! Beendet das Spiel
        /*!
         * Diese Funktion Räumt den Speicher auf und beendet das Spiel
         */
        void Clean();

        //! Beendet den Mainloop
        /*!
         * Setzt _Runnig auf false, wodurch die Hauptschleife beendet wird
         */
        void Quit();

        //! Gibt das Benutzer Verzeichnis zurück
        /*!
         * Hier können zum Beispiel Speicherstände abgelegt werden
         * @return Das Benutzerverzeichniss der Anwendung
         */
        std::string GetUserDir();

        //! Hauptschleife des Spiels
        /*!
         * Wenn diese Funktion aufgerufen wird, werden alle Update und Render-Funktionen in der richtigen \n
         * reihenfolge aufgerufen, bis das spiel beendet wird
         *
         */
        void Run();

        //! Gibt die Breite das Fensters/Bildschirm zurück
        int GetWindowWidth();

        //! Gibt die Höhe des Fensters/Bildschirms zurück
        int GetWindowHeight();

        //! Gibt den Defaultfont zurück
        Font GetDefaultFont();

        LibEricApp(const LibEricApp &) = delete;

        LibEricApp(LibEricApp &&) = delete;

        LibEricApp &operator=(const LibEricApp &) = delete;

        LibEricApp &operator=(LibEricApp &&) = delete;


        //!da meine installation probleme mit meinen Controllern hat, das als Workarout
        int GetGamepad() { return UseGamepad; }

        void SetGamepad(int gp) { UseGamepad = gp; };

    private:
        static LibEricApp *_Instance;

        LibEricApp();

        bool _IsReady;
        bool _Running;
        std::string _AppName;
        std::string _AppDir;

        Font _Font;
        int _FontSize;
        int UseGamepad;
    };

    }//extern "C"

} // LibEric

#endif //ERIC_LIBERICAPP_HPP
