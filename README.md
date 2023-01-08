## EricTheViking
Advanture/RPG inspieriert von alten (SNES) Zelda und alten Final Fantasy teilen.


## Übersicht

Erik wird ein kleines Advanture/RPG, das viele Elemente von The Legend of Zelda (SNES) und Final Fantasy vereint.
Die ErikFW soll dabei als mehr oder weniger eigentständiges Projekt entstehen und es ermöglichen, relativ einfach, mit wenig c++, Tiled (https://www.mapeditor.org/) und lua ein eigenes Spiel auf die Beine zu stellen.


# Bauanleitung

## Linux / BSD

Momentan wird eine interne kopie von tinyxml2, zlib, sol2 und lua verwendet, später wird man sich entscheiden können, ob man die interne Version nutzen möchte oder die vom System installierte.

```
git clone https://gitlab.com/kleinod88/erik.git
cd erik
mkdir build
cd build
cmake ..
make
```

## Windows

Für später mal geplant.


## Die Großen Ziele

- [X] [Git Projekt erstellen]
- [ ] [Einstellungen mit lua laden]
- [ ] [Menüs mit lua erstellen]
- [ ] [Karten laden und Kamera implämentieren]
- [ ] [Spieler erstellen]
- [ ] [Kollisionssystem]
- [ ] [Übergange zu den einzelnen Karten]
- [ ] [Wegweiser und Hinweisschilder]
- [ ] [NPCs]
- [ ] [Zerstörbares Gras und Gegenstände]
- [ ] [Gegner]
- [ ] [Inventar und Items]
- [ ] [Storyknoten]


