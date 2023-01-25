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

#ifndef __GRAPHICGAMEOBJECT
#define __GRAPHICGAMEOBJECT

#include "GameObject.hpp"
#include <raylib.h>


namespace LibEric {

class  GraphicGameObject : public GameObject
{
public:

    GraphicGameObject();

    //Objektparameter Laden
    virtual void Load (const std::string script);

    //Objekt Darstellen
    virtual void Draw();

    //Logik des Objektes updaten
    virtual void Update();

    //Speicher freigeben
    virtual void Clean();

    //Position des Objektes zurückgeben
    Vector2 GetPosition();
    void SetPosition (float x, float y);

    int GetWidth ();
    int GetHeight();
    void SetWidth (float w);
    void SetHeight (float h);

    //FIXME: Braucht man das?
    //Namen für das Objekt Setzen
    void SetName(std::string name);
    //Namen vom Objekt bekommen
    std::string GetName();


    //FIXME Collisionszeug sollte in eigene Klasse
    //      Kollisionsboxen sollten aber natürlich beim Objekt bleiben
    //
    //Diese Funktionen betreffen nur das Setzen der Kollisionsboxen
    //und das abfragen der selbigen
    void SetNorth(Rectangle north);//Oben
    void SetEast (Rectangle east);//Rechts
    void SetSouth( Rectangle south);//Unten
    void SetWest(Rectangle west);//Links
    void SetObject(Rectangle object);//Für Kollision mit umgebung und anderen Objekten
    Rectangle GetNorth();
    Rectangle GetEast();
    Rectangle GetSouth();
    Rectangle GetWest();
    Rectangle GetObject();




    //Temp funktion, bis ein collisionsManager fertig ist
    void SetActivCollision(int activ);
    int GetActivCollision();
    bool CollisionDetect (GraphicGameObject *obj);



    void ResetAtack() {
        _IsAttack = false;
    }
protected:

    int _Width;
    int _Height;

    Vector2 _Position;
    Vector2 _Velocity;
    Vector2 _Acceleration;

    int _CurrentFrame;
    int _CurrentRow;
    int _NumFrames;

    std::string _TextureID;

    std::string _Name;

    //FIXME Collision muss in eigene klasse und deutlich verbessert werden
    //Für die Collisionsbestimmung
    Rectangle _ObjectCollision;
    Rectangle _NorthCollision, _EastCollision, _SouthCollision, _WestCollision;
    int _ActivCollision; // 0 = none, 1=north, 2 =east, 3=South, 4=_WestCollision
    int _Direction; // siehe _ActivCollision

    bool _IsAttack;

    bool _Visable;

};

}; //namespace LibEric
#endif // __GRAPHICGAMEOBJECT
