## EricTheViking
Advanture/RPG inspieriert von alten (SNES) Zelda und alten Final Fantasy teilen.


## Übersicht

Erik wird ein kleines Advanture/RPG, das viele Elemente von The Legend of Zelda (SNES) und Final Fantasy vereint.
Die libEric soll dabei als mehr oder weniger eigenständiges Projekt entstehen und es ermöglichen, relativ einfach, mit wenig c++, Tiled (https://www.mapeditor.org/) und lua ein eigenes Spiel auf die Beine zu stellen.


# Bauanleitung

## Linux / BSD

Es werden tinyxml2, zlib, lua zum bauen benötigt.

```
git clone https://github.com/FrankyBalu/EricTheViking.git
cd EricTheViking
mkdir build
cd build
cmake ..
make
sudo make install

```

## Windows

Sowohl mit Visual Studio als auch mit CLion ist das Projekt baubar.

## Die Großen Ziele für libEric

- [X] [Einstellungen mit lua laden]
- [X] [Menüs mit lua erstellen]
- [X] [Karten laden und Kamera implämentieren]
- [ ] [Kollisionssystem]
- [ ] [Übergange zu den einzelnen Karten]
- [ ] [Wegweiser und Hinweisschilder]
- [ ] [NPCs]
- [ ] [Zerstörbares Gras und Gegenstände]
- [ ] [Gegner]
- [ ] [Inventar und Items]
- [ ] [Storyknoten]


